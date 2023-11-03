#include <asm/page.h>
#include <asm/io.h>
#include <linux/stddef.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/gfp.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <xen/xen.h>
#include <asm/xen/hypercall.h>
#include "modxom.h"

#define MMUEXT_MARK_XOM       21
#define MMUEXT_UNMARK_XOM     22

#define MODXOM_PROC_FILE_NAME "xom"
#define READ_HEADER_STRING "        Address:             Size:\n"
#define MAPPING_LINE_SIZE ((2 * (2 * sizeof(size_t) + 2)) + 5)
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define page_l_arr_index(pmapping, index) ((pmapping)->lock_status[(index) >> 3])
#define is_page_locked(pmapping, index)  ((page_l_arr_index(pmapping, index) & (1 << ((index) & 0x7))) ? 1 : 0)
#define set_lock_status(pmapping, index, val) \
    page_l_arr_index(pmapping, index) = (page_l_arr_index(pmapping, index) & ~(1 << ((index) & 0x7))) | (((val) ? 1 : 0) << ((index) & 0x7))

struct
{
    struct list_head lhead;
    unsigned int num_pages;
    unsigned long kaddr;
    unsigned long uaddr;
    uint8_t* lock_status;
} typedef xom_mapping, *pxom_mapping;

struct
{
    struct list_head lhead;
    pid_t pid;
    struct list_head mappings;
} typedef xom_process_entry, *pxom_process_entry;

LIST_HEAD(xom_entries);
static struct mutex file_lock;

static bool were_pages_locked(pxom_mapping mapping){
    unsigned int i;
    uint8_t ret = 0;

    for(i = 0; i < (mapping->num_pages >> 3) + 1; i++)
        ret |= mapping->lock_status[i];

    return ret > 0;
}

// Add or remove hypervisor protection
static int xen_handle_xom(pxom_mapping mapping, unsigned int page_index, unsigned int num_pages, bool set_xom){
	int status;
    struct mmuext_op op;
    unsigned long kaddr = mapping->kaddr + page_index * PAGE_SIZE;
    unsigned long cur_kaddr = kaddr, base_kaddr = kaddr;
    unsigned int page_c, i, pages_locked = 0;
	phys_addr_t cur_gfn, last_gfn;

    if(!num_pages)
        return 0;
    if(page_index + num_pages > mapping->num_pages)
        return -EINVAL;

    memset(&op, 0, sizeof(op));

    while(cur_kaddr < kaddr + PAGE_SIZE * num_pages){
        page_c = 0;

        // Group into physically contiguous ranges
        do{
            page_c++;
            cur_kaddr += PAGE_SIZE;
            last_gfn = cur_gfn;
            cur_gfn = virt_to_phys((void*) kaddr);
        } while((last_gfn == cur_gfn + PAGE_SIZE) && (cur_kaddr < kaddr + PAGE_SIZE * num_pages));

        // Perform Hypercall for range
        op.cmd = set_xom ? MMUEXT_MARK_XOM : MMUEXT_UNMARK_XOM;
        op.arg1.mfn = virt_to_phys((void*) base_kaddr);
        op.arg2.nr_ents = page_c;
        printk(KERN_INFO "[XOM Seal] Invoking Hypervisor with mfn 0x%lx for %u pages\n", op.arg1.mfn, op.arg2.nr_ents);
        status = HYPERVISOR_mmuext_op(&op, 1, NULL, DOMID_SELF);

        if(status){
            printk(KERN_INFO "[XOM Seal] Failed - Status 0x%x\n", status);
            return status;
        }

        // Update lock status in mapping struct
        for(i = 0; i < page_c; i++)
            set_lock_status(mapping, page_index + pages_locked + i, 1);
        
        base_kaddr = cur_kaddr;
        pages_locked += page_c;
        // Repeat until all physically contiguous ranges are locked
    }

	return 0;
}

static int release_mapping(pxom_mapping mapping) {
    int status;
    unsigned long i;
    struct page *page = virt_to_page(mapping->kaddr);

    if (!page)
        return -EFAULT;


    if(were_pages_locked(mapping)){
        status = xen_handle_xom(mapping, 0, mapping->num_pages, false);
        if(status)
            return status;
    }

    for (i = 0; i < mapping->num_pages * PAGE_SIZE; i += PAGE_SIZE)
        ClearPageReserved(virt_to_page(mapping->kaddr + i));

    // Don't mess with a dying processes address space
    if (!(current->flags & PF_EXITING)) {
        if(vm_munmap(mapping->uaddr, mapping->num_pages * PAGE_SIZE))
            return -EFAULT;
    }

    free_pages(mapping->kaddr, get_order(mapping->num_pages * PAGE_SIZE));
    if(mapping->lock_status){
        kfree(mapping->lock_status);
        mapping->lock_status = NULL;
    }

    return 0;
}

static pxom_process_entry get_process_entry(void)
{
    pxom_process_entry curr_entry = (pxom_process_entry)xom_entries.next;
    while ((void *)curr_entry != &xom_entries)
    {
        if (curr_entry->pid == current->pid)
            break;
        curr_entry = (pxom_process_entry)curr_entry->lhead.next;
    }
    if ((void *)curr_entry == &xom_entries)
        return NULL;
    return curr_entry;
}

static int release_process(pxom_process_entry curr_entry)
{
    pxom_mapping last_mapping, curr_mapping;

    if (!curr_entry)
        return -EINVAL;

    curr_mapping = (pxom_mapping)curr_entry->mappings.next;

    while ((void *)curr_mapping != &(curr_entry->mappings))
    {
        release_mapping(curr_mapping);
        last_mapping = curr_mapping;
        curr_mapping = (pxom_mapping)curr_mapping->lhead.next;
        kfree(last_mapping);
    }
    return 0;
}

static int xmem_free(pmodxom_cmd cmd){
    int status;
    pxom_process_entry curr_entry;
    pxom_mapping curr_mapping;

    curr_entry = get_process_entry();
    if(!curr_entry)
        return -EINVAL;
    
    curr_mapping = (pxom_mapping) curr_entry->mappings.next;
    while ((void *)curr_mapping != &(curr_entry->mappings)){
        if(curr_mapping->uaddr != cmd->base_addr){
            curr_mapping = (pxom_mapping)curr_mapping->lhead.next;
            continue;
        }
        
        if(curr_mapping->num_pages != cmd->num_pages)
            return -EINVAL;
        
        status = release_mapping(curr_mapping);

        if(status)
            return status;
        list_del(&(curr_mapping->lhead));
        kfree(curr_mapping);
        return 0;
    }
    return -EINVAL;
}

static int lock_pages(pmodxom_cmd cmd){
    unsigned page_index;
    pxom_process_entry curr_entry;
    pxom_mapping curr_mapping;

    curr_entry = get_process_entry();
    if(!curr_entry)
        return -EINVAL;
    
    curr_mapping = (pxom_mapping) curr_entry->mappings.next;
    while ((void *)curr_mapping != &(curr_entry->mappings)){
        if(cmd->base_addr < curr_mapping->uaddr || 
                cmd->base_addr >= curr_mapping->uaddr + curr_mapping->num_pages * PAGE_SIZE){
            curr_mapping = (pxom_mapping)curr_mapping->lhead.next;
            continue;
        }

        page_index = (cmd->base_addr - curr_mapping->uaddr) / PAGE_SIZE;
        
        if(cmd->base_addr + cmd->num_pages * PAGE_SIZE > curr_mapping->uaddr + curr_mapping->num_pages * PAGE_SIZE) 
            return -EINVAL;
        
        return xen_handle_xom(curr_mapping, page_index, cmd->num_pages, true);
    }
    return -EINVAL;
}

static pxom_mapping get_new_mapping(struct vm_area_struct *vma, pxom_process_entry curr_entry)
{
    unsigned long size = (vma->vm_end - vma->vm_start);
    void *newmem = NULL;
    uint8_t* n_lock_status = NULL;
    unsigned int i;
    int status;
    pxom_mapping new_mapping = NULL;

    if (!curr_entry)
        return NULL;

    // Must be page-aligned
    if (size % PAGE_SIZE || vma->vm_start % PAGE_SIZE || !size) {
        return NULL;
    }

    new_mapping = kmalloc(sizeof(*new_mapping), GFP_KERNEL);
    if (!new_mapping)
        return NULL;
    
    n_lock_status = kmalloc(((size / PAGE_SIZE) >> 3) + 1, GFP_KERNEL);
    if(!n_lock_status)
        goto fail;

    memset(n_lock_status, 0, ((size / PAGE_SIZE) >> 3) + 1);

    newmem = (void *)__get_free_pages(GFP_KERNEL, get_order(size));
    if (!newmem || (ssize_t)newmem == -1)
        goto fail;

    // Set PG_reserved bit to prevent swapping
    for (i = 0; i < size; i += PAGE_SIZE)
        SetPageReserved(virt_to_page(newmem + i));

    memset(newmem, 0x0, PAGE_SIZE * (1 << get_order(size)));

    status = remap_pfn_range(vma, vma->vm_start, page_to_pfn(virt_to_page(newmem)), size, vma->vm_page_prot);

    if (status < 0)
        goto fail;

    *new_mapping = (xom_mapping){
        .num_pages = size / PAGE_SIZE,
        .kaddr = (unsigned long)newmem,
        .uaddr = vma->vm_start,
        .lock_status = n_lock_status
    };

    return new_mapping;

fail:
    if (curr_entry)
        kfree(curr_entry);
    if(n_lock_status)
        kfree(n_lock_status);
    if (newmem)
        __free_pages(virt_to_page(newmem), get_order(size));
    return NULL;
}

int xom_open(struct inode *, struct file *)
{
    pxom_process_entry new_entry = kmalloc(sizeof(*new_entry), GFP_KERNEL);
    new_entry->pid = current->pid;
    INIT_LIST_HEAD(&(new_entry->mappings));
    mutex_lock(&file_lock);
    list_add(&(new_entry->lhead), &xom_entries);
    mutex_unlock(&file_lock);
    return 0;
}

int xom_release(struct inode *, struct file *)
{
    int status;
    pxom_process_entry curr_entry;

    mutex_lock(&file_lock);
    curr_entry = get_process_entry();
    status = release_process(curr_entry);
    list_del(&(curr_entry->lhead));
    kfree(curr_entry);
    mutex_unlock(&file_lock);

    return status;
}

int xom_mmap(struct file *f, struct vm_area_struct *vma)
{
    int status = 0;
    pxom_process_entry curr_entry;
    pxom_mapping new_mapping;

    if(!xen_hvm_domain())
        return -ENODEV;

    mutex_lock(&file_lock);

    curr_entry = get_process_entry();
    new_mapping = get_new_mapping(vma, curr_entry);

    if (!new_mapping)
        status = -EINVAL;
    else
        list_add(&(new_mapping->lhead), &(curr_entry->mappings));

    mutex_unlock(&file_lock);
    return status;
}

ssize_t xom_read(struct file *f, char __user *user_mem, size_t len, loff_t *offset)
{
    size_t len_reqired = sizeof(READ_HEADER_STRING), index, clen;
    char *dstring;
    pxom_process_entry curr_entry;
    pxom_mapping curr_mapping;
    struct vm_area_struct *vma;

    mutex_lock(&file_lock);

    curr_entry = get_process_entry();
    curr_mapping = (pxom_mapping)curr_entry->mappings.next;
    while ((void *)curr_mapping != &(curr_entry->mappings))
    {
        len_reqired += MAPPING_LINE_SIZE;
        curr_mapping = (pxom_mapping)curr_mapping->lhead.next;
    }

    if (*offset >= len_reqired)
        return 0;

    dstring = kvmalloc(len_reqired, GFP_KERNEL);
    if (!dstring)
        return -ENOMEM;

    memcpy(dstring, READ_HEADER_STRING, sizeof(READ_HEADER_STRING));
    curr_mapping = (pxom_mapping)curr_entry->mappings.next;
    index = sizeof(READ_HEADER_STRING) - 1;
    while ((void *)curr_mapping != &(curr_entry->mappings) && index < len_reqired)
    {
        vma = find_vma(current->mm, curr_mapping->uaddr);
        if (!vma)
        {
            curr_mapping = (pxom_mapping)curr_mapping->lhead.next;
            continue;
        }
        index += snprintf(dstring + index, len_reqired - index, "%16lx, %16lx\n",
                          vma->vm_start, vma->vm_end - vma->vm_start);
        curr_mapping = (pxom_mapping)curr_mapping->lhead.next;
    }

    clen = MIN(len_reqired - (unsigned long)*offset, len);
    if (copy_to_user(user_mem, dstring + *offset, clen))
        clen = 0;
    *offset += clen;
    kvfree(dstring);

    mutex_unlock(&file_lock);
    return clen;
}

ssize_t xom_write(struct file *f, const char __user *user_mem, size_t len, loff_t *offset)
{
    ssize_t ret = -EINVAL;
    modxom_cmd cmd;
    if(len < sizeof(modxom_cmd))
        return -EINVAL;
    if(copy_from_user(&cmd, user_mem, sizeof(cmd)))
        return -EFAULT;
    
    mutex_lock(&file_lock);
    switch(cmd.cmd){
        case MODXOM_CMD_NOP:
            ret = sizeof(cmd);
            break;
        case MODXOM_CMD_FREE:
            ret = xmem_free(&cmd);
            break;
        case MODXOM_CMD_LOCK:
            ret = lock_pages(&cmd);
            break;
        default:;
    }

    mutex_unlock(&file_lock);

    return ret;
}

const static struct proc_ops file_ops = {
    .proc_open = xom_open,
    .proc_release = xom_release,
    .proc_read = xom_read,
    .proc_write = xom_write,
    .proc_mmap = xom_mmap
};

static int __init modxom_init(void) {
    struct proc_dir_entry *entry;
    printk(KERN_INFO "[MODXOM] Hello World!\n");
    mutex_init(&file_lock);
    entry = proc_create(MODXOM_PROC_FILE_NAME, 0666, NULL, &file_ops);
    printk(KERN_INFO "[MODXOM] MODXOM Kernel Module loaded!\n");
    return 0;
}

static void __exit modxom_exit(void) {
    pxom_process_entry curr_entry = (pxom_process_entry)xom_entries.next, last_entry;
    while ((void *)curr_entry != &xom_entries)
    {
        release_process(curr_entry);
        last_entry = curr_entry;
        curr_entry = (pxom_process_entry)curr_entry->lhead.next;
        kfree(last_entry);
    }

    remove_proc_entry(MODXOM_PROC_FILE_NAME, NULL);
    mutex_destroy(&file_lock);
    printk(KERN_INFO "[MODXOM] MODXOM Kernel Module unloaded. Goodbye!\n");
}

module_init(modxom_init);
module_exit(modxom_exit);

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Tristan Hornetz");

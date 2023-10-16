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
#include <linux/dma-mapping.h>

#define MODXOM_PROC_FILE_NAME "xom"

struct {
    struct list_head lhead;
    loff_t mmap_offset;
    unsigned int num_pages;
    unsigned int num_refs;
    uintptr_t kaddr;
} typedef xom_mapping, *pxom_mapping;

struct {
    struct list_head lhead;
    pid_t pid;
    struct list_head mappings;
} typedef xom_process_entry, *pxom_process_entry;

LIST_HEAD(xom_entries);

static int release_mapping(pxom_mapping mapping) {
    uintptr_t i;
    struct vm_area_struct* vma = find_vma(current->mm, mapping->kaddr);
    unsigned long vm_flags;

    if(!vma)
        return -EFAULT;

    vm_flags = vma->vm_flags | VM_DONTEXPAND | VM_DONTDUMP;

    for(i = 0; i < mapping->num_pages * PAGE_SIZE; i += PAGE_SIZE)
        ClearPageReserved(virt_to_page(mapping->kaddr + i));

    if (remap_pfn_range(vma, mapping->kaddr, 0, mapping->num_pages * PAGE_SIZE, (pgprot_t){vm_flags})) {
        printk(KERN_ERR "Failed to unmap kernel pages from user space\n");
        return -EFAULT;
    }

    kfree((void*) mapping->kaddr);
    return 0;
}

static pxom_process_entry get_process_entry(void){
    pxom_process_entry curr_entry = (pxom_process_entry) xom_entries.next;
    while ((void*)curr_entry != &xom_entries) {
        if (curr_entry->pid == current->pid)
            break;
        curr_entry = (pxom_process_entry) curr_entry->lhead.next;
    }
    if ((void*)curr_entry == &xom_entries)
        return NULL;
    return curr_entry; 
}

static int release_process(pxom_process_entry curr_entry){
    pxom_mapping last_mapping, curr_mapping;

    if (!curr_entry)
        return -EINVAL;
    
    curr_mapping = (pxom_mapping) curr_entry->mappings.next;

    while ((void*)curr_mapping != &(curr_entry->mappings)) {
        curr_mapping->num_refs--;
        if(curr_mapping->num_refs > 0){
            curr_mapping = (pxom_mapping) curr_mapping->lhead.next;
            continue;
        }
        release_mapping(curr_mapping);
        last_mapping = curr_mapping;
        curr_mapping = (pxom_mapping) curr_mapping->lhead.next;
        kfree(last_mapping);
    } 
    return 0;
}

int	xom_open(struct inode *, struct file *) {
    pxom_process_entry new_entry = kmalloc(sizeof(*new_entry), GFP_KERNEL);
    new_entry->pid = current->pid;
    INIT_LIST_HEAD(&(new_entry->mappings));
    list_add(&(new_entry->lhead), &xom_entries);
    return 0;
}

int	xom_release(struct inode *, struct file *){
    int status;
    pxom_process_entry curr_entry = get_process_entry();

    status = release_process(curr_entry);
    list_del(&(curr_entry->lhead));
    kfree(curr_entry);
    return status;
}

int	xom_mmap(struct file * f, struct vm_area_struct * vma){
    unsigned long size = (vma->vm_end - vma->vm_start);
    uintptr_t newmem, i;
    int status;
    pxom_mapping new_mapping;
    pxom_process_entry curr_entry = get_process_entry();
    struct page *page;

    printk(KERN_INFO "[MODXOM] Enter xom_mmap\n");

    if (!curr_entry)
        return -EINVAL;

    // Must be page-aligned
    if (size % PAGE_SIZE || vma->vm_start % PAGE_SIZE || !size)
        return -EINVAL;

    new_mapping = kmalloc(sizeof(*new_mapping), GFP_KERNEL);
    if (!new_mapping)
        return -ENOMEM;
    
    newmem = (uintptr_t) kmalloc(size, GFP_KERNEL);
    if(!newmem){
        kfree(curr_entry);
        return -ENOMEM;
    }

    printk(KERN_INFO "[MODXOM] newmem: %p\n", (void*) newmem);

    // Set PG_reserved bit to prevent swapping
    for(i = 0; i < size; i += PAGE_SIZE)
        SetPageReserved(virt_to_page(newmem + i));

    page = virt_to_page(newmem);
    status = remap_pfn_range(vma, vma->vm_start, page_to_pfn(page), size, 
        (pgprot_t){(vma->vm_page_prot.pgprot) | VM_DONTCOPY | VM_DONTDUMP | VM_DONTEXPAND});

    if(status < 0){
        kfree(curr_entry);
        kfree((void*) newmem);
        return status;
    }

    *new_mapping = (xom_mapping) {
        .mmap_offset = f->f_pos,
        .num_pages = size / PAGE_SIZE,
        .num_refs = 1,
        .kaddr = newmem
    };

    list_add(&(new_mapping->lhead), &(curr_entry->mappings));

    return status;
}

ssize_t	xom_read(struct file * _f, char __user * _user_mem, size_t _len, loff_t * _offest){
    return -ENOTSUPP;
}

ssize_t	xom_write(struct file * _f, const char __user * _user_mem, size_t _len, loff_t * _offset){
    return -ENOTSUPP;
}

const static struct proc_ops file_ops = {
    .proc_open = xom_open,
    .proc_release = xom_release,
    .proc_read = xom_read,
    .proc_write = xom_write,
    .proc_mmap = xom_mmap,
};


static int __init
MODXOM_init(void) {
    struct proc_dir_entry *entry;
    printk(KERN_INFO
    "[MODXOM] Hello World!\n");
    entry = proc_create(MODXOM_PROC_FILE_NAME, 0666, NULL, &file_ops);
    printk(KERN_INFO
    "[MODXOM] MODXOM Kernel Module loaded!\n");
    return 0;
}

static void __exit
MODXOM_exit(void) {
    pxom_process_entry curr_entry = (pxom_process_entry) xom_entries.next, last_entry;
    while((void*) curr_entry != &xom_entries){
        release_process(curr_entry);
        last_entry = curr_entry;
        curr_entry = (pxom_process_entry) curr_entry->lhead.next;
        kfree(last_entry);
    }

    remove_proc_entry(MODXOM_PROC_FILE_NAME, NULL);
    printk(KERN_INFO
    "[MODXOM] MODXOM Kernel Module unloaded. Goodbye!\n");
}

module_init(MODXOM_init);
module_exit(MODXOM_exit);

MODULE_LICENSE("GPL");


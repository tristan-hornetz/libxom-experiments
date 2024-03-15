#define CL_TARGET_OPENCL_VERSION 300
#include <stdio.h>
#include <CL/cl.h>
#include <string.h>
#include <sys/mman.h>
#include "libxom.h"

asm (".data\nkernelText: .incbin \"kernel.cl\"\nkernelTextEnd: .byte 0x00");

extern char kernelText[];
extern char kernelTextEnd[];

static char test_str[] = "This text should be inaccessible!";

static cl_device_id get_gpu() {
    cl_int status;
    cl_platform_id platform;
    cl_device_id dev;

    status = clGetPlatformIDs(1, &platform, NULL);
    if (status < 0)
        goto error;

    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
    if (status >= 0)
        return dev;

    puts("No OpenCL-capable GPU found! Attempting to use CPU...");

    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
    if(status < 0)
        goto error;

    return dev;

error:
    printf("Could not find an OpenCL-capable device! Error: %d\n", status);
    exit(1);
}

static cl_program build_kernel(cl_context ctx, cl_device_id dev_id){
    cl_int status = 0;
    const char* src = kernelText;
    const size_t kernel_size = kernelTextEnd - kernelText + 1;
    cl_program program = clCreateProgramWithSource(ctx, 1,&src, &kernel_size, &status);
    if (status < 0)
        goto error;
    status = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (status < 0)
        goto error;
    return program;
error:
    printf("Could not build kernel! Error: %d\n", status);
    exit(1);
}

int main() {
    const size_t workgroup_size = 1;
    const unsigned int test_str_size = sizeof(test_str);
    char output[sizeof(test_str)] = {0, }, *input;
    cl_int status;
    size_t kernel_size = kernelTextEnd - kernelText + 1;
    cl_device_id device_id = get_gpu();
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &status);
    cl_program program;
    cl_command_queue queue;
    cl_mem data_in, data_out;
    cl_kernel kernel;
    struct xombuf* xbuf;
    unsigned i;

    if (status < 0){
        puts("Could not create context!");
        return 1;
    }

    xbuf = xom_alloc(PAGE_SIZE);
    xom_write(xbuf, test_str, sizeof(test_str), 0);
    input = xom_lock(xbuf);
    if(!input){
        puts("Could not allocate XOM!");
         return 1;
    }

    //input = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    //printf("Input: %p\n", input);
    //memcpy(input, test_str, sizeof(test_str));
    //mprotect(input, PAGE_SIZE, PROT_NONE);

    program = build_kernel(context, device_id);
    queue = clCreateCommandQueueWithProperties(context, device_id, NULL, &status);
    if (status < 0){
        puts("Could not create command queue!");
        return 1;
    }

    data_in = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(test_str), input, &status);

    if(status < 0){
        puts("Could not create input buffer!");
        return 1;
    }

    data_out  = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(test_str), NULL, &status);

    if(status < 0){
        puts("Could not create output buffer!");
        return 1;
    }

    kernel = clCreateKernel(program, "copy", &status);
    if (status < 0){
        puts("Could not create kernel!");
        return 1;
    }
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &data_in);
    status |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &data_out);
    status |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &test_str_size);
    if(status < 0) {
        puts("Could not add parameters!");
        return 1;
    }

    //clEnqueueCopyBuffer(queue,data_in,data_out,0,0,sizeof(test_str),0,NULL,NULL);

    status = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &workgroup_size, &workgroup_size, 0, NULL, NULL);
    if(status < 0) {
        puts("Could not enqueue kernel!");
        return 1;
    }

    clFinish(queue);

    clEnqueueReadBuffer(queue, data_out, CL_TRUE, 0, sizeof(output), output, 0, NULL, NULL);

    for(i = 0; i < sizeof(output); i++)
        printf("%c", output[i]);
    puts("");

    clReleaseKernel(kernel);
    clReleaseMemObject(data_in);
    clReleaseMemObject(data_out);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);

    return 0;
}

#pragma once

#include <Slab.h>
#include <Uart.h>
#include <stdint.h>

extern char HEAP_START;
extern char HEAP_END;

namespace Kernel {
namespace Kmalloc {

static const uint32_t HEAP_BOTTOM = (uint32_t)&HEAP_START;
static const uint32_t HEAP_TOP = (uint32_t)&HEAP_END;
static const uint32_t KB_SIZE = 1024;
static uint32_t HEAP_BOTTOM_CUR = HEAP_BOTTOM;

static const uint32_t SLABS_COUNT = 7;
static Slab SLABS[SLABS_COUNT];

size_t kmalloc_slab_buffer_align(size_t size)
{
    return ((size - 1) | 3) + 1;
}

size_t kmalloc_size_coerce(size_t size)
{
    size--;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    return ++size;
}

void kmalloc_slab_init(size_t slab_index, size_t slab_size, size_t buffer_size)
{
    size_t buffer_aligned_size = kmalloc_slab_buffer_align(sizeof(Slab::Buffer) + buffer_size);
    size_t buffer_count = slab_size / buffer_aligned_size;
    size_t total_size = buffer_aligned_size * buffer_count;
    uint32_t ptr = HEAP_BOTTOM_CUR;
    HEAP_BOTTOM_CUR += total_size;
    SLABS[slab_index] = Slab(ptr, buffer_count, buffer_size, buffer_aligned_size - buffer_size - sizeof(Slab::Buffer));
}

void kmalloc_init()
{
    kmalloc_slab_init(0, 128 * KB_SIZE, 2);
    kmalloc_slab_init(1, 128 * KB_SIZE, 4);
    kmalloc_slab_init(2, 512 * KB_SIZE, 8);
    kmalloc_slab_init(3, 512 * KB_SIZE, 16);
    kmalloc_slab_init(4, 128 * KB_SIZE, 32);
    kmalloc_slab_init(5, 64 * KB_SIZE, 64);
    kmalloc_slab_init(6, 64 * KB_SIZE, 128);
}

void* kmalloc(size_t size)
{
    size = kmalloc_size_coerce(size);
    uint32_t ptr;
    for (int i = 0; i < SLABS_COUNT; i++) {
        if (SLABS[i].alloc(&ptr, size)) {
            break;
        }
    }
    return (void*)ptr;
}

void kfree(void* ptr)
{
    for (int i = 0; i < SLABS_COUNT; i++) {
        if (SLABS[i].free(ptr)) {
            break;
        }
    }
}

}
}

void* operator new(size_t size)
{
    return Kernel::Kmalloc::kmalloc(size);
}

void* operator new[](size_t size)
{
    return Kernel::Kmalloc::kmalloc(size);
}

void operator delete(void* ptr)
{
    Kernel::Kmalloc::kfree(ptr);
}

#include <Slab.h>
#include <stdint.h>

extern char HEAP_START;
extern char HEAP_END;

namespace Kernel {

static const uint32_t HEAP_BOTTOM = (uint32_t)&HEAP_START;
static const uint32_t HEAP_TOP = (uint32_t)&HEAP_END;
static const uint32_t KB_SIZE = 1024;
static uint32_t HEAP_BOTTOM_CUR = HEAP_BOTTOM;

static Slab SLABS[4];

size_t kmalloc_slab_buffer_align(size_t size)
{
    return ((size - 1) | 3) + 1;
}

void kmalloc_slab_init(size_t slab_index, size_t slab_size, size_t buffer_size)
{
    size_t buffer_count = slab_size / buffer_size;
    size_t total_size = buffer_size * buffer_count;
    uint32_t ptr = HEAP_BOTTOM_CUR;
    HEAP_BOTTOM_CUR += total_size;
    SLABS[slab_index] = Slab(ptr, buffer_count, buffer_size);
}

void kmalloc_init()
{
    kmalloc_slab_init(0, 1 * KB_SIZE, kmalloc_slab_buffer_align(sizeof(Slab::Buffer) + 1));
    kmalloc_slab_init(1, 2 * KB_SIZE, kmalloc_slab_buffer_align(sizeof(Slab::Buffer) + 2));
    kmalloc_slab_init(2, 4 * KB_SIZE, kmalloc_slab_buffer_align(sizeof(Slab::Buffer) + 4));
    kmalloc_slab_init(3, 8 * KB_SIZE, kmalloc_slab_buffer_align(sizeof(Slab::Buffer) + 8));
}

}

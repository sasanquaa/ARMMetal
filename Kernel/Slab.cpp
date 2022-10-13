#include <Slab.h>

namespace Kernel {

Slab::Slab(uint32_t buffer_ptr, size_t buffer_count, size_t buffer_size)
    : m_buffer_list((Buffer*)buffer_ptr)
    , m_buffer_count(buffer_count)
    , m_buffer_size(buffer_size)
    , m_ref_count(0)
{
    size_t slab_size = sizeof(Buffer);
    for (auto i = 1; i < m_buffer_count; i++) {
        Buffer* buffer = (Buffer*)buffer_ptr;
        buffer->m_next = (Buffer*)(buffer_ptr + m_buffer_size);
        buffer->m_ptr = (void*)(buffer_ptr + slab_size);
        buffer_ptr += m_buffer_size;
    }
}

void Slab::alloc()
{
}

void Slab::free()
{
}

}

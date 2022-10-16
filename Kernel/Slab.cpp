#include <Kernel/Slab.h>

namespace Kernel {

void Slab::init(uintptr_t buffer_ptr, size_t buffer_count, size_t buffer_size, size_t align_size)
{
    m_buffer_list = (Buffer*)buffer_ptr;
    m_buffer_count = buffer_count;
    m_buffer_size = buffer_size;
    m_ref_count = 0;

    size_t slab_size = sizeof(Buffer);
    size_t buffer_aligned_size = buffer_size + slab_size + align_size;
    for (auto i = 1; i < m_buffer_count; i++) {
        Buffer* buffer = (Buffer*)buffer_ptr;
        buffer->m_next = (Buffer*)(buffer_ptr + buffer_aligned_size);
        buffer->m_occupied = false;
        buffer->m_ptr = (void*)(buffer_ptr + slab_size);
        buffer_ptr += buffer_aligned_size;
    }
}

bool Slab::alloc(uintptr_t* ptr, size_t size)
{
    if (size != m_buffer_size || m_ref_count == m_buffer_count) {
        return false;
    }
    for (auto buffer = m_buffer_list; buffer != nullptr; buffer = buffer->m_next) {
        if (!buffer->m_occupied) {
            buffer->m_occupied = true;
            *ptr = (uintptr_t)buffer->m_ptr;
            m_ref_count++;
            break;
        }
    }
    return true;
}

bool Slab::free(void* ptr)
{
    if (m_ref_count == 0) {
        return false;
    }
    for (auto buffer = m_buffer_list; buffer != nullptr; buffer = buffer->m_next) {
        if (buffer->m_occupied && buffer->m_ptr == ptr) {
            buffer->m_occupied = false;
            m_ref_count--;
            return true;
        }
    }
    return false;
}

}

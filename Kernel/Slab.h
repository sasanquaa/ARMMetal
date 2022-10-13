#pragma once

#include <stddef.h>
#include <stdint.h>

namespace Kernel {

class Slab final {
public:
    struct Buffer {
        Buffer* m_next;
        bool m_occupied;
        void* m_ptr;
    };

    Slab() = default;

    Slab(uint32_t buffer_ptr, size_t buffer_count, size_t buffer_size, size_t align_size);

    bool alloc(uint32_t* ptr, size_t size);

    bool free(void* ptr);

private:
    Buffer* m_buffer_list;
    size_t m_buffer_count;
    size_t m_buffer_size;
    size_t m_ref_count;
};

}

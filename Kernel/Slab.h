#pragma once

#include <stddef.h>
#include <stdint.h>

namespace Kernel {

class Slab final {
public:
    struct Buffer {
        Buffer* m_next;
        void* m_ptr;
    };

    Slab() = default;

    Slab(uint32_t buffer_ptr, size_t buffer_count, size_t buffer_size);

    void alloc();

    void free();

private:
    Buffer* m_buffer_list;
    size_t m_buffer_count;
    size_t m_buffer_size;
    size_t m_ref_count;
};

}

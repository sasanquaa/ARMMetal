#pragma once

#include <Kernel/Referable.h>
#include <Kernel/Traits.h>

namespace Kernel {

template<typename T, typename = RequiresExtend<Referable, T>>
void ref_if_not_null(const T* ptr)
{
    if (ptr) {
        ptr->ref();
    }
}

template<typename T, typename = RequiresExtend<Referable, T>>
void unref_if_not_null(const T* ptr)
{
    if (ptr) {
        ptr->unref();
    }
}

template<typename T, typename = RequiresExtend<Referable, T>>
void ref_count_assert_if_not_null(const T* ptr, ReferableCounter count)
{
    if (ptr) {
        assert(ptr->count() == count);
    }
}

}

#pragma once

#include <Kernel/ReferableUtils.h>

namespace Kernel {

template<typename T>
class WeakPtr;

template<typename T>
class UniquePtr;

template<typename T>
class ReferablePtr {
public:
    template<typename = RequiresExtend<Referable, T>>
    ReferablePtr() { }

    template<typename = RequiresExtend<Referable, T>>
    explicit ReferablePtr(const T* ptr)
        : ReferablePtr(ptr, false)
    {
    }

    template<typename = RequiresExtend<Referable, T>>
    ReferablePtr(const T* ptr, bool raw)
        : m_ptr(const_cast<T*>(ptr))
    {
        if (!raw) {
            ref_if_not_null(m_ptr);
        }
    }

    template<typename = RequiresExtend<Referable, T>>
    explicit ReferablePtr(const T& obj)
        : m_ptr(const_cast<T*>(&obj))
    {
        ref_if_not_null(m_ptr); // m_ptr not null
    }

    ReferablePtr(const ReferablePtr<T>& other)
        : m_ptr(const_cast<ReferablePtr<T>&>(other).raw())
    {
        ref_if_not_null(m_ptr);
    }

    ~ReferablePtr()
    {
        unref_if_not_null(m_ptr);
        m_ptr = nullptr;
    }

    ReferablePtr& operator=(const T* ptr)
    {
        swap(const_cast<T*>(ptr));
        return *this;
    }

    ReferablePtr& operator=(const T& obj)
    {
        swap(const_cast<T*>(&obj));
        return *this;
    }

    ReferablePtr& operator=(const ReferablePtr<T>& other)
    {
        swap(const_cast<ReferablePtr<T>&>(other).raw());
        return *this;
    }

    T* operator->()
    {
        assert(m_ptr);
        return m_ptr;
    }

    T& operator*()
    {
        assert(m_ptr);
        return *m_ptr;
    }

    T* raw() { return m_ptr; }

    UniquePtr<T> as_unique()
    {
        UniquePtr<T> ptr = UniquePtr<T>(m_ptr);
        m_ptr = nullptr;
        return ptr;
    }

    WeakPtr<T> as_weak()
    {
        return WeakPtr<T>(raw());
    }

    operator bool() { return m_ptr != nullptr; }

private:
    void swap(T* new_ptr)
    {
        T* old_ptr = m_ptr;
        m_ptr = new_ptr;
        ref_if_not_null(m_ptr);
        unref_if_not_null(old_ptr);
    }

    T* m_ptr = nullptr;
};

}

#pragma once

#include <Kernel/ReferableUtils.h>
#include <Kernel/UniquePtrForward.h>
#include <LibC/assert.h>

template<typename T>
class ReferablePtr {
public:
    ReferablePtr() = default;

    explicit ReferablePtr(const T* ptr)
        : ReferablePtr(ptr, false)
    {
    }

    ReferablePtr(const T* ptr, bool raw)
        : m_ptr(const_cast<T*>(ptr))
    {
        if (!raw) {
            ref_if_not_null(m_ptr);
        }
    }

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

    ReferablePtr(ReferablePtr<T>&& other)
        : m_ptr(other.raw())
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

    ReferablePtr& operator=(ReferablePtr<T>&& other)
    {
        swap(const_cast<T*>(other.raw()));
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

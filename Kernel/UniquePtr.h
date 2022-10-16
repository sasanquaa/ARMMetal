#pragma once

#include <Kernel/ReferablePtrForward.h>
#include <Kernel/ReferableUtils.h>
#include <LibC/assert.h>

template<typename T>
class UniquePtr {
public:
    UniquePtr() = delete;

    explicit UniquePtr(const T* ptr)
        : m_ptr(const_cast<T*>(ptr))
    {
        ref_count_assert_if_not_null(m_ptr, 1);
    }

    explicit UniquePtr(const T& obj)
        : m_ptr(&obj)
    {
        ref_count_assert_if_not_null(m_ptr, 1);
    }

    UniquePtr(const UniquePtr<T>& other)
        : m_ptr(const_cast<UniquePtr<T>&>(other).transfer())
    {
    }

    UniquePtr(UniquePtr<T>&& other)
        : m_ptr(other.transfer())
    {
    }

    ~UniquePtr()
    {
        unref_if_not_null(m_ptr);
        m_ptr = nullptr;
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

    UniquePtr& operator=(const UniquePtr<T>& other)
    {
        m_ptr = const_cast<UniquePtr<T>&>(other).transfer();
        return *this;
    }

    UniquePtr& operator=(UniquePtr<T>&& other)
    {
        m_ptr = other.transfer();
        return *this;
    }

    T* raw() { return m_ptr; }

    ReferablePtr<T> as_referable()
    {
        return ReferablePtr<T>(transfer(), true);
    }

    operator bool() { return m_ptr != nullptr; }

private:
    T* transfer()
    {
        T* current = m_ptr;
        m_ptr = nullptr;
        return current;
    }

    T* m_ptr = nullptr;
};
;

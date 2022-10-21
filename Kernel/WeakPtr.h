#pragma once

#include <Kernel/Traits.h>
#include <Kernel/WeaklyReferable.h>

namespace Kernel {

template<typename T>
class WeakPtr {
public:
    template<typename = RequiresExtend<WeaklyReferable, T>>
    WeakPtr() { }

    template<typename = RequiresExtend<WeaklyReferable, T>>
    explicit WeakPtr(const T* ptr)
        : m_link(const_cast<T*>(ptr)->link())
    {
    }

    template<typename = RequiresExtend<WeaklyReferable, T>>
    explicit WeakPtr(const T& obj)
        : m_link(obj.link())
    {
    }

    WeakPtr(const WeakPtr<T>& other)
        : m_link(other.m_link)
    {
    }

    WeakPtr& operator=(const T* ptr)
    {
        m_link = const_cast<T*>(ptr)->link();
        return *this;
    }

    WeakPtr& operator=(const T& obj)
    {
        m_link = obj.link();
        return *this;
    }

    WeakPtr& operator=(const WeakPtr<T>& other)
    {
        m_link = other.m_link;
        return *this;
    }

    T* operator->()
    {
        return static_cast<T*>(m_link->raw());
    }

    T& operator*()
    {
        return static_cast<T*>(m_link->raw());
    }

    T* raw()
    {
        if (m_link) {
            return static_cast<T*>(m_link->raw());
        }
        return nullptr;
    }

    ReferablePtr<T> as_referable()
    {
        return ReferablePtr<T>(raw());
    }

    operator bool() { return raw() != nullptr; }

private:
    ReferablePtr<WeaklyReferableLink> m_link;
};

}

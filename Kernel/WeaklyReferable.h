#pragma once

#include <Kernel/ReferablePtr.h>

namespace Kernel {

class WeaklyReferable;

class WeaklyReferableLink : public Referable {
    friend class WeaklyReferable;

public:
    WeaklyReferable* raw() { return m_ptr; }

private:
    WeaklyReferableLink(const WeaklyReferable* ptr)
        : m_ptr(const_cast<WeaklyReferable*>(ptr))
    {
    }

    void clear() { m_ptr = nullptr; }

    mutable WeaklyReferable* m_ptr;
};

class WeaklyReferable : public Referable {
public:
    ReferablePtr<WeaklyReferableLink> link() const { return m_link; }

protected:
    WeaklyReferable()
        : m_link(new WeaklyReferableLink(this), true)
    {
    }

    ~WeaklyReferable()
    {
        m_link->clear();
    }

private:
    ReferablePtr<WeaklyReferableLink> m_link;
};

}

#pragma once

#include <LibC/assert.h>

namespace Kernel {

using ReferableCounter = unsigned int;

class Referable {
public:
    void ref() const
    {
        assert(m_counter);
        ++m_counter;
    }

    void unref() const
    {
        assert(m_counter);
        if (--m_counter == 0) {
            delete this;
        }
    }

    ReferableCounter count() const { return m_counter; }

protected:
    Referable() = default;

    virtual ~Referable()
    {
        assert(!m_counter);
    }

private:
    mutable ReferableCounter m_counter = 1;
};

}

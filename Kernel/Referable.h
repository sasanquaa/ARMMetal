#pragma once

#include <LibC/assert.h>

using ReferableCounter = unsigned int;

template<typename T>
class Referable {
    template<typename U>
    friend void ref_if_not_null(const U* ptr);
    template<typename U>
    friend void unref_if_not_null(const U* ptr);

public:
    ReferableCounter count() const { return m_counter; }

protected:
    Referable() = default;

    ~Referable()
    {
        assert(!m_counter);
    }

    void ref() const
    {
        assert(m_counter);
        ++m_counter;
    }

    void unref() const
    {
        assert(m_counter);
        if (--m_counter == 0) {
            delete static_cast<const T*>(this);
        }
    }

private:
    mutable ReferableCounter m_counter = 1;
};

#pragma once

namespace Kernel {

template<bool, typename>
class Requires {
};

template<typename T>
class Requires<true, T> {
public:
    typedef T Type;
};

template<typename T, typename U>
class Extends {
private:
    class True {
        char m_dummy[4];
    };
    class False {
    };

    static True extends(T*);

    static False extends(void*);

public:
    static const bool Value = sizeof(extends(static_cast<U*>(nullptr))) == sizeof(True);
};

}

template<bool C, typename T>
using Requires = typename Kernel::Requires<C, T>::Type;

template<typename T, typename U>
constexpr bool Extends = Kernel::Extends<T, U>::Value;

template<typename T, typename U>
using RequiresExtend = Requires<Extends<T, U>, T>;

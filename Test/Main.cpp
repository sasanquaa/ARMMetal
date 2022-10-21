#include <Kernel/UniquePtr.h>
#include <Kernel/WeakPtr.h>
#include <assert.h>
#include <iostream>

namespace Kernel {

class Foo : public WeaklyReferable {
    ~Foo()
    {
        assert(count() == 0);
    }
};

void test_weak()
{
    WeakPtr<Foo> weak_foo;
    std::cout << "Current weak ptr (main): " << weak_foo.raw() << std::endl;
    {
        ReferablePtr<Foo> strong_foo { new Foo(), true };
        std::cout << "Current strong ptr (scope): " << strong_foo.raw() << std::endl;
        UniquePtr<Foo> unique_foo = strong_foo.as_unique();
        std::cout << "Current strong ptr (scope): " << strong_foo.raw() << std::endl;
        std::cout << "Current unique ptr (scope): " << unique_foo.raw() << std::endl;
        strong_foo = unique_foo.as_referable();
        std::cout << "Current strong ptr (scope): " << strong_foo.raw() << std::endl;
        std::cout << "Current unique ptr (scope): " << unique_foo.raw() << std::endl;
        weak_foo = strong_foo.as_weak();
        std::cout << "Current weak ptr (scope): " << weak_foo.raw() << std::endl;
        strong_foo = weak_foo.as_referable();
        std::cout << "Current strong ptr (scope): " << strong_foo.raw() << " / " << strong_foo->count() << std::endl;
        ReferablePtr<Foo> strong_foo2 = weak_foo.as_referable();
        std::cout << "Current strong ptr (scope): " << strong_foo2.raw() << " / " << strong_foo->count() << std::endl;
    }
    std::cout << "Current weak ptr (main): " << weak_foo.raw() << std::endl;
}

}

int main()
{
    Kernel::test_weak();
    return 0;
}

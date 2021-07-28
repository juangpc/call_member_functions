#include <functional>
#include <iostream>

class Foo {
    public:
        static void doSomething(int i) { std::cout << "i = " << i << "\n";}
        void call(std::function<void(int)> f, int i) {
                f(i);
        }
};

class Foo2;

class Foo2 {
    public:
        void doSomething(int i) { std::cout << "i = " << i << "\n";}
        void call(std::function<void(Foo2*, int)> f, Foo2* foo, int i) {
            f(foo, i);
        }
};

int main()
{
    Foo f;
    f.call(Foo::doSomething, 32);

    Foo2 f2;
    f2.call(&Foo2::doSomething, &f2, 22);

    return 0;
}
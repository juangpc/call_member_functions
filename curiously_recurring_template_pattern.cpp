#include <iostream>

template <typename T>
class Base {
public:
    T* downCast() {
        return static_cast<T*>(this);
    }

    // virtual void sayHi() {
    //     
    // }

};

// template<typename T>
// void processRuntime(Base<T>* b)
// {
//     b->sayHi();
// }

template<typename T>
void processCompileTime(Base<T>* b)
{
    b->downCast()->sayHi();
}

class Derived1 : public Base<Derived1>
{
public:
    void sayHi() /*final*/
    {
        std::cout << "in Derived1\n";
    }
};

class Derived2 : public Base<Derived2>
{
public: 
    void sayHi() /*final*/
    {
        std::cout << "in Derived2\n";
    }
};

int main() {
    Derived1* d1 = new Derived1();
    Derived2* d2 = new Derived2();

    processCompileTime(d1);
    processCompileTime(d2);

    //processRunTime(d1);
    //processRunTime(d2);

    return EXIT_SUCCESS;
}








#include <iostream>
#include <typeinfo>

class Base {
public:
    Base() : a{33}, b{44}, f{0.22} {
        std::cout << "Constructor Base.\n";
    }
    int a;
    int b;
    float f;
//    char* ustring = "this is an unmutable";
    virtual void sayHi() {
        std::cout << "Base hello!\n";
    }

};

class Derived: public Base {
public:
    Derived() : a2{3}, a3{2} /*,f2{0.55}*/ {
        std::cout << "Constructor Derived.\n";
    }
    int a2;
    int a3;
//    double f2;
    void sayHi() {
        std::cout << "Derived hello!\n";
    }
    void sayHi2() {
        std::cout << "Derived hello!\n";
    }
};

void blat() {
    std::cout << "hhh\n";
}

int main() {
    char* myStr = new char[12];
    memcpy(myStr, (void*)"blablabla",9);
            "blablabla";
    Derived d;
    std::cout << "Hello, World! " << sizeof(d) << std::endl;
    d.sayHi();
    Base b;
    b.sayHi();
    void* blahhh{(void*) blat};
    Base* bp;
    bp = &d;
    bp->sayHi();

    return 0;
}
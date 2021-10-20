#include <iostream>
#include <functional>
#include <vector>


class A 
{
public:
    friend std::ostream& operator<<(std::ostream& os, const A& a);
    A():count(0){}

    void incrementCount() {
        count++;
    }
    void incrementCount2() {
        incrementCount();
        incrementCount();
    }
    void incrementCount3() {
        incrementCount();
        incrementCount();
        incrementCount();
    }
private:
    int count;
    bool dataReady;
};

std::ostream& operator<<( std::ostream& os, const A& a) 
{
    os << " count: " << a.count << "\n";
    return os;
}

void incrementCountStatic(void* ptr)
{
    A* a = static_cast<A*>(ptr);
    a->incrementCount();
}

void incrementCount2Static(void* ptr)
{
    A* a = static_cast<A*>(ptr);
    a->incrementCount2();
}

void incrementCount3Static(void* ptr)
{
    A* a = static_cast<A*>(ptr);
    a->incrementCount3();
}

struct Binder
{   Binder(void(*f)(void*),void*o):funcPtr(f),objPtr(o){}
    void(*funcPtr)(void*);
    void* objPtr;
};

class Caller
{
public:
    void addCall(Binder call) 
    {
        callbacks.push_back(call);
    }
    void callAll() 
    {
        for (auto& c: callbacks)
        {
            c.funcPtr(c.objPtr);
        }
    }
private:
    std::function<void(void)> fcnToCall;
    std::vector<Binder> callbacks;
};

int main()
{
    A a1;
    A a2;
    std::cout << "Starting:\n";
    std::cout << "A1: " << a1;
    std::cout << "A2: " << a2;

    Caller c;

    c.addCall( Binder( &incrementCountStatic , &a1) );
    c.addCall( Binder( &incrementCount2Static, &a2) );
    c.callAll();

    std::cout << "After Calls:\n";
    std::cout << "A1: " << a1;
    std::cout << "A2: " << a2;
    
    // A a1;
    // A a2;
    // Caller c1(std::bind(&A::incrementCount,&a1));
    // Caller c2(std::bind(&A::incrementCount,&a2));

    // std::cout << "Starting:\n";
    // std::cout << "A1: " << a1;
    // std::cout << "A2: " << a2;
    // c1.callYourThing();
    // std::cout << "A1: " << a1;
    // std::cout << "A2: " << a2;


    return 0;
}

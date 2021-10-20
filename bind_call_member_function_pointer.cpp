#include <iostream>
#include <functional>

class A 
{
public:
    friend std::ostream& operator<<(std::ostream& os, const A& a);
    A():count(0){}
    void incrementCount() {
        count++;
    }
private:
    int count;
};

std::ostream& operator<<( std::ostream& os, const A& a) 
{
    os << " count: " << a.count << "\n";
    return os;
}

class Caller
{
public:
    Caller(std::function<void(void)>fcn):fcnToCall(fcn){};
    void callYourThing(){fcnToCall();}
private:
    std::function<void(void)> fcnToCall;
};

int main()
{
    A a1;
    A a2;
    Caller c1(std::bind(&A::incrementCount,&a1));
    Caller c2(std::bind(&A::incrementCount,&a2));

    std::cout << "Starting:\n";
    std::cout << "A1: " << a1;
    std::cout << "A2: " << a2;
    c1.callYourThing();
    std::cout << "A1: " << a1;
    std::cout << "A2: " << a2;


    return 0;
}

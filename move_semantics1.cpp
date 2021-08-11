#include <iostream> 
#include <stdlib.h>
#include <iomanip>
#include <cstring>

class A
{
public:

    A() 
    : A(1)
    { }

    A(int i) 
    : generation{std::to_string(i)}
    , size{i}
    {
        std::cout << "A" << generation << " Constructor\n";
        m_vals = new int[size];
        for( int i = 0; i < size; ++i )
        {
            m_vals[i] = rand() % (max_val+1);
        }
    }

    ~A()
    {
        std::cout << "A" << generation << " Destructor\n";
        delete m_vals;
    }

    A(const A& a)
    : generation{a.generation + "_cp"}
    , size{a.size}
    {
        std::cout << "A" << generation << " Copy constructor \n";
        m_vals = new int[size];
        // for(int i = 0; i < size; ++i)
        // {
        //     m_vals[i] = a.m_vals[i];
        // }
        memcpy(m_vals, a.m_vals, size * sizeof(int));
    }
    // A(const A&& a)
    // {
    //     std::cout << "Move constructor\n";
    // }

    std::string generation;
    int* m_vals;
    int size;
    constexpr static int max_val = 99;
};

std::ostream& operator<<(std::ostream& out, const A& a)
{
    out << "            Object A" << a.generation << ": ";
    for( int i = 0; i < a.size-1; ++i)
    {
        out << std::setw(2) << a.m_vals[i] << " - ";
    }
    out << a.m_vals[a.size-1] << "\n";
    return out;
}

A gimmeA(int i)
{
    A localA(i);
    std::cout << localA;
    localA.m_vals[0] = 0;
    return localA;
}

int main()
{
    // A myA1;
    // std::cout << myA1;

    // A myA2(2);
    // std::cout << myA2;

    // A myA3(myA2);
    // std::cout << myA3;

    // // myA3.m_vals[0] = 0;
    // // std::cout << myA2;
    // // std::cout << myA3;


    // // A myA4 = myA3;
    // // myA4.m_vals[1] = 88;
    // // std::cout << myA4;
    // // std::cout << myA2;

    // // A myA4();
    // // myA4 = myA2;

    // A myA4(gimmeA(4));
    // std::cout << myA4;

    std::cout << gimmeA(6);
    std::cout << "bye\n";
    return 0;
}

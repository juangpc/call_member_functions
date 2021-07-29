#include <iostream>

template<typename T> 
void print(const T& t)
{
    std::cout << t << '\n';
}


int main()
{
    print(1);
    print("hello world!");
    print(5.23);

    return 0;
}
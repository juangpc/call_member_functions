#include <iostream>
#include <vector>
#include <cstdlib>

template < class T >
class MyAllocator
{
public:
    T * allocate(size_t size)
    {
        std::cout << "Allocation request size => " << size << std::endl;
        return new T[size];
    }
    void deallocate(T * p_t, size_t n)
    {
        std::free(p_t);
    }
    using value_type = T;
};

int main()
{
    std::vector <int, MyAllocator<int>> x;
    x.push_back(10);
    x.push_back(10);
    x.push_back(10);

    for (auto& var : x)
        std::cout << "Value " << var << std::endl;

}
#include "utils.hpp"

void initArrays(float* a, float* b, float* c, float* d, float al, float be)
{
    for( int i = 0; i < 8; i++) 
    {
        a[i] = al;
        b[i] = be;
        c[i] = i;
        d[i] = 0.0f;
    }
}

void show_results(const float* a, const float* b, const float* c, const float* d)
{
    std::ios oldstate(nullptr);
    oldstate.copyfmt(std::cout);
    std::cout << std::setfill(' ') << std::setw(3);

    std::cout << "a = [ " << std::setfill(' ') << std::setw(5) << a[0] << " ]";
    for( int i = 1; i < 8; i++)
    {
        std::cout << ", [ " << std::setfill(' ') << std::setw(5) << a[i] << " ]";
    }
    std::cout << "\n";

    std::cout << "b = [ " << std::setfill(' ') << std::setw(5) << b[0] << " ]";
    for( int i = 1; i < 8; i++)
    {
        std::cout << ", [ " << std::setfill(' ') << std::setw(5) << b[i] << " ]";
    }
    std::cout << "\n";
    std::cout << "c = [ " << std::setfill(' ') << std::setw(5) << c[0] << " ]";
    for( int i = 1; i < 8; i++)
    {
        std::cout << ", [ " << std::setfill(' ') << std::setw(5) << c[i] << " ]";
    }
    std::cout << "\n";
    std::cout << "d = [ " << std::setfill(' ') << std::setw(5) << d[0] << " ]";
    for( int i = 1; i < 8; i++)
    {
        std::cout << ", [ " << std::setfill(' ') << std::setw(5) << d[i] << " ]";
    }
    std::cout << "\n";

    std::cout <<"\n";
    std::cout.copyfmt(oldstate);
}

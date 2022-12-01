
#include <string>
#include <iostream>

#include "sequentialComputation.hpp"
#include "intrinsicsComputation.hpp"


#ifdef _MSC_VER
  #define ALIGN(n) declspec(align(n))
#else
  #define ALIGN(n) __attribute__ ((aligned(n)))
//   #define ALIGN(n)
#endif


int main(int argc, char** argv) 
{
    int numKRepetitions{0};

    if(argc != 2)
    {
        std::cout << "no args. setting it to 100\n";
        numKRepetitions = 100;
    } 
    else if (argc == 2)
    {
        int argIn{std::atoi(argv[1])};
        std::cout << ".using args. setting it to " << argIn << "\n";
        numKRepetitions = argIn;
    }

    ALIGN(32) float a[8];
    ALIGN(32) float b[8];
    ALIGN(32) float c[8];
    float d[8];

    float d2[8 * 2];
    for(int i = 0; i < 16; i++)
        d2[i] = 0.0f;

    unsigned long int head = (unsigned long int) &d2;
    int i = 0;
    for(; i < 8 * sizeof(float); i++)
    {
        if(((head + i) % 32) == 0)
            break;
    }
    float* d_aligned = (float*)(head+i);

    initArrays(a, b, c, d, 2.0f, 5.0f);
    std::cout << "\n";
    std::cout << "Executing sequential mode: \n";
    std::cout << "\n";

    testSequentialImplementation(numKRepetitions,a, b, c, d);

    initArrays(a, b, c, d, 2.0f, 5.0f);
    std::cout << "\n";
    std::cout << "Executing intrinsics: \n";
    std::cout << "\n";

    testIntrinsicsImplementation(numKRepetitions, a, b, c, d_aligned);
    
    std::cout << "head: " << (void*) head << "\n";
    std::cout << "\n";
    for(int i = 0; i < 16; i++)
        std::cout << "d2[" << i << "] = " << d2[i] << " - " << &d2[i] << "\n";
    std::cout << "\n";

    return EXIT_SUCCESS;
}


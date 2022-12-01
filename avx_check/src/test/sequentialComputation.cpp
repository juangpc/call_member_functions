#include "sequentialComputation.hpp"

void multiply_and_add(const float* a, const float* b, const float* c, float* d) 
{
  for(int i = 0; i < 8; i++) {
    d[i] = a[i] * b[i];
    d[i] = d[i] + c[i];
  }
}

void testSequentialImplementation(int numRepetitions, float* a, float* b, float* c, float* d)
{
    timer::time_point t1{timer::now()};

    for (int i = 0; i < numRepetitions; i++)
    {
        for(int j = 0; j < 1000; j++)
        {
            multiply_and_add(a, b, c, d);
        }
    }
    
    timer::time_point t2{timer::now()};

    float ops{2.0f * 8.0f * 1000.0f * static_cast<float>(numRepetitions)};
    float timeDiff{timer::diff(t1, t2)};
    float flops{ops/timeDiff * 1.0e6f};
    
    std::cout << "Num ops: " << ops << "\n";
    std::cout << "Duration: " << std::to_string(timeDiff * static_cast<float>(1.0e-6)) << " secs.\n";
    std::cout << "GFlops: " <<  std::to_string(flops * static_cast<float>(1.0e-9)) << "\n";
    std::cout << "\n";

    show_results(a, b, c, d);
}


#include "intrinsicsComputation.hpp"

// int checkIntrinsics()
// {
//     bool AVXsupported{false};
//     int cpuInfo[4] = {0, 0, 0, 0};
//     __cpuid(cpuInfo,0);
//     int nIds_ = cpuInfo[0];
    
//     __cpuidex(cpuInfo, 0, 0);
//     if(cpuInfo ^ BIT_avx )
// }

void intrinsicsComputation(const float* a, const float* b, const float* c, float* d)
{
    __m256 av = _mm256_loadu_ps(a);
    __m256 bv = _mm256_loadu_ps(b);
    __m256 cv = _mm256_loadu_ps(c);
    __m256 dv = _mm256_fmadd_ps(av, bv, cv);
    //  _mm256_storeu_ps(d,dv); //correct solution
    _mm256_storeu_ps(d, dv);
}

void testIntrinsicsImplementation(int numRepetitions, float* a, float* b, float* c, float* d)
{
    std::cout << "starting intrinsics!\n";

    timer::time_point t1{timer::now()};

    for (int i = 0; i < numRepetitions; i++)
    {
        for(int j = 0; j < 1000; j++)
        {
            intrinsicsComputation(a, b, c, d);
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
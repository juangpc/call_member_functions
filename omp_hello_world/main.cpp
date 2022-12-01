#include <iostream>
#include <thread>
#include <chrono>
#include <omp.h>

#include "timetracer.hpp"


int main()
{
    TIME_TRACER_ENABLE("test1.json");

    omp_set_num_threads(2);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            TIME_TRACE("section1");
            std::cout << "1";
            std::this_thread::sleep_for(std::chrono::seconds(1));

        }
        #pragma omp section 
        {
            TIME_TRACE("section2");
            std::cout << "2";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        

    }
    std::cout << "\n";
    
    TIME_TRACER_DISABLE;
}

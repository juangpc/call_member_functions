#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "TutorialConfig.h"

#ifdef USE_MYMATH
    #include "MathFunctions.h"
#else 
    #include <cmath>
#endif


int main(int argc, char* argv[]) {
    std::cout << "Hello, Cmake!" << "\n\n";

    if (argc < 2) {
        // report version
        std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
                  << Tutorial_VERSION_MINOR << "." << Tutorial_VERSION_PATCH << "\n\n";
        std::cout << "Usage: " << argv[0] << " number" << "\n\n";
    }
    else if(argc == 3)
    {
        const double inputValue = std::atof(argv[1]);
        const int num_iters = std::atoi(argv[2]);
        
        #ifdef USE_MYMATH
            const double outputValue = mysqrt(inputValue, num_iters);
        #else
            const double outputValue = sqrt(inputValue); 
        #endif

        std::cout <<">>> The square root of " << inputValue << " is " << std::setprecision(20) << outputValue << "\n\n";
    }

    return 0;
}

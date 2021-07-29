#include <iostream>
#include <iomanip>

double mysqrt(double x, int num_iters)
{
    double result{0.};

    if (x > 0.)
    {
        for (int i = 0; i < num_iters; ++i)
        {
            if (result <= 0.)
            {
                result = 0.1;
            }
            double delta = x - (result * result);
            result = result + 0.5 * delta / result;
            std::cout << "Iteration: " << i+1 << "\t - Computing sqrt of " << x << " to be " << std::setprecision(20) << result << "\n";
        }
    }
    return result;
}


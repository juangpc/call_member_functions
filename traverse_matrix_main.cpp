#include <iostream>
#include <iomanip>
#include <chrono>

void initMatrix(float* m, float* m2, int size) {
    float counter = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            m [i*size + j] = counter;
            m2[j*size + i]= counter++;
        }
    }
}

void displayMatrix(float* m, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            std::cout << std::setfill('0') << std::setw(2) << m[i*size + j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void displayMatrixTraverse(float* m, int size) {
    for(int i = 0; i < size * size; i++) {
        std::cout << m[i] << "\n";
    }
}

void traverseM(float* m, float* m2, float* t, int size) {

    int tIndex = 0;

    for (int circ = 0; circ < size/2; circ++)
    {   
        {
            int i = circ;
            int j = circ;
            for(; j < size - i; j++) 
            {
                // std::cout << "m[" << i << "," << j << "] = " << m[i*size + j] << "\n"; 
                t[tIndex++] = m[i*size + j];
            }
            //std::cout << " -- \n";
        }
        { 
            int i = circ + 1;
            int j = size - circ - 1; 
            for(; i < size - circ; i++) 
            {
                // std::cout << "m[" << i << "," << j << "] = " << m[i*size + j] << "\n"; 
                t[tIndex++] = m[i*size + j];
                //t[tIndex++] = m2[j*size + i];
            }
            //std::cout << " -- \n";
        }
        { 
            int i = size - circ - 1;
            int j = size - 2 - circ; 
            for(; j > circ - 1; j--) 
            {
                // std::cout << "m[" << i << "," << j << "] = " << m[i*size + j] << "\n"; 
                t[tIndex++] = m[i*size + j];
            }
            // std::cout << " -- \n";
        }
        { 
            int i = size - circ - 2;
            int j = circ; 
            for(; i > circ; i--) 
            {
                // std::cout << "m[" << i << "," << j << "] = " << m[i*size + j] << "\n"; 
                t[tIndex++] = m[i*size + j];
                // t[tIndex++] = m2[j*size + i];
            }
            // std::cout << " -- \n";
        }
    }
}


int main() {
    for (int N = 4; N < 4000; N = N + 30)
    {
        float* m  = new float[N * N];
        float* m2 = new float[N * N];
        float* mt = new float[N * N];

        initMatrix(m, m2, N);

        // displayMatrix(m, N);

        //displayMatrix(m2,N);
        auto startTime = std::chrono::high_resolution_clock::now();
        traverseM(m, m2, mt, N);
        auto endTime = std::chrono::high_resolution_clock::now();

        std::cout << "time for N = " << N << " is: " << std::chrono::duration<double, std::milli>
            (endTime - startTime).count() << "\n";

        // displayMatrixTraverse(mt,N);

        delete [] m;
        delete [] m2;
        delete [] mt;
    }

    return EXIT_SUCCESS;
}

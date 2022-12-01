
clang++ main.cpp timetracer.cpp -o out -std=c++11 -DTRACE -Xpreprocessor -fopenmp -I/usr/local/Cellar/libomp/14.0.5/include -lomp

-
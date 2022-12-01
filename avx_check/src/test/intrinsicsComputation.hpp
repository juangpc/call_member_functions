#pragma once

#include <iostream>

#include <cpuid.h>
#include <immintrin.h>
#include "timer.hpp"
#include "utils.hpp"

void intrinsicsComputation(const float* a, const float* b, const float* c, float* d);
void testIntrinsicsImplementation(int numRepetitions, float* a, float* b, float* c, float* d);

// int checkIntrinsics();
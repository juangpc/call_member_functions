#pragma once

#include <chrono>



namespace timer {

using time_point = std::chrono::time_point<std::chrono::steady_clock>;


inline time_point now()
{
    return std::chrono::steady_clock::now();
} 


template <typename T>
inline float diff(const time_point& a, const time_point& b)
{
    return static_cast<float>( \
        std::chrono::duration_cast<T> \
        (b - a).count() \
        );
}

inline float diff(const time_point& a, const time_point& b)
{
    return diff<std::chrono::microseconds>(a,b);
}

}//timer namespace

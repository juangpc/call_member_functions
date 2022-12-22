#include "calls.hpp"
#include <iostream>

namespace calls {
  
void callback1(int a) 
{
  std::cout << "Hello from callback1! with input "<< a << "\n"; 
}

void callback2(int a)
{
  std::cout << "Hello from callback2! with input "<< a << "\n"; 
}

void callback3(int a)
{
  std::cout << "Hello from callback3! with input "<< a << "\n"; 
}

}


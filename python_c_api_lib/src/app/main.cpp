
#include <iostream>
#include "calls.hpp"

int main() {
  
  std::cout << "Starting main app.\n";

  calls::callback1(1);
  calls::callback2(2);
  calls::callback3(3);

  return EXIT_SUCCESS;
}


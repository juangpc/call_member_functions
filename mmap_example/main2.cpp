#include "timetracer.hpp"

#include <iostream>
#include <string>
#include <ctime>

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

std::string randString(size_t len);


void multiplyby3(float* addr, size_t len);
void populateArray(float* addr, size_t len);


std::string randString(size_t len)
{
  static bool seed_rand = false;
  if(!seed_rand)
  {
    std::srand(std::time(0));
  }

  std::string out;

  for (size_t i = 0; i < len; ++i)
  {
    out += std::rand() % 26 + 'A' + rand() % 2 * 32;
  }
  
  return out;
}


void multiplyby3(float* addr, size_t len)
{
  TIME_TRACE();
  for (size_t i = 0; i < len; ++i)
  {
    addr[i] *= 3.f;
  }
}
void populateArray(float* addr, size_t len)
{
  TIME_TRACE();

  for (size_t i = 0; i < len; ++i)
  {
    // TIME_TRACE_VALUE("populate_i");
    addr[i] = static_cast<float>(i);
  }
}

int main(int argc, char* argv[])
{
  size_t length = 1000;

  if(argc >= 2){
    length = std::stoi(argv[1]);
  }

  std::cout << "Running with array length " << length << ".\n";
  auto randName = randString(12);

  TIME_TRACER_ENABLE(randName + "_len" +  std::to_string(length) + "_trace.json");

  auto tempfileName = randName + "_len" + std::to_string(length) + ".data";
  
  int fd = mkstemp(tempfileName.data());
  ftruncate(fd, length * sizeof(float));

  void* mem = mmap( NULL, length * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
  
  if(mem == MAP_FAILED){
    std::cout << "Unable to map memory.\n";
    return 1;
  }

  close(fd);

  float* arr = nullptr;
  {
    {
      TIME_TRACE("allocating array");
      arr = new float[length]; 
    }
    TIME_TRACE("dealing with unmapped array");
    populateArray(arr, length);
    multiplyby3(arr, length);
  }
  {
    TIME_TRACE("dealing with unmapped array again");
    populateArray(arr, length);
    multiplyby3(arr, length);
  }

  {
    TIME_TRACE("dealing with populating mapped memory");  
    populateArray(static_cast<float*>(mem), length);
    multiplyby3(static_cast<float*>(mem), length);
  }
    {
    TIME_TRACE("dealing with populating mapped memory again");  
    populateArray(static_cast<float*>(mem), length);
    multiplyby3(static_cast<float*>(mem), length);
  }
  {
    TIME_TRACE("unmapping");
    munmap(mem, length * sizeof(int));
  }



  delete[] arr;

  TIME_TRACER_DISABLE;

  return 0;

}

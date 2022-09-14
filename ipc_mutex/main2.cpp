
#include <iostream>
#include "sharedMemoryGoodies.hpp"
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <unistd.h>
#include <iomanip>
#include <ctime>
#include <atomic>

using time_stamp = std::chrono::time_point<std::chrono::system_clock,
                                           std::chrono::microseconds>;

struct Data { 
    // std::mutex mtx;
    int a = 15;
    time_stamp now;
};

using atomicData = std::atomic<Data>;

int main(int argc, char** argv) {

    SharedMemAddress shm = getShmAddressForId("14", 2048);

    atomicData* dptr = (atomicData*) shm.shm_addr;
    Data d;

    for(;;) {
        d = dptr->load();
        // std::time_t t_c = std::chrono::system_clock::to_time_t(d.now);
        // std::cout << "time: " << std::put_time(std::localtime(&t_c),"%F %T.\n") << std::flush;
        std::cout << "time: " << dptr->load().now.time_since_epoch().count() << "\n" <<std::flush;
        // dptr->mtx.unlock();
        usleep(std::stoi(argv[1]));    
    }

    return EXIT_SUCCESS;
}


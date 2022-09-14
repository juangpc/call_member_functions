
#include <iostream>
#include "sharedMemoryGoodies.hpp"
#include <chrono>
#include <mutex>
#include <condition_variable>
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


int main() {

    SharedMemAddress shm = createShmAddressForId("14", 2048);

    atomicData data;
    atomicData* dptr;

    memcpy(shm.shm_addr, &data, sizeof(atomicData));
    dptr = (atomicData*) shm.shm_addr;

    for(;;) {
        // dptr->mtx.lock();
        Data newData;
        newData.now = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
        dptr->store(newData);
        // dptr->mtx.unlock();

        // std::time_t t_c = std::chrono::system_clock::to_time_t(dptr->load().now);
        // auto nowy = std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds-duration>
        std::cout << "time: " << dptr->load().now.time_since_epoch().count() << "\n" <<std::flush;
        //std::cout << "updating time...: " << std::put_time(std::localtime(dptr->now),"%F %T.\n") << std::flush;
        sleep(5);
    }
    
    shmctl(shm.shm_id, IPC_RMID, nullptr);

    return EXIT_SUCCESS;
}

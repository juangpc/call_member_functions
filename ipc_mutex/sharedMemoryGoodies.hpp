#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>

struct SharedMemAddress { 
key_t shm_key;
int shm_id;
void* shm_addr;
};

SharedMemAddress createShmAddressForId(const char* id, size_t size) {
    SharedMemAddress shMemAddr;

    shMemAddr.shm_key = ftok(id, 0);

    shMemAddr.shm_id = shmget(shMemAddr.shm_key, size, IPC_CREAT | SHM_R | SHM_W);

    shMemAddr.shm_addr = shmat(shMemAddr.shm_id, nullptr, 0);

    return shMemAddr;
}

SharedMemAddress getShmAddressForId(const char* id, size_t size) {

    SharedMemAddress shMemAddr;

    shMemAddr.shm_key = ftok(id, 0);

    shMemAddr.shm_id = shmget(shMemAddr.shm_key, size, SHM_R | SHM_W);

    shMemAddr.shm_addr = shmat(shMemAddr.shm_id, nullptr, 0);

    return shMemAddr;
}

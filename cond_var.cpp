#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable condVar;
std::string data;
bool continueRunning = true;
bool workToBeDone = false;
bool readyForNewWork = false;

void wakerThread()
{
    std::cout << "\t\t\t\t\tentering worker thread.\n";

    int sleepTimes[] = {4,3,2,5,2,10,3,20};
    for(int i = 0; i < 8; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(sleepTimes[i]+2));
        {
            std::unique_lock<std::mutex> lock(mutex);
            condVar.wait(lock, [] {
                std::cout << "\t\t\t\t\tchecking readyForNewWork in thread.\n";
                std::cout << "readyForNewWork = " << readyForNewWork << "\n";
                return readyForNewWork;
            });

            workToBeDone = true;
            std::cout << "\t\t\t\t\tworkToBeDone = " << workToBeDone << "\n";
            std::cout << "\t\t\t\t\tnotifying from thread.\n";
            condVar.notify_one();
        }
    }
}

void closeMainLoop()
{
    std::cout << "Entering closer thread\n";
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << "Changing value of continue running in closer thread\n";
    continueRunning = false;
    std::cout << "continueRunning = " << continueRunning << "\n";
}

int main()
{
    std::cout << "Current process: " << ::getpid() << "\n";
    std::thread closer(closeMainLoop);
    std::thread worker(wakerThread);

    std::cout << "changing value of readyForNewWork in main\n";
    readyForNewWork = true;
    std::cout << "readyForNewWork = " << readyForNewWork << "\n";
    std::cout << "notifying from main.\n";
    condVar.notify_one();
    while(continueRunning)
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            condVar.wait(lock, []{
                std::cout << "checking workToBeDone in main.\n";
                std::cout << "workToBeDone = " << workToBeDone << "\n";
                return workToBeDone;
            });

            readyForNewWork = false;
            std::cout << "Processing events";
            for(int i = 0; i < 10; ++i)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << ".";
            }
            std::cout << "done.\n\n";
            workToBeDone = false;
            readyForNewWork = true;
            std::cout << "workToBeDone = " << workToBeDone << "\n";
            std::cout << "readyForNewWork = " << readyForNewWork << "\n";
            std::cout << "Notifying from main.\n";
            condVar.notify_one();
        }
    }


    std::cout << "Back in main(), closing. bye bye...\n";

    closer.join();
    worker.join();

    return 0;
}
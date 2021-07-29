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

std::mutex mtx_cout;

// Asynchronous output
struct acout
{
    std::unique_lock<std::mutex> lk;
    acout()
    :lk(std::unique_lock<std::mutex>(mtx_cout))
    { }

    template<typename T>
    acout& operator<<(const T& _t)
    {
        std::cout << _t;
        return *this;
    }

    acout& operator<<(std::ostream& (*fp)(std::ostream&))
    {
        std::cout << fp;
        return *this;
    }
};

void wakerThread()
{
    acout() << "\t\t\t\t\tentering worker thread.\n";

    int sleepTimes[] = {4000,3000,200,500,200,10,3000,20000};
    for(int i = 0; i < 8; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds (sleepTimes[i]));
        {
            std::unique_lock<std::mutex> lock(mutex);
            condVar.wait(lock, [] {
                acout() << "\t\t\t\t\tchecking readyForNewWork in thread.\n";
                acout() << "\t\t\t\t\treadyForNewWork = " << readyForNewWork << "\n";
                return readyForNewWork;
            });

            workToBeDone = true;
            acout() << "\t\t\t\t\tworkToBeDone = " << workToBeDone << "\n";
            acout() << "\t\t\t\t\tnotifying from thread.\n";
            condVar.notify_all();
        }
    }
    continueRunning = false;
}

//void closeMainLoop()
//{
//    acout() << "Entering closer thread\n";
//    std::this_thread::sleep_for(std::chrono::seconds(60));
//    acout() << "Changing value of continue running in closer thread\n";
//    continueRunning = false;
//    acout() << "continueRunning = " << continueRunning << "\n";
//}

void printTime()
{
    while(continueRunning)
    {
        acout() << ".\n" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    acout() << "Current process: " << ::getpid() << "\n";
//    std::thread closer(closeMainLoop);
    std::thread worker(wakerThread);
    std::thread timePrinter(printTime);

    acout() << "changing value of readyForNewWork in main\n";
    readyForNewWork = true;
    acout() << "readyForNewWork = " << readyForNewWork << "\n";
    acout() << "notifying from main.\n";
    condVar.notify_all();
    while(continueRunning)
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            condVar.wait(lock, []{
                acout() << "checking workToBeDone in main.\n";
                acout() << "workToBeDone = " << workToBeDone << "\n";
                return workToBeDone;
            });

            readyForNewWork = false;
            acout() << "Processing events";
            for(int i = 0; i < 10; ++i)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                acout() << ".";
            }
            acout() << "done.\n\n";
            workToBeDone = false;
            readyForNewWork = true;
            acout() << "workToBeDone = " << workToBeDone << "\n";
            acout() << "readyForNewWork = " << readyForNewWork << "\n";
            acout() << "Notifying from main.\n";
            condVar.notify_all();
        }
    }


    acout() << "Back in main(), closing. bye bye...\n";

//    closer.join();
    worker.join();
    timePrinter.join();

    return 0;
}
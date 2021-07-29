#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

long long int a = 0;
long long int b = 0;
long long int c = 0;
long long int d = 0;
int ii = 0;
std::mutex iMutex;

void generateRandNums(int* v, int num)
{
    for (int i = 0; i < num; ++i)
    {
        v[i] = rand() % 20 + 1;
//        std::cout << "Random : " << v[i] << "\n";
    }
}

void increment(long long int& a)
{
    a++;
}

void safe_increment(int* v)
{
    int t(0);
    for (int j = 0; j < 10; ++j)
    {
        {
            const std::lock_guard<std::mutex> lock(iMutex);
            t = v[ii++]; std::this_thread::sleep_for(std::chrono::milliseconds (t));
            increment(a);
            t = v[ii++]; std::this_thread::sleep_for(std::chrono::milliseconds (t));
            increment(c);

            std::cout << "in thread # " << std::this_thread::get_id() << " - mult&subtract: " << a*b-c*d << " - after sleeping for: "
                      << t << " ms\n" << std::flush;

            t = v[ii++]; std::this_thread::sleep_for(std::chrono::milliseconds (t));
            increment(b);
            t = v[ii++]; std::this_thread::sleep_for(std::chrono::milliseconds (t));
            increment(d);

        }
    }
}

int main()
{
    std::cout << "Size of i is: " << sizeof(a) << "\n";
    srand(time(0));
    int* v = new int(200);
    generateRandNums(v,200);
    std::cout << "in thread # " << std::this_thread::get_id() << " - mult&subtract: " << a*b-c*d << "\n";


    std::thread t2(safe_increment, std::ref(v));
    std::thread t3(safe_increment, std::ref(v));
    std::thread t4(safe_increment, std::ref(v));
    std::thread t5(safe_increment, std::ref(v));
    std::thread t6(safe_increment, std::ref(v));

    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    std::cout << "in thread # " << std::this_thread::get_id() << " - mult&subtract: " << a*b-c*d << "\n";

    return 0;
}

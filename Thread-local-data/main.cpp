#include <iostream>
#include <random>
#include <thread>


using namespace std;
thread_local std::mt19937 mt;

void func() {
    std::uniform_real_distribution<double> dist(0,1);
    for (int i = 0; i < 10; ++i) {
        std::cout << dist(mt) << ", ";
    }
}

int main()
{
    cout << "Hello Thread Local Data lesson !" << endl;
    std::cout << "Thread 1's random values: \n";
    std::thread thr1(func);
    thr1.join();

    std::cout <<"\nThread 2's randm values: \n";
    std::thread thr2(func);
    thr2.join();
    return 0;
}

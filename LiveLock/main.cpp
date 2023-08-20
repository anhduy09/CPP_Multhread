#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

std::mutex mut1, mut2;

void funcA() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    bool locked = false;
    while (!locked) {
        std::lock_guard<std::mutex> lck_guard(mut1); //lock mut1
        std::cout << "After you, Claude!\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        locked = mut2.try_lock();
    }
    if(locked == true) {
        std::cout << "ThreadA has locked both mutexes\n";
    }
}

void funcB() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    bool locked = false;
    while (!locked) {
        std::lock_guard<std::mutex> lck_guard(mut2); //lock mut1
        std::cout << "After you, Duy!\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        locked = mut1.try_lock();
    }
    if(locked == true) {
        std::cout << "ThreadB has locked both mutexes\n";
    }

}

int main()
{
    cout << "Hello LiveLock!" << endl;
    std::thread thrA(funcA), thrB(funcB);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    thrA.join(); thrB.join();

    return 0;
}

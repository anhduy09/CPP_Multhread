// require C++17 compiler
#include <iostream>
#include <thread>
#include <mutex>


using namespace std;

std::mutex mt1, mt2;

void funcA() {
    std::unique_lock<std::mutex> uniq_lk1(mt1, std::defer_lock);    // associate with the lock ...
    std::unique_lock<std::mutex> uniq_lk2(mt2, std::defer_lock);    //... but don't lock it yet


    std::cout << " Thread A trying to lock mutexes 1 and 2 ....\n";

    std::lock(uniq_lk1,uniq_lk2);     // Now lock both of them
    std::cout << "Thread A has locked mutex 1 and 2\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout <<  "Thread A releases mutexes 1 and 2 ....\n";
}

void funcB() {
    std::unique_lock<std::mutex> uniq_lk1(mt1, std::defer_lock);
    std::unique_lock<std::mutex> uniq_lk2(mt2, std::defer_lock);


    std::cout << " Thread B trying to lock mutexes 1 and 2 ....\n";

    std::lock(uniq_lk1,uniq_lk2);     //lock both mutexes
    std::cout << "Thread B has locked mutex 1 and 2\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout <<  "Thread B releases mutexes 1 and 2 ....\n";
}

int main()
{
    cout << "Hello DeadLock Avoidance Defer!" << endl;
    std::thread thrA(funcA), thrB(funcB);
    thrA.join(); thrB.join();
    return 0;
}

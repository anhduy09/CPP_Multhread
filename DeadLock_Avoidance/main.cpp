// require C++17 compiler
#include <iostream>
#include <thread>
#include <mutex>


using namespace std;

std::mutex mt1, mt2;

void funcA() {
    std::cout << " Thread A trying to lock mutexes 1 and 2 ....\n";
    std::scoped_lock scoped_lck(mt1, mt2);
    std::cout << "Thread A has locked mutex 1 and 2\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout <<  "Thread A releases mutexes 1 and 2 ....\n";
}

void funcB() {
    std::cout << " Thread B trying to lock mutexes 1 and 2 ....\n";
    std::scoped_lock scoped_lck(mt1, mt2);
    std::cout << "Thread B has locked mutex 1 and 2\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout <<  "Thread B releases mutexes 1 and 2 ....\n";
}

int main()
{
    cout << "Hello DeadLock Avoidance!" << endl;
    std::thread thrA(funcA), thrB(funcB);
    thrA.join(); thrB.join();
    return 0;
}

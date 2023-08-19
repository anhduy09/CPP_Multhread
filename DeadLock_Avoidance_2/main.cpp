// require C++17 compiler
#include <iostream>
#include <thread>
#include <mutex>


using namespace std;

std::mutex mt1, mt2;

void funcA() {
    std::cout << " Thread A trying to lock mutexes 1 and 2 ....\n";
    std::lock(mt1,mt2);     //lock both mutexes
    std::cout << "Thread A has locked mutex 1 and 2\n";

    //adopt locks
    std::unique_lock<std::mutex> uniq_lk1(mt1, std::adopt_lock); // associate each mutex with unique_lock
    std::unique_lock<std::mutex> uniq_lk2(mt2, std::adopt_lock);
    std::cout << "Thread A has adopted locks\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout <<  "Thread A releases mutexes 1 and 2 ....\n";
}

void funcB() {
    std::cout << " Thread B trying to lock mutexes 1 and 2 ....\n";
//    std::scoped_lock scoped_lck(mt1, mt2);

    std::lock(mt1,mt2);
    std::cout << "Thread B has locked mutex 1 and 2\n";

    //adopt locks
    std::unique_lock<std::mutex> uniq_lk1(mt1, std::adopt_lock); // associate each mutex with unique_lock
    std::unique_lock<std::mutex> uniq_lk2(mt2, std::adopt_lock);
    std::cout << "Thread B has adopted locks\n";


    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout <<  "Thread B releases mutexes 1 and 2 ....\n";
}

int main()
{
    cout << "Hello DeadLock Avoidance Adopting!" << endl;
    std::thread thrA(funcA), thrB(funcB);
    thrA.join(); thrB.join();
    return 0;
}

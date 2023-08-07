#include <iostream>
#include <mutex>
#include <thread>


using namespace std;

std::mutex mt1;
std::mutex mt2;

void funcA() {
    std::cout << "Thread A is trying to lock mutex 1...\n";
    std::lock_guard<std::mutex> lck_guard(mt1);
    std::cout <<  "Thread A has locked mutex 1\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread A is trying to lock mutex 2...\n";
    std::lock_guard<std::mutex> lck_guard2(mt2);
    std::cout <<  "Thread A has locked mutex 2\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread A release all locks\n";
}

void funcB() {
    std::cout << "Thread B is trying to lock mutex 2...\n";
    std::lock_guard<std::mutex> lck_guard2(mt2);
    std::cout <<  "Thread B has locked mutex 2\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread B is trying to lock mutex 1...\n";
    std::lock_guard<std::mutex> lck_guard(mt1);
    std::cout <<  "Thread B has locked mutex 1\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread B release all locks\n";
}

void funcC() {
    std::cout << "Thread C is trying to lock mutex 2...\n";
    std::lock_guard<std::mutex> lck_guard(mt2);
    std::cout <<  "Thread C has locked mutex 2\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread C is trying to lock mutex 1...\n";
    std::lock_guard<std::mutex> lck_guard2(mt1);
    std::cout <<  "Thread C has locked mutex 1\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread C release all locks\n";
}

void funcD() {
    std::cout << "Thread D is trying to lock mutex 2...\n";
    std::lock_guard<std::mutex> lck_guard2(mt2);
    std::cout <<  "Thread D has locked mutex 2\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread D is trying to lock mutex 1...\n";
    std::lock_guard<std::mutex> lck_guard(mt1);
    std::cout <<  "Thread D has locked mutex 1\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Thread D release all locks\n";
}

int main()
{
    cout << "Hello Deadlock!" << endl;
//    std::thread thrA(funcA);
//    std::thread thrB(funcB);
//    thrA.join(); thrB.join();
    std::thread thrC(funcC);
    std::thread thrD(funcD);
    thrC.join(); thrD.join();
    return 0;
}

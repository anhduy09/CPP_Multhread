#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

std::mutex mut;

//share variable
int x = 0;

void write() {
    std::lock_guard<std::mutex> lck_guard(mut);

    //start of critical section
    ++x;
    //end of critical section

}

void read() {
    std::lock_guard<std::mutex> lck_guard(mut);

    //start of critical section
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout<<x<<"\n";
    //end
}

int main()
{
    std::vector<std::thread> threads;

    for (int i =0; i < 20; ++i) {
        threads.push_back(std::thread(read));
    }
    threads.push_back(std::thread(write));
    threads.push_back(std::thread(write));

    for (int i = 0; i < 20; ++i) {
        threads.push_back(std::thread(read));
    }

    for (auto& thr : threads) {
        thr.join();
    }
    return 0;
}

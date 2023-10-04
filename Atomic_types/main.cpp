#include <iostream>
#include  <thread>
#include <vector>
#include <mutex>
#include <atomic>


using namespace std;
//std::mutex mut;
std::atomic<int> counter(0);

void task() {
    for (int i = 0; i < 100000; ++i) {
        //std::lock_guard<mutex> lck(mut);
        ++counter;
    }
}

int main()
{
    cout << "Hello Integer Operation and Threads!" << endl;
    std::vector<std::thread> tasks;
    for (int i = 0; i< 10; ++i) {
        tasks.push_back(std::thread(task));
    }

    for (auto& thr: tasks) {
        thr.join();
    }
    std::cout <<counter <<"\n";

    return 0;
}

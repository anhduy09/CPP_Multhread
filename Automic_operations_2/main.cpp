#include <iostream>
#include  <thread>
#include <vector>
#include <mutex>
#include <atomic>


using namespace std;
//std::mutex mut;
//std::atomic<int> counter(0);
std::atomic_flag lock_cout = ATOMIC_FLAG_INIT;

void task(int n) {
    //test_and_set()
    //Returns true if another thread set the flag
    //Returns false if this thread set the flag
    while(lock_cout.test_and_set()) {

    }

    //start of critical section
    //do some work
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "I'm a task with argument "<<n<<'\n';
    //End of critical section

    //clear the flag, so another thread can set it
    lock_cout.clear();
}

int main()
{
    cout << "Hello Automic operations" << endl;
    std::vector<std::thread> tasks;
    for (int i = 0; i< 10; ++i) {
        tasks.push_back(std::thread(task,i));
    }

    for (auto& thr: tasks) {
        thr.join();
    }
    //std::cout <<counter <<"\n";

    return 0;
}

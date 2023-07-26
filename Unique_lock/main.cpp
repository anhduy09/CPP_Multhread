#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
std::mutex print_mutex;

void task(std::string str) {
    for (int i = 0; i<5; ++i) {
        //create an std::unique_lock object
        //this calls print_mutex.lock()
        std::unique_lock<std::mutex> unq_lck(print_mutex);

        std::cout << str[0]<<str[1]<<str[2]<<std::endl;

        //unq_lck.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }
}

int main()
{
    std::thread t1(task,"anh");
    std::thread t2(task, "duy");
    std::thread t3(task, "taa");

    t1.join();t2.join();t3.join();
    return 0;
}

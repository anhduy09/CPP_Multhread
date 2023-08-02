#include <iostream>
#include "singleton.h"
#include <vector>
#include <thread>



using namespace std;

void task() {
    Singleton* single = Singleton::get_Singleton();
    std::cout << single <<std::endl;
}


int main()
{
    cout << "Share Data Initialization" << endl;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(task));
    }

    for (auto& thr: threads)
        thr.join();


    return 0;
}

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;

class Test {
    //....
public:
    void func() {

    }
};

std::atomic<Test*> ptest(nullptr); // variable to be lazily initialize
std::mutex mut;

void process() {
    //First check of ptest
    if(!ptest) {
        std::lock_guard<std::mutex> lck_guard(mut);

        //second check of ptest
        if(!ptest) {
            //Initialize ptest
            ptest = new Test();

        }
    }

    //Atomic pointers cannot be deferenced
    // Copy it to a non-atomic pointer first
    Test* ptr_test = ptest;
    ptr_test->func();
}

int main()
{
    cout << "Hello World!" << endl;
    std::vector<std::thread> tasks;
    for (int i = 0; i< 10; ++i) {
        tasks.push_back(std::thread(process));
    }

    for (auto& thr: tasks) {
        thr.join();
    }
    return 0;
}

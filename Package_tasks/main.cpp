#include <iostream>
#include <future>
#include <thread>

using namespace std;

int main()
{
    cout << "Hello Package Task!" << endl;
    //Packaged task obkject
    //The callable object is a lamda expression
    // It takes int and int arguments
    // It returns int
    std::packaged_task<int(int,int)> pTask([](int a, int b) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return a+b;
    });

    std::future<int> fut = pTask.get_future();

    //Invok the packaged task in this thread
    //pTask(10,20);

    //cout << fut.get();

    //Create a thread
    //The package task will be its entry point
    std::thread thr(std::move(pTask), 10, 20);
    thr.join();
    cout << fut.get();
    return 0;
}

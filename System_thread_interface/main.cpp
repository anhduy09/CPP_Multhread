#include <iostream>
#include <thread>
using namespace std;

void hello() {
    std::cout <<  "hello system thread interface"<<std::endl;
}

void helloThreadID() {
    std::cout<< "Hello from thread with ID "<<std::this_thread::get_id()<<std::endl;
}

void helloWithSleep() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"hello thread with sleep "<<std::endl;
}

int main()
{
    std::thread thr(hello);

    //Display the child thread's native handle
    std::cout<<"hello thread has native handle "<<thr.native_handle()<<std::endl;

    //wait for thread complete
    thr.join();

    //one more time
    std::cout<<"hello thread has native handle "<<thr.native_handle()<<std::endl;

    //-----------------------------------
    std::cout<<"Main thread's ID "<<std::this_thread::get_id()<<std::endl;
    std::thread thr1(helloThreadID);
    std::cout<<"Hello thread has ID "<<thr1.get_id()<<std::endl;
    thr1.join();
    //again
    std::cout<<"Hello thread has ID "<<thr1.get_id()<<std::endl;
    //------------------------------------
    std::cout<<"Starting thread.............."<<std::endl;
    std::thread thr2(helloWithSleep);
    thr2.join();
    return 0;
}

#include <iostream>
#include <mutex>
#include <thread>


using namespace std;
std::mutex task_mutex;

void task(const std::string& str) {
    for (int i = 0; i < 6; ++i) {
        try {
            //lock the mutex
            task_mutex.lock();
            //start of critical section
            std::cout<<str[0]<<str[1]<<str[2]<<std::endl;
            //critical section throws an exception
            throw std::exception();

            //never gets called
            task_mutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(40));
        }  catch (std::exception& e) {
            std::cout<<"Exception caught: "<<e.what()<<"\n";
        }
    }
}

void task_lock_guard(const std::string& str) {
//    for (int i = 0; i < 5; ++i) {
//        // create an std:;lock_guard object
//        //this calls task_mutext.lock()
//        std::lock_guard<std::mutex> lck_guard(task_mutex);

//        //critical section
//        std::cout<<str[0]<<str[1]<<str[2]<<std::endl;
//        //end of critical section

//    }//calls ~std::lock_guard

    for (int i = 0; i < 6; ++i) {
        try {
            //lock the mutex
            std::lock_guard<std::mutex> lck_guard(task_mutex);
            //start of critical section
            std::cout<<str[0]<<str[1]<<str[2]<<std::endl;
            //critical section throws an exception
            throw std::exception();
            std::this_thread::sleep_for(std::chrono::milliseconds(40));
        }  catch (std::exception& e) {
            std::cout<<"Exception caught: "<<e.what()<<"\n";
        }
    }
}

int main()
{
    std::thread t1(task_lock_guard,"anh");
    std::thread t2(task_lock_guard, "duy");
    std::thread t3(task_lock_guard, "taa");

    t1.join();t2.join();t3.join();
    return 0;
}

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
std::mutex task_mutex;

void task(const std::string& str)
{
    for (int i=0; i<5; ++i) {
        //lock the mutext before the critical sectio
        task_mutex.lock();

        //start of critical section
        std::cout<<str[0]<<str[1]<<str[2]<<std::endl;
        //end of critical section

        //unlock the mutext after the critical section
        task_mutex.unlock();
    }
}

void task1() {
    std::cout<<"Task1 trying to lock the mutex"<<std::endl;
    task_mutex.lock();
    std::cout <<"Task1 has locked the mutex"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout <<"Task1 unlocking the mutex"<<std::endl;
    task_mutex.unlock();
}

void task2() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Task2 trying to lock the mutex"<<std::endl;
    while (!task_mutex.try_lock()) {
        std::cout << "Task2 could not to lock the mutex"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Task2 has locked the mutex"<<std::endl;
    task_mutex.unlock();
}

int main()
{
//    std::thread thr1(task,"anh");
//    std::thread thr2(task,"duy");
//    std::thread thr3(task,"abc");

//    //    //wait for the tasks to complete
//    thr1.join();
//    thr2.join();
//    thr3.join();

    std::thread thr4(task1);
    std::thread thr5(task2);

    thr4.join();
    thr5.join();
    return 0;
}

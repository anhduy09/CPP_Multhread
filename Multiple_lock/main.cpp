#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rmut;
std::timed_mutex tmut;


int bad_factorial(int n)
{
    if (n <= 1) {
        std::cout << "Returning "<<1<<"\n";
        return 1;
    }

    std::lock_guard<std::recursive_mutex> lck_guard(rmut);
    //rmut.lock();

    //start of critical section
    int retval = n*bad_factorial(n-1);
    std::cout<<"Returning "<<retval<<std::endl;

    //rmut.unlock();
    return retval;
}

void task1()
{
    std::cout << "Task1 trying to lock the mutex \n";
    tmut.lock();
    std::cout<<"Task1 locks the mutex\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout<<"Task1 unlocking the mutex\n";
    tmut.unlock();
}

void task2() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Task2 trying to lock the mutex\n";

    while (!tmut.try_lock_for(std::chrono::seconds(1))) {
        //return flase
        std::cout << "Task2 could not lock the mutex\n";

        //try again on Iteration

    }
    //Return True - mutext is now locked

    //start of critical section
    std::cout<<"Task2 has locked the mutex\n";
    //end

}

using namespace std;

int main()
{
//    std::thread t(bad_factorial, 10);
//    t.join();
    std::thread t2(task1);
    std::thread t3(task2);
    t2.join(); t3.join();
    return 0;
}

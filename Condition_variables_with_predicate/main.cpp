#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

std::string sdata;

std::mutex mt;

//the condition variable
std::condition_variable cond_var;
bool flag = false;

//waiting thread
void reader() {
    //lock the mutex
    std::cout << "Reader thread locking mutex\n";
    std::unique_lock<std::mutex> uniq_lck(mt);
    std::cout << "Reader thread has locked the mutex\n";

    //call wait()
    // This will unlock the mutex and make this thread sleep until the condition variable waks us up
    std::cout << "Reader thread sleeping...\n";
    cond_var.wait(uniq_lck, [] {return flag;});

    //the condition variable has woken this thread up
    // and locked the mutex
    std::cout << "Reader thread wakes up\n";

    //Display the new value of the string
    std::cout << "Data is \""<<sdata<<"\"\n";

}

//notifying thread
void writer() {
    {
        //Lock the mutex
        std::cout<<"writer thread locking mutex\n";

        //lock the mutex
        //This will not explicitly unlocked std::lock_guard is sufficient
        std::lock_guard<std::mutex> lck_guard(mt);
        std::cout<<"Writer thread has locked the mutex\n";

        //Pretend to be busy....
        std::this_thread::sleep_for(std::chrono::seconds(2));

        //Modifying the string
        std::cout << "Writer thread modifying data....\n";
        sdata = "Populated";

        //set the flag
        flag =true;

    }

    //notify the condition variable
    std::cout <<"writer thread sends notification\n";
    cond_var.notify_one();
}

int main()
{
    cout << "Hello Condition Variables!" << endl;
    sdata = "Empty";
    //display its initial value
    std::cout<<"Data is \""<<sdata<<" \"\n";

    //start threads
    std::thread write(writer);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::thread read(reader);

    read.join(); write.join();
    return 0;
}

#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>


using namespace std;

std::shared_mutex shmut;
int x = 0;
void write()    // write thread with exclusive lock
{
    std::lock_guard<std::shared_mutex> lck_guard(shmut);

    x++;
    cout <<"write "<<x<<endl;
}

void read() {
    std::shared_lock sh_lck(shmut);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    cout<<"read it ...."<<x<<endl;
}

int main()
{
    cout << "Shared Mutex!" << endl;

    std::vector<std::thread> threads;

    for (int i = 0; i < 20; ++i) {
        threads.push_back(std::thread(read));
    }

    threads.push_back(std::thread(write));
    threads.push_back(std::thread(write));

    for (int i = 0; i < 20; ++i) {
        threads.push_back(std::thread(read));
    }
    return 0;
}

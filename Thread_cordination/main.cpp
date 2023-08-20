#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>


using namespace std;

//shared variable for the data being fetched
std::string sdata;
//Flags for thread communication
bool update_progress = false;
bool completed = false;

//mutexes to protect the shared variables
std::mutex data_mutex;
std::mutex completed_mutex;

//data fetch thread
void fetch_data() {
    for (int i=0; i < 5; ++i) {
        std::cout << "Fetcher thread is waiting for data....\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        //Update sdata, notify progressbar thread
        std::lock_guard<std::mutex> data_lck(data_mutex);
        sdata += "Block "+std::to_string(i+1);
        std::cout << "sdata "<<sdata<<std::endl;
        update_progress = true;
    }

    std::cout << "Fetch the sdata has just ended\n";
    std::lock_guard<std::mutex> complete_lck(completed_mutex);
    completed = true;
}

//Progress bar thread
void progress_bar() {
    size_t len = 0;
    while (true) {
        std::cout << " Progress bar thread is waiting for data....\n";

        //waiting until there is some new data to display
        std::unique_lock<std::mutex> data_lck(data_mutex);
        while(!update_progress) {
            data_lck.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            data_lck.lock();
        }

        //wake up and use the new value
        len = sdata.size();

        //set the flag back to false
        update_progress = false;
        data_lck.unlock();

        std::cout << "Received "<<len<<" bytes so far \n";

        // Terminate when the download has finished
        std::lock_guard<std::mutex> complete_lck(completed_mutex);

        if(completed) {
            std::cout << "Progress bar thread has ended"<<std::endl;
            break;
        }
    }
}

void process_data() {
    std::cout << "Processing thread waiting for data......\n";

    //wait until the download is completed
    std::unique_lock<std::mutex> completed_lck(completed_mutex);

    while(!completed) {
        completed_lck.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        completed_lck.lock();
    }

    completed_lck.lock();
    std::lock_guard<std::mutex> data_lck(data_mutex);
    std::cout << "Processing sdata: "<<sdata<<std::endl;
}

int main()
{
    cout << "Hello Thread Cordination!" << endl;

    std::thread fetcher(fetch_data);
    std::thread pro(progress_bar);
    std::thread process(process_data);
    fetcher.join(); pro.join(); process.join();
    return 0;
}

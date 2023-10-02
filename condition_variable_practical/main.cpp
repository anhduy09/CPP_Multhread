#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <string>

//using namespace std::literals;

using namespace std;

string sdata;

//bool flags for predicates
bool update_progress = false;
bool completed = false;

//Mutexes to protect the shared variables
std::mutex data_mutex;
std::mutex completed_mutex;

//the condition variables
std::condition_variable data_cv;
std::condition_variable completed_cv;

void fetch_data() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Fetcher thread waiting for data..."<<endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        //Update sdata, then notify the progress bar thread
        std::unique_lock<std::mutex> uniq_lck(data_mutex);
        sdata += "Block"+std::to_string(i+1);
        std::cout << "Fetched data: "<<sdata << std::endl;
        update_progress = true;
        uniq_lck.unlock();
        data_cv.notify_all();
    }

    std::cout << "Fetch sdata has ended\n";

    //Tell the progress bar thread to exit
    //and wakeup the processing thread
    std::lock_guard<std::mutex> lg(completed_mutex);
    completed = true;
    completed_cv.notify_all();
}

void progress_bar() {
    size_t len = 0;

    while (true) {
        //wait until there is some new data to display
        std::unique_lock<std::mutex> data_lck(data_mutex);
        data_cv.wait(data_lck,[]{return update_progress;});

        //wake up and use the new value
        len = sdata.size();

        //set our flag to false
        update_progress = false;
        data_lck.unlock();

        std::cout << "Received "<<len <<" bytes so far"<<endl;

        //check if the download has finished
        std::unique_lock<std::mutex> compl_lck(completed_mutex);

        //use wait_for( to avoid blocking
        if(completed_cv.wait_for(compl_lck, std::chrono::milliseconds(10),[] {return completed;})){
            std::cout << "Progress bar thread has ended"<<std::endl;
            break;
        }
    }

}

void process_data() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "Processing thread waiting for data ...\n";

    //wait until the download is complete
    std::unique_lock<std::mutex> compl_lck(completed_mutex); //acquire lock
    completed_cv.wait(compl_lck, []{return completed;});

    compl_lck.unlock();

    std::lock_guard<std::mutex> data_lck(data_mutex);
    std::cout << "Processing sdata: "<<sdata << std::endl;

    //process the data.......

}

int main()
{
    cout << "condition variable pratice" << endl;
    std::thread fetcher(fetch_data);
    std::thread prog(progress_bar);
    std::thread processor(process_data);

    fetcher.join();
    prog.join();
    processor.join();
    return 0;
}

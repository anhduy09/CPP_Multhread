#include <iostream>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <future>

using namespace std;
//using namespace literal;

int task() {
    std::cout << "Executing task() in thread with ID: \n";
    std::cout << std::this_thread::get_id() <<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "Returning from task() \n";
    return 42;
}

void func(const std::string& option = "default") {
    std::future<int> result;

    if (option == "async") {
        result = std::async(std::launch::async, task);
    } else if (option == "defered") {
        result = std::async(std::launch::deferred, task);
    } else {
        result = std::async(task);
    }

    std::cout << "Calling async with option \" "<<option<<"\" \n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Calling get() \n";
    std::cout << "Task result: " << result.get() << "\n";

}

int main()
{
    cout << "Hello World!" << endl;
    std::cout << "In main thread with ID: "<<std::this_thread::get_id() <<"\n";
    func("async");
    std::cout << "----------------------------\n";
    func("deferred");
    std::cout <<"-----------------------------\n";
    func("default");
    return 0;
}

#include <iostream>
#include <thread>
#include <future>

using namespace std;

int produce() {
    int x = 42;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    //some code which may throw an exception
    if(1) {
        throw std::out_of_range("Oops");
    }

    std::cout << "Produce returning " <<x<<"\n";
    return x;
}

int main()
{
    cout << "Hello the asycn function 2!" << endl;
    auto result = std::async(produce);

    //Get the result - may throw an exception
    std::cout << "Future calling get ....\n";
    try {
        int x = result.get();
        std::cout << "Future returns from calling get()\n";
        std::cout <<"The answer is "<<x<<"\n";

    }  catch (std::exception& e) {
        std::cout<<"Exception caught: "<<e.what()<<"\n";
    }
    return 0;
}

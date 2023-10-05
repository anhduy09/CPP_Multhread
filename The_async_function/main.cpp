#include <iostream>
#include <future>



using namespace std;

void hello() {
    std::cout << "Hello, Async!\n";
}

//task returns a value
unsigned long long fibonacci(unsigned long long n) {
    if (n <= 1) {
        return 1;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
    cout << "Hello The Async function!" << endl;
    //std::async(hello);
    std::cout << "Calling Fibonacci(44)\n";

    //call async() and store the return future;
    auto fut = std::async(fibonacci, 44);

    //Do some other work
    bool finished = false;

    while(fut.wait_for(std::chrono::seconds(1)) != std::future_status::ready) {
        std::cout << "waiting for the result...\n";

    }

    //call get() when we are ready
    std::cout << fut.get() <<std::endl;


    return 0;
}

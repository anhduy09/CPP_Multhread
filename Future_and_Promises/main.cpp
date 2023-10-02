#include <iostream>
#include <future>
#include <thread>

using namespace std;

void produce(std::promise<int>& px) {

    //produce the result
    int x =42;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    //store the result in the shared state
    std::cout << "Promise sets shared state to "<< x << '\n';
    px.set_value(x);

}

//the consumer's task function takes an std::future as argument
void consume(std::future<int>& fx) {
    //get the result from the shared state
    std::cout << "Future calling get()...\n";
    int x = fx.get();
    std::cout << "Future returns from calling get()\n";
    std::cout<<"The answer is "<<x<<'\n';
}

int main()
{
    cout << "Hello Promise and Future!" << endl;
    //create an std::promise object
    //this creates an associated std::future object
    //and sets up a thread state between them
    std::promise<int> prom;

    //get the future associated with the promises
    std::future<int> fut = prom.get_future();
    //Start the threads
    //The producer task function takes the promises as argument
    std::thread thr_producer(produce, std::ref(prom));

    //The consumer task function takes the future as argument
    std::thread thr_consumer(consume, std::ref(fut));

    thr_consumer.join();
    thr_producer.join();
    return 0;
}

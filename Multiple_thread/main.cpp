#include <iostream>
#include <thread>

using namespace std;

void hello(int num) {
    std::this_thread::sleep_for(std::chrono::seconds(num));
    std::cout<<"Hello Multiple thread lesson\n";

}

int main()
{
    std::thread thr1(hello,1);
    std::thread thr2(hello,5);
    std::thread thr3(hello,10);

    thr1.join();
    thr2.join();
    thr3.join();
    return 0;
}

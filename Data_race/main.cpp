#include <iostream>
#include <thread>

void print(std::string str)
{
    // A very artificial way to display a string
    for (int i = 0; i < 5; ++i) {
        std::cout<<str[0]<<str[1]<<str[2]<<std::endl;
    }
}

void assigment() {
    for (int i = 0; i <100000; ++i) {
        std::cout<<std::this_thread::get_id()<<" "<<i<<std::endl;
    }
}

using namespace std;

int main()
{
//    std::thread thr1(print,"anh");
//    std::thread thr2(print,"duy");
//    std::thread thr3(print,"abc");

    std::thread thr1(assigment);
    std::thread thr2(assigment);
    std::thread thr3(assigment);

//    //wait for the tasks to complete
    thr1.join();
    thr2.join();
    thr3.join();

    return 0;
}

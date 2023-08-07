#include <iostream>
#include <thread>
#include <mutex>


using namespace std;

class Test {
public:
    Test() {
        std::cout <<"Test constructor is called \n";
    }
    void func() {

    }
};

Test *pTest = nullptr;  //variable to be lazily initialized
std::once_flag pTest_flag;  //The flag stores synchroniztion data


void process() {
    //Pass a callable object which performs the initialization
    std::call_once(pTest_flag,[]() {
        pTest = new Test();
    });
    pTest->func();
}

int main()
{
    cout << "Hello Double-checked Locking!" << endl;
    std::thread thr1(process);
    std::thread thr2(process);
    thr1.join(); thr2.join();
    return 0;
}

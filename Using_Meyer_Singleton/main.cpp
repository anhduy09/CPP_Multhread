//Lazy Initialization (multi thread)
// Use Meyer singleton

#include <iostream>
#include <thread>

using namespace std;

class Test {
public:
    Test()
    {
        std::cout << "Test constructor called\n";
    }
    void func() {

    }
};

void process() {
    static Test test;
    test.func();
}

int main()
{
    cout << "Hello Double-checked Locking and using Meyer singleton!" << endl;
    std::thread thr1(process);
    std::thread thr2(process);
    thr1.join(); thr2.join();
    return 0;
}

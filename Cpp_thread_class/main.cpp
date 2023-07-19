#include <iostream>
#include <thread>

using namespace std;

void hello() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "hello thread"<<std::endl;

}

//Function taking a thread object as argument
//The object must be moved into the argument
void func(std::thread thr) {
    std::cout<<"Recived thread with Id "<<thr.get_id()<<std::endl;

    //The function argument now "owns" the system thread
    // It is responsible for calling join()
    thr.join();
}

std::thread func() {
    std::thread thr(hello);

    //retun a local variable
    return thr;

    //IF wanna return a temporary object
    //return std::thread(hello);
}

int main()
{
    // std::thread is move-only object
    std::thread thr(hello);

    //display the child thread's ID
    std::cout << "hello thread has ID "<<thr.get_id()<<std::endl;
    func(std::move(thr));
    //pass a temporary object
    //func(std::thread(hello))
    std::cout<<"----------------------------------"<<endl;
    std::thread thr2 = func();
    thr2.join();
    return 0;
}

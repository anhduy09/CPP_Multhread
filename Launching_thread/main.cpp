#include <iostream>
#include <thread>

using namespace std;

class Hello {
public:
    void operator()() {
        std::cout<<"Hello, Functor Thread!\n"<<endl;
    }
};

void hello() {
    cout << "Hello World!" << endl;
}

void check(int a) {
    if (a%3 == 0) {
        std::cout << "Fizz"<<endl;
    } else if (a%5 == 0) {
        std:: cout << "Buzzz"<<endl;
    }
}

void sayHello(std::string v) {
    std::cout << v <<std::endl;
}

void func(std::string&& val) {
    std::cout << "thread with argument - "<<val<<std::endl;
}

void sayHello1(std::string& v) {
    std::cout << "thread with ref - "<<v<<std::endl;
}

int main()
{

    thread thr(hello);
    thr.join();
    Hello hello1;
    std::thread thr1(hello1);
    thr1.join();

    int n = 10;
    int group[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (auto i : group) {
        check(i);
    }

    std::thread thr2(sayHello,"Ta anh duy");
    thr2.join(); // join function means we will wait this thread run and finish before exit the program
//    std::string a = "------------";
//    sayHello(a);

    //
    std::string name = "DUYYYYYYYYYYYYY";
    std::thread thr3(func, std::move(name));
    thr3.join();
    // verify that str has been modified
    std::cout << "Do I still keep my name??"<<std::endl;
    std::cout<< (name.empty() ? "No" : "Yes") <<std::endl;

    //
    std::string name1 = "Ta Anh Duong";
    std::thread thr4(sayHello1,std::ref(name1));
    thr4.join();

    return 0;
}


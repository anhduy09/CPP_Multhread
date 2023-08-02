#ifndef SINGLETON_H
#define SINGLETON_H
#include <iostream>

class Singleton {


public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    Singleton() {
        std::cout<< "Initializing Singleton"<<std::endl;
    }
};

//Funtion to obtain the Singleton object
Singleton& get_Singleton();

#endif // SINGLETON_H

#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>


class Singleton {
    //Pointer to unique instance
    static Singleton *single;

    //The constructor is private
    Singleton() {
        std::cout<< "Initializing Singleton"<<std::endl;
    }

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    //Static member function to obtain the singleton object
    static Singleton* get_Singleton();
};



#endif // SINGLETON_H

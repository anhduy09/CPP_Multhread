#include "singleton.h"

Singleton* Singleton::single = nullptr;

Singleton* Singleton::get_Singleton()
{
    if(single == nullptr)
        single = new Singleton();
    return single;
}

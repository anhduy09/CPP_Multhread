#include "singleton.h"

Singleton& get_Singleton() {
    // Initialized by the first thread that executes this code
    static Singleton single;
    return single;
}

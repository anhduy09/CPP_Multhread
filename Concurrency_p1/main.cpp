#include <iostream>
#include <thread>

using namespace std;

void sayHello(std::string v) {
    std::cout << v <<std::endl;
}

int main()
{
    std::thread thr(sayHello,"Ta anh duy");
    thr.join(); // join function means we will wait this thread run and finish before exit the program
    return 0;
}


//perform two activities at the same time
//    - conceptually differnt

//e.g. A program which executes a long-running task
//    - Fetching data over the network
//    - Performing a lengthy computation
//The program displays "feedback"to the user
//The task and the feedback are performed at the same time
//Standard in OS for many years
//Computers run many programs at the same time
    //-Compiler generates code
    //- Wordprocessor waits for next keystroke
    //- Mail program fetches a new mail

//Modern computer have multiple processors
    //- Multiple CPU Chip
    //- CPU chips which contains multiple processor "cores"
//Different processors can perform different activities at the same time
    //- Even within the same program
//These are known as "hardware threads"
    //- Each processor follow its own "thread of execution" through the code
    //- 1 hardware thread <=> 1 processor core

//Modern operating system support "software threading"
//A program can perform multiple activities at the same time
    //- These activities are managed by the operating system
//Typically there are more software threads than hardware threads
    //- some threads may have to stop and wait for something
    //- while they are waiting, another thread which is ready can run




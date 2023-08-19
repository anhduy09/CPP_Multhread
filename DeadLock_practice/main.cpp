#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

//some data about the problem
constexpr int nforks = 5;
constexpr int nphilosophers = nforks;

std::string names[nphilosophers] = {"A", "B", "C", "D", "E"};

// keep track of how many times a philosopher is able to eat
int mouths[nphilosophers] = {0};

//A philosopher who has not picked up both forks is thinking
constexpr auto think_time = std::chrono::seconds(2);

//A philoshopher who has picked up bothe forks is eating
constexpr auto eat_time = std::chrono::seconds(1);


//A mutex prevent more than one philosopher picking up the same fork
// A philosopher thread can only pick up a fork if it can lock the corresponding mutex
std::mutex mutex_forks[nforks];

// mutex to protect output
std::mutex print_mutex;

// funtion to display the information about the 'nth' philosopher

//Interaction with a fork
void print(int n, const std::string& str, int forkno) {
    std::lock_guard<std::mutex> print_lock (print_mutex);
    std::cout << "philosopher "<<names[n]<<str<<forkno<<std::endl;
}

//Philosopher's state
void print(int n, const std::string& str) {
    std::lock_guard<std::mutex> print_lock(print_mutex);
    std::cout<< "philosopher "<<names[n]<<str<<std::endl;
}

//Thread which represents a dining philosopher
void dine(int nphilo) {
    /* Philosopher A has fork 0 on the left
    and fork 1 on the right
    Philosopher B has fork 1 on the left
    and fork 2 on the right
    ........
    Philosopher E has fork 4 on the left
    and fork 0 on the right*/

    //Earch philosopher must pick up the left fork first
    int lfork = nphilo;
    int rfork = (nphilo+1) % nforks;
    print(nphilo, "\'s left fork is number ", lfork);
    print(nphilo, "\'s right fork is number ",rfork);
    print(nphilo, " is thinking ....");

    std::this_thread::sleep_for(think_time);

    // make an attempt to eat
    print(nphilo, "\'s reach for fork number ", lfork);

    //try to pick up the left fork
    mutex_forks[lfork].lock();
    print(nphilo, " picks up fork ", lfork);
    print(nphilo, " is thinking ....");

    //Succeed - now try pick up the right fork
    std::this_thread::sleep_for(think_time);

    print(nphilo, " reaches for fork number ", rfork);
    mutex_forks[rfork].lock();
    print(nphilo, " picks up fork ", rfork);
    print(nphilo, " is eating ....");

    std::this_thread::sleep_for(eat_time);

    print(nphilo, " puts down the fork ", lfork);
    print(nphilo, " puts down the fork  ",rfork);
    print(nphilo, " thinking ....");

    mutex_forks[lfork].unlock();
    mutex_forks[rfork].unlock();
    std::this_thread::sleep_for(think_time);
}


int main()
{
    cout << "Hello DeadLock practice!" << endl;

    //Start a separate thread for each philosopher
    std::vector<std::thread> philos;

    for (int i = 0; i < nphilosophers; ++i) {
        philos.push_back(std::move(std::thread{dine, i}));
    }

    for (auto& philo : philos) {
        philo.join();
    }

    //How many times were the philosophers to be able to eat;
    for (int i = 0; i < nphilosophers; ++i) {
        std::cout << "philosopher " << names[i]
                     << " had "<<mouths[i] << "mouthfuls"<<std::endl;
    }

    return 0;
}

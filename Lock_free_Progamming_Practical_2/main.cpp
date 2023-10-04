#include <iostream>
#include <list>
#include <thread>
#include <iostream>
#include <vector>

using namespace std;
template <typename T>
struct LockFreeQueue {
private:
    //use an std::list to store the elements
    std::list<T> lst;

    //ihead and iTail iterators
    typename std::list<T>::iterator iHead, iTail;
public:
    //class constructor
    LockFreeQueue () {
        //Create a dummy element to seperate iHead from iTail
        lst.push_back(T());
        iHead = lst.begin();
        iTail = lst.end();
    }

    //Procduce thread function
    void produce(const T& t) {
        //Add the new element
        lst.push_back(t);

        //update iTail
        iTail = lst.end();

        //Erase the removed elements
        lst.erase(lst.begin(), iHead);

    }

    //consumer thread function
    bool Consume(T& t) {
        //Go to the first element
        auto iFirst = iHead;
        ++iFirst;

        //if queue is not empty
        if(iFirst != iTail) {
            //update iHead
            iHead = iFirst;

            //Fetch this first element
            t = *iHead;
            return true;
        }

        //no element to fetch
        return true;
    }

    //function to display all the elements
    void print() {
        //go to the first element
        auto head = iHead;
        ++head;

        //we cannot use the range-for loop, because we only access some of the elements
        for(auto el = head; el != iTail; ++el) {
            std::cout << &el << ", ";

        }
        std::cout <<"\n";
    }
};

int main()
{
    cout << "Hello Lock-free Programming practical!" << endl;
    LockFreeQueue<int> lfq;
    std::vector<std::thread> threads;
    int j = 1;

    for (int i = 0; i < 10; ++i) {
        //Run the member functions of LockFreeQueue in threads
        //Syntax for member function with std::thread
        //First argument is a pointer to member function
        //Second argument is the address of the object the member function is called on
        //(this will be the "this" pointer in the member function)
        //Then the arguments to the member function. These are passed as reference to int
        // So wee need to wrap them in std::ref()

//        lfq.produce(i);
//        lfq.Consume(j);

        std::thread produce(&LockFreeQueue<int>::produce, &lfq, std::ref(i));
        threads.push_back(std::move(produce));
        std::thread consume(&LockFreeQueue<int>::Consume, &lfq, std::ref(j));
        threads.push_back(std::move(consume));
    }

    for(auto& thr : threads){
        thr.join();
    }
    lfq.print();
    return 0;
}

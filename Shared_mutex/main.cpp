#include <iostream>
#include <thread>
#include <shared_mutex>

int value = 0;
std::shared_mutex mutex;

// Reads the value and sets v to that value
void readValue(int& v) {
  mutex.lock_shared();
  // Simulate some latency/time to run
  std::this_thread::sleep_for(std::chrono::seconds(1));
  v = value;
  mutex.unlock_shared();
}

// Sets value to v
void setValue(int v) {
  mutex.lock();
  // Simulate some latency/time to run
  std::this_thread::sleep_for(std::chrono::seconds(1));
  value = v;
  mutex.unlock();
}

int main() {
  int read1;
  int read2;
  int read3;
  std::thread t1(readValue, std::ref(read1));
  std::thread t2(readValue, std::ref(read2));
  std::thread t3(readValue, std::ref(read3));
  std::thread t4(setValue, 1);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  std::cout << read1 << "\n";
  std::cout << read2 << "\n";
  std::cout << read3 << "\n";
  std::cout << value << "\n";
}

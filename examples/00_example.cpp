#include <iostream>
#include <thread>

#include "trm/trm.hpp"

void increment_counter(trm::Trm<int> counter, int num_increments) {
  for (int i = 0; i < num_increments; ++i) {
    counter.withLock([](int& value) { ++value; });
  }
}

int main() {
  trm::Trm<int> counter(0);

  std::thread t1(increment_counter, counter, 1000);
  std::thread t2(increment_counter, counter, 1000);

  t1.join();
  t2.join();

  counter.withConstLock([](const int& value) {
    std::cout << "Thread 3 (Read-only): " << value << std::endl;
  });

  return 0;
}

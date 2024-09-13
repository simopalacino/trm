# TRM - Thread-safe Reference with Mutex

**TRM (Thread-safe Reference with Mutex)** is a header-only C++ library that provides thread-safe, reference-counted objects for managing shared resources in a multithreaded environment. It offers utilities like shared mutexes and thread-safe data structures such as queues and buffers, designed to simplify the challenges of concurrent programming.

## Features

- **Reference-counted mutexes**: Automatic memory management with thread-safe access to shared objects.
- **Thread-safe queues and buffers**: Safe, lock-protected containers for multithreaded applications.
- **Header-only**: No need for linking libraries, just include the headers and you're ready to go.
- **Multithreading utilities**: (*Maybe in future*) Helpers like thread pools, scoped locks, and synchronization primitives.

## Getting Started

### Requirements

- **C++17 or later**: TRM requires modern C++ standards for features like smart pointers and lambdas.
- **pthread**: You’ll need to link against pthread for multithreading support.

### Installation

TRM is a header-only library, so no installation is required. Just download or clone the repository, and include the relevant headers in your project.

```sh
git clone <https://github.com/simopalacino/trm.git>
```

### Usage

Include the necessary headers from the `include/` directory in your project.

```cpp
# include "RefMutex.hpp"
```

### Example: Shared Counter

Here's an example using `TRM` to create a thread-safe, reference-counted shared counter across multiple threads:

```cpp
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
```

### Compile the Example

You can compile the example using `g++`:

```sh
g++ -std=c++17 -pthread examples/00_example.cpp -I./include -o build/00_example
./build/00_example
```

### License

This project is licensed under the BSD 3-Clause License - see the [LICENSE](./LICENSE) file for details.

---

### Contributing

We welcome contributions! Please feel free to submit pull requests, open issues, or share ideas to help improve TRM.

---

### Authors

Developed by [simopalacino](https://github.com/simopalacino). If you have any questions or feedback, feel free to reach out!

---

Let me know if you'd like any adjustments or additional sections.

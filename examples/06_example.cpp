/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2024 Simone Palacino <simo.palacino@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source or binary forms are permitted provided that
 * the following conditions are met: (1) source code retains the copyright
 * notice and disclaimer, (2) binary forms reproduce the copyright notice and
 * disclaimer, (3) neither the name Trm its contributors may
 * be used to endorse or promote derived products without permission.
 *
 * For the full license text, see the LICENSE file.
 */

#include <iostream>
#include <thread>

#include "trm/ThreadSafeQueue.hpp"

int main() {
  trm::ThreadSafeQueue<int> s_queue(std::queue<int>{});

  auto producer = [s_queue](int id) mutable {
    for (int i = 0; i < 5; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      // This is synchronized ...
      s_queue.push(id * 10 + i);
      // but the print it's not.
      std::cout << "Producer " << id << " pushed: " << id * 10 + i << std::endl;
    }
  };

  auto consumer = [s_queue](int id) mutable {
    for (int i = 0; i < 5; ++i) {
      int item = s_queue.waitAndPop();
      std::cout << "Consumer " << id << " popped: " << item << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
  };

  std::vector<std::thread> producers;
  for (int i = 0; i < 3; ++i) {
    producers.emplace_back(producer, i);
  }

  std::vector<std::thread> consumers;
  for (int i = 0; i < 3; ++i) {
    consumers.emplace_back(consumer, i);
  }

  for (auto &producer_thread : producers) {
    producer_thread.join();
  }

  for (auto &consumer_thread : consumers) {
    consumer_thread.join();
  }

  return 0;
}

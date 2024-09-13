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

#include "trm/trm.hpp"

int main() {
  // Start multiple readers
  std::vector<std::thread> readers;
  std::thread *writer;
  {
    trm::RwTrm<int> rw_int(0);
    for (int i = 0; i < 5; ++i) {
      readers.emplace_back([rw_int, i]() {
        rw_int.withReadLock([i](const int &value) {
          std::cout << "Reader " << i << ": " << value << std::endl;
        });
      });
    }

    // Start a writer
    writer = new std::thread([rw_int]() mutable {
      rw_int.withWriteLock([](int &value) {
        value += 42;
        std::cout << "Writer updated value to: " << value << std::endl;
      });
    });
  }

  // Wait for threads to finish
  for (auto &reader : readers) {
    reader.join();
  }
  writer->join();

  return 0;
}

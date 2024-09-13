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
  trm::RwTrm<int> rw_int(0);

  std::thread writer([rw_int]() mutable {
    rw_int.withWriteLock([](int &value) {
      value += 42;
      std::cout << "Writer: " << value << std::endl;
    });
  });

  std::thread reader1([rw_int]() {
    rw_int.withReadLock([](const int &value) {
      std::cout << "Reader 1: " << value << std::endl;
    });
  });

  std::thread reader2([rw_int]() {
    rw_int.withReadLock([](const int &value) {
      std::cout << "Reader 2: " << value << std::endl;
    });
  });

  writer.join();
  reader1.join();
  reader2.join();

  return 0;
}

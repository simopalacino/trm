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

#include "trm/trm.hpp"

int main() {
  trm::LazyTrm<int> lazy_int(0);

  lazy_int.modifyIfNeeded([](const int &value) { return value < 100; },
                          [](int &value) {
                            value += 50;
                            std::cout << "Modified: " << value << std::endl;
                          });

  std::cout << "Final value: " << lazy_int.getValue() << std::endl;

  return 0;
}

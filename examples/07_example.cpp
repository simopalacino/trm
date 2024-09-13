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
#include <ostream>
#include <string>
#include <thread>

#include "trm/trm.hpp"

namespace trm::examples {

struct Person {
  std::string name;
  int age;

  Person &operator+=(int years) {
    age += years;
    return *this;
  }
};

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &ostream,
                                     const Person &person) {
  return ostream << "Person[\n"
                 << "    name=\"" << person.name + "\"\n"
                 << "    age=" + std::to_string(person.age) << "\n"
                 << "]";
}

}  // namespace trm::examples

int main() {
  using trm::examples::Person;

  trm::Trm<Person> trm_person(Person{"simopalacino", 27});

  std::thread t1([trm_person]() mutable {
    trm_person.withLock([](Person &value) {
      value += 1;
      std::cout << "Thread 1: " << value << std::endl;
    });
  });

  std::thread t2([trm_person]() mutable {
    trm_person.withLock([](Person &value) {
      value += 2;
      std::cout << "Thread 2: " << value << std::endl;
    });
  });

  std::thread t3([trm_person]() {
    trm_person.withConstLock([](const Person &value) {
      std::cout << "Thread 3 (Read-only): " << value << std::endl;
    });
  });

  t2.join();
  t1.join();
  t3.join();

  return 0;
}

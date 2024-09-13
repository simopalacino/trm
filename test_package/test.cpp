#include <cstdio>

#include "trm/trm.hpp"

int main() {
  trm::Trm<int> Trm(0);
  Trm.withConstLock([](const int &value) { std::printf("%d\n", value); });

  return 0;
}

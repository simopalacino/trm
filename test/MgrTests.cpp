#include <gtest/gtest.h>
#include <sys/types.h>

#include <chrono>
#include <cstring>
#include <thread>

#include "trm/trm.hpp"

namespace trm {

class TrmTests : public testing::Test {
 public:
  TrmTests() {}
  void SetUp() override {}
};

TEST_F(TrmTests, NoTest) {}

}  // namespace trm

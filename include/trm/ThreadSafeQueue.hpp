/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2024 Simone Palacino <simo.palacino@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source or binary forms are permitted provided that
 * the following conditions are met: (1) source code retains the copyright
 * notice and disclaimer, (2) binary forms reproduce the copyright notice and
 * disclaimer, (3) neither the name of Trm nor its contributors may be used to
 * endorse or promote derived products without permission.
 *
 * For the full license text, see the LICENSE file.
 */

#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

#include "trm/trm.hpp"

namespace trm {

template <typename T>
class ThreadSafeQueue : public Trm<std::queue<T>> {
 public:
  ThreadSafeQueue(std::queue<T> initial_value)
      : Trm<std::queue<T>>(initial_value),
        queue_data_(std::make_shared<QueueData>()) {}

  void push(T value) {
    {
      std::lock_guard lk(queue_data_->mutex_cv);
      Trm<std::queue<T>>::withLock(
          [&](std::queue<int> &queue) { queue.push(value); });
    }
    queue_data_->cv.notify_one();
  }

  T waitAndPop() {
    T result;
    std::unique_lock lk(queue_data_->mutex_cv);
    queue_data_->cv.wait(lk, [&] { return !empty(); });

    Trm<std::queue<T>>::withLock([&](std::queue<int> &queue) {
      result = queue.front();
      queue.pop();
    });
    return result;
  }

  bool empty() const {
    bool empty;
    Trm<std::queue<T>>::withConstLock(
        [&](const std::queue<int> &queue) mutable { empty = queue.empty(); });
    return empty;
  }

 private:
  struct QueueData {
    std::condition_variable cv;
    std::mutex mutex_cv;
  };

  std::shared_ptr<QueueData> queue_data_;
};

}  // namespace trm

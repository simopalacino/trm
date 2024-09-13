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

#include <functional>
#include <memory>
#include <mutex>
#include <shared_mutex>

/**
 * @brief TRM: Thread-safe Reference with Mutex
 */
namespace trm {

/**
 * @brief A thread-safe reference-counting pointer.
 */
template <typename T>
class Trm {
 public:
  explicit Trm(T initial_value)
      : data_(std::make_shared<Data>(std::move(initial_value))) {}

  void withLock(std::function<void(T&)> fn) {
    std::lock_guard<std::mutex> lock(data_->mtx);
    fn(data_->value);
  }

  void withConstLock(std::function<void(const T&)> fn) const {
    std::lock_guard<std::mutex> lock(data_->mtx);
    fn(data_->value);
  }

 private:
  struct Data {
    explicit Data(T value) : value(std::move(value)) {}
    T value;
    mutable std::mutex mtx;
  };

  std::shared_ptr<Data> data_;
};

template <typename T>
class TrmWithTimeout {
 public:
  explicit TrmWithTimeout(T initial_value)
      : data_(std::make_shared<Data>(std::move(initial_value))) {}

  bool tryWithLockFor(std::function<void(T&)> fn,
                      std::chrono::milliseconds timeout) {
    std::unique_lock lock(data_->mtx, std::defer_lock);
    if (lock.try_lock_for(timeout)) {
      fn(data_->value);
      return true;
    }
    return false;
  }

 private:
  struct Data {
    explicit Data(T value) : value(std::move(value)) {}
    T value;
    mutable std::timed_mutex mtx;
  };

  std::shared_ptr<Data> data_;
};

template <typename T>
class RwTrm {
 public:
  explicit RwTrm(T initial_value)
      : data_(std::make_shared<Data>(std::move(initial_value))) {}

  void withWriteLock(std::function<void(T&)> fn) const {
    std::unique_lock lock(data_->mtx);
    fn(data_->value);
  }

  void withReadLock(std::function<void(const T&)> fn) const {
    std::shared_lock lock(data_->mtx);
    fn(data_->value);
  }

 private:
  struct Data {
    explicit Data(T value) : value(std::move(value)) {}
    T value;
    mutable std::shared_mutex mtx;
  };

  std::shared_ptr<Data> data_;
};

template <typename T>
class LazyTrm {
 public:
  explicit LazyTrm(T initial_value)
      : data_(std::make_shared<Data>(std::move(initial_value))) {}

  void modifyIfNeeded(std::function<bool(const T&)> condition,
                      std::function<void(T&)> modifier) {
    std::unique_lock lock(data_->mtx, std::defer_lock);

    if (condition(data_->value)) {
      lock.lock();
      modifier(data_->value);
    }
  }

  T getValue() const {
    std::lock_guard lock(data_->mtx);
    return data_->value;
  }

 private:
  struct Data {
    explicit Data(T value) : value(std::move(value)) {}
    T value;
    mutable std::mutex mtx;
  };

  std::shared_ptr<Data> data_;
};

}  // namespace trm

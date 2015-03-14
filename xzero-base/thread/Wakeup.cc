// This file is part of the "libxzero" project, http://xzero.io/
//   (c) 2009-2015 Christian Parpart <trapni@gmail.com>
//   (c) 2014-2015 Paul Asmuth
//
// Licensed under the MIT License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of
// the License at: http://opensource.org/licenses/MIT

#include <xzero-base/thread/Wakeup.h>

namespace xzero {
namespace thread {

Wakeup::Wakeup() : gen_(0) {
}

void Wakeup::waitForNextWakeup() {
  waitForWakeup(generation());
}

void Wakeup::waitForFirstWakeup() {
  waitForWakeup(0);
}

void Wakeup::waitForWakeup(long oldgen) {
  std::unique_lock<std::mutex> l(mutex_);

  condvar_.wait(l, [this, oldgen] {
    return gen_.load() > oldgen;
  });
}

void Wakeup::onWakeup(long generation, std::function<void()> callback) {
  std::unique_lock<std::mutex> l(mutex_);

  if (gen_.load() > generation) {
    l.unlock();
    callback();
    return;
  }

  callbacks_.push_back(callback);
}

long Wakeup::generation() const {
  return gen_.load();
}

void Wakeup::wakeup() {
  std::list<std::function<void ()>> callbacks;

  std::unique_lock<std::mutex> l(mutex_);
  gen_++;
  callbacks.splice(callbacks.begin(), callbacks_);
  l.unlock();

  condvar_.notify_all();

  for (const auto& callback: callbacks) {
    callback();
  }
}

} // namespace thread
} // namespace xzero


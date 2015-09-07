/**
 * This file is part of the "libstx" project
 *   Copyright (c) 2015 Christian Parpart
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * libstx is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include "stx/duration.h"

namespace stx {

Duration::Duration(uint64_t microseconds) : micros_(microseconds) {}

uint64_t Duration::microseconds() const noexcept {
  return micros_;
}

uint64_t Duration::seconds() const noexcept {
  return micros_ / MicrosPerSecond;
}

Duration Duration::operator+(const Duration& other) const {
  return Duration(micros_ + other.micros_);
}

}

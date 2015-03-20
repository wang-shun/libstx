// This file is part of the "libxzero" project
//   (c) 2009-2015 Christian Parpart <https://github.com/christianparpart>
//   (c) 2014-2015 Paul Asmuth <https://github.com/paulasmuth>
//
// libxzero is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License v3.0. You should have received a
// copy of the GNU General Public License along with this program. If not, see
// <http://www.gnu.org/licenses/>.

#pragma once

#include <xzero-base/Api.h>
#include <string>

namespace xzero {

enum class LogLevel {
  None = 0,
  Error = 1,
  Warning = 2,
  Info = 3,
  Debug = 4,
  Trace = 5,

  none = None,
  error = Error,
  warn = Warning,
  info = Info,
  debug = Debug,
  trace = Trace,
};

XZERO_API std::string to_string(LogLevel value);
XZERO_API LogLevel to_loglevel(const std::string& value);

}  // namespace xzero

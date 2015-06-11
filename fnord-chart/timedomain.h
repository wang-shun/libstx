/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2011-2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _FNORDMETRIC_TIMEDOMAIN_H
#define _FNORDMETRIC_TIMEDOMAIN_H
#include "fnord/datetime.h"
#include "fnord-chart/continuousdomain.h"

namespace fnord {
namespace chart {

class TimeDomain : public ContinuousDomain<fnord::DateTime> {
public:

  TimeDomain(
    fnord::DateTime min_value =
        std::numeric_limits<fnord::DateTime>::max(),
    fnord::DateTime max_value =
        std::numeric_limits<fnord::DateTime>::min(),
    bool is_logarithmic = false,
    bool is_inverted = false);

  std::string label(fnord::DateTime value) const;

};

}
}
#endif

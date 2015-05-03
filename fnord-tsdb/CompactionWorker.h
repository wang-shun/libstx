/**
 * This file is part of the "libfnord" project
 *   Copyright (c) 2015 Paul Asmuth
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _FNORD_TSDB_COMPACTIONWORKER_H
#define _FNORD_TSDB_COMPACTIONWORKER_H
#include <thread>
#include <fnord-base/stdtypes.h>
#include <fnord-tsdb/TSDBNodeRef.h>

namespace fnord {
namespace tsdb {

class CompactionWorker : public RefCounted {
public:

  CompactionWorker(TSDBNodeRef* node);
  void start();
  void stop();

protected:
  void run();

  thread::Queue<RefPtr<StreamChunk>>* queue_;
  std::atomic<bool> running_;
  std::thread thread_;
};

} // namespace tsdb
} // namespace fnord

#endif
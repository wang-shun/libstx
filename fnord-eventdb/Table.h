/**
 * This file is part of the "libfnord" project
 *   Copyright (c) 2015 Paul Asmuth
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _FNORD_EVENTDB_TABLE_H
#define _FNORD_EVENTDB_TABLE_H
#include <fnord-base/stdtypes.h>
#include <fnord-base/autoref.h>
#include <fnord-base/random.h>
#include <fnord-msg/MessageSchema.h>
#include <fnord-msg/MessageObject.h>
#include <fnord-eventdb/TableArena.h>

namespace fnord {
namespace eventdb {

struct ChunkRef {
  String replica_id;
  String chunk_id;
  uint64_t start_sequence;
  uint64_t num_rows;
};

struct TableSnapshot : public RefCounted {
  String table_name;
  uint64_t generation;
  List<ChunkRef> chunks;
};

class Table : public RefCounted {
public:

  static RefPtr<Table> open(
      const String& table_name,
      const String& replica_id,
      const String& db_path,
      const msg::MessageSchema& schema);

  void addRecords(const Buffer& records);
  void addRecord(const msg::MessageObject& record);

  const String& name() const;

  size_t commit();

  RefPtr<TableSnapshot> getSnapshot();

protected:

  Table(
      const String& table_name,
      const String& replica_id,
      const String& db_path,
      const msg::MessageSchema& schema,
      uint64_t head_sequence,
      RefPtr<TableSnapshot> snapshot);

  void commitTable(RefPtr<TableArena> arena) const;

  String name_;
  String replica_id_;
  String db_path_;
  msg::MessageSchema schema_;
  std::mutex mutex_;
  uint64_t seq_;
  List<RefPtr<TableArena>> arenas_;
  Random rnd_;
  RefPtr<TableSnapshot> head_;
};

} // namespace eventdb
} // namespace fnord

#endif

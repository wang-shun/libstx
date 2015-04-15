/**
 * This file is part of the "libfnord" project
 *   Copyright (c) 2015 Paul Asmuth
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _FNORD_EVENTDB_ARTIFACTINDEX_H
#define _FNORD_EVENTDB_ARTIFACTINDEX_H
#include <fnord-base/stdtypes.h>
#include <fnord-eventdb/TableReader.h>
#include <fnord-eventdb/TableWriter.h>
#include <fnord-msg/MessageSchema.h>

namespace fnord {
namespace eventdb {

enum class ArtifactStatus : uint8_t {
  DOWNLOAD,
  PRESENT,
  IGNORE
};

struct ArtifactFileRef {
  String filename;
  uint64_t size;
  uint64_t checksum;
};

struct ArtifactRef {
  String name;
  ArtifactStatus status;
  Vector<ArtifactFileRef> files;
  Vector<Pair<String, String>> attributes;
};

class ArtifactIndex {
public:

  ArtifactIndex(
      const String& db_path,
      const String& index_name,
      bool readonly);

  void addArtifact(const ArtifactRef& artifact);
  void updateStatus(const String& artifact_name, ArtifactStatus new_status);

protected:
  String db_path_;
  String index_name_;
  bool readonly_;
};

} // namespace eventdb
} // namespace fnord

#endif

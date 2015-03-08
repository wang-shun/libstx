/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <fnord-base/VFS.h>
#include <fnord-base/io/mmappedfile.h>

namespace fnord {

RefPtr<VFSFile> WhitelistVFS::openFile(const String& filename) {
  return RefPtr<VFSFile>(
      new io::MmappedFile(File::openFile(filename, File::O_READ)));
}

void WhitelistVFS::registerFile(
    const String vfs_path,
    const String& real_path) {
  whitelist_[vfs_path] = real_path;
}

}

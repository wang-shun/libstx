/**
 * This file is part of the "libfnord" project
 *   Copyright (c) 2015 Paul Asmuth
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _FNORD_DPROC_APPLICATION_H
#define _FNORD_DPROC_APPLICATION_H
#include <fnord-base/stdtypes.h>
#include <fnord-base/autoref.h>
#include <fnord-dproc/Task.h>
#include <fnord-msg/msg.h>

namespace fnord {
namespace dproc {

class Application {
public:

  Application(const String& name);

  RefPtr<Task> getTaskInstance(const String& name, const Buffer& params);

  template <typename ProtoType>
  void registerProtoTaskFactory(
      const String& name,
      ProtoTaskFactory<ProtoType> factory);

  void registerTaskFactory(const String& name, TaskFactory factory);

  template <typename TaskType, typename... ArgTypes>
  void registerTask(const String& name, ArgTypes... args);

  template <typename TaskType, typename... ArgTypes>
  void registerProtoTask(const String& name, ArgTypes... args);

protected:
  String name_;
  HashMap<String, TaskFactory> factories_;
};

template <typename ProtoType>
void Application::registerProtoTaskFactory(
    const String& name,
    ProtoTaskFactory<ProtoType> factory) {
  registerTaskFactory(name, [factory] (const Buffer& params) -> RefPtr<Task> {
    return factory(msg::decode<ProtoType>(params));
  });
}

template <typename TaskType, typename... ArgTypes>
void Application::registerTask(const String& name, ArgTypes... args) {
  registerTaskFactory(name, [=] (const Buffer& params) -> RefPtr<Task> {
    return new TaskType(params, args...);
  });
}

template <typename TaskType, typename... ArgTypes>
void Application::registerProtoTask(const String& name, ArgTypes... args) {
  registerTaskFactory(name, [=] (const Buffer& params) -> RefPtr<Task> {
    return new TaskType(msg::decode<typename TaskType::ParamType>(params), args...);
  });
}

} // namespace dproc
} // namespace fnord

#endif
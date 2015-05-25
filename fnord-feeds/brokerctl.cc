/**
 * This file is part of the "libfnord" project
 *   Copyright (c) 2015 Paul Asmuth
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <unistd.h>
#include "fnord-base/stdtypes.h"
#include "fnord-base/inspect.h"
#include "fnord-base/application.h"
#include "fnord-base/cli/flagparser.h"
#include "fnord-base/cli/CLI.h"
#include "fnord-base/thread/eventloop.h"

using namespace fnord;

void cmd_monitor(const cli::FlagParser& flags) {
  fnord::iputs("monitor", 1);
}

void cmd_export(const cli::FlagParser& flags) {
  fnord::iputs("export", 1);
}

int main(int argc, const char** argv) {
  fnord::Application::init();
  fnord::Application::logToStderr();

  fnord::cli::FlagParser flags;

  flags.defineFlag(
      "loglevel",
      fnord::cli::FlagParser::T_STRING,
      false,
      NULL,
      "INFO",
      "loglevel",
      "<level>");

  flags.parseArgv(argc, argv);

  Logger::get()->setMinimumLogLevel(
      strToLogLevel(flags.getString("loglevel")));

  cli::CLI cli;

  /* command: monitor */
  auto monitor_cmd = cli.defineCommand("monitor");
  monitor_cmd->onCall(std::bind(&cmd_monitor, std::placeholders::_1));

  /* command: export */
  auto export_cmd = cli.defineCommand("export");
  export_cmd->onCall(std::bind(&cmd_export, std::placeholders::_1));

  export_cmd->flags().defineFlag(
      "output_path",
      fnord::cli::FlagParser::T_STRING,
      true,
      NULL,
      NULL,
      "output file path",
      "<path>");

  export_cmd->flags().defineFlag(
      "output_prefix",
      fnord::cli::FlagParser::T_STRING,
      false,
      NULL,
      NULL,
      "output filename prefix",
      "<prefix>");


  cli.call(flags.getArgv());
  return 0;
}


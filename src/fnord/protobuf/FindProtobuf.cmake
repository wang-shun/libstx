# Locate and configure the Google Protocol Buffers library.
# Defines the following variables:
#
#   PROTOBUF_FOUND - Found the Google Protocol Buffers library
#   PROTOBUF_INCLUDE_DIRS - Include directories for Google Protocol Buffers
#   PROTOBUF_LIBRARIES - The protobuf library
#
# The following cache variables are also defined:
#   PROTOBUF_LIBRARY - The protobuf library
#   PROTOBUF_PROTOC_LIBRARY   - The protoc library
#   PROTOBUF_INCLUDE_DIR - The include directory for protocol buffers
#   PROTOBUF_PROTOC_EXECUTABLE - The protoc compiler
#
#  ====================================================================
#  Example:
#
#   find_package(Protobuf REQUIRED)
#   include_directories(${PROTOBUF_INCLUDE_DIRS})
#
#   include_directories(${CMAKE_CURRENT_BINARY_DIR})
#   PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS foo.proto)
#   add_executable(bar bar.cc ${PROTO_SRCS} ${PROTO_HDRS})
#   target_link_libraries(bar ${PROTOBUF_LIBRARY})
#
# NOTE: You may need to link against pthreads, depending
# on the platform.
#  ====================================================================
#
# PROTOBUF_GENERATE_CPP (public function)
#   SRCS = Variable to define with autogenerated
#          source files
#   HDRS = Variable to define with autogenerated
#          header files
#   ARGN = proto files
#
#  ====================================================================


#=============================================================================
# Copyright 2009 Kitware, Inc.
# Copyright 2009 Philip Lowman <philip@yhbt.com>
# Copyright 2008 Esben Mose Hansen, Ange Optimization ApS
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distributed this file outside of CMake, substitute the full
#  License text for the above reference.)

function(PROTOBUF_GENERATE_CPP SRCS HDRS)
  if(NOT ARGN)
    message(SEND_ERROR "Error: PROTOBUF_GENERATE_CPP() called without any proto files")
    return()
  endif(NOT ARGN)

  set(${SRCS})
  set(${HDRS})
  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)

    get_filename_component(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
    string(LENGTH ${ROOT_DIR} ROOT_DIR_LEN)

    get_filename_component(FIL_DIR ${ABS_FIL} PATH)
    string(LENGTH ${FIL_DIR} FIL_DIR_LEN)
    math(EXPR FIL_DIR_REM "${FIL_DIR_LEN} - ${ROOT_DIR_LEN}")

    string(SUBSTRING ${FIL_DIR} ${ROOT_DIR_LEN} ${FIL_DIR_REM} FIL_DIR_PREFIX)
    set(FIL_WEPREFIX "${FIL_DIR_PREFIX}/${FIL_WE}")

    list(APPEND ${SRCS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WEPREFIX}.pb.cc")
    list(APPEND ${HDRS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WEPREFIX}.pb.h")

    add_custom_command(
      OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WEPREFIX}.pb.cc"
             "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WEPREFIX}.pb.h"
      COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --cpp_out ${CMAKE_CURRENT_BINARY_DIR} --proto_path ${CMAKE_CURRENT_SOURCE_DIR} --proto_path ${PROTOBUF_INCLUDE_DIR} --proto_path ${FNORD_SOURCE_DIR}/fnord ${PROTOC_ARGS} ${ABS_FIL}
      DEPENDS ${ABS_FIL}
      COMMENT "Running C++ protocol buffer compiler on ${FIL}"
      VERBATIM )
  endforeach()

  set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${SRCS} ${${SRCS}} PARENT_SCOPE)
  set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()


find_path(PROTOBUF_INCLUDE_DIR google/protobuf/service.h)

# Google's provided vcproj files generate libraries with a "lib"
# prefix on Windows
if(WIN32)
    set(PROTOBUF_ORIG_FIND_LIBRARY_PREFIXES "${CMAKE_FIND_LIBRARY_PREFIXES}")
    set(CMAKE_FIND_LIBRARY_PREFIXES "lib" "")
endif()

find_library(PROTOBUF_LIBRARY NAMES protobuf
             DOC "The Google Protocol Buffers Library"
)
find_library(PROTOBUF_PROTOC_LIBRARY NAMES protoc
             DOC "The Google Protocol Buffers Compiler Library"
)
find_program(PROTOBUF_PROTOC_EXECUTABLE NAMES protoc
             DOC "The Google Protocol Buffers Compiler"
)

mark_as_advanced(PROTOBUF_INCLUDE_DIR
                 PROTOBUF_LIBRARY
                 PROTOBUF_PROTOC_LIBRARY
                 PROTOBUF_PROTOC_EXECUTABLE)

# Restore original find library prefixes
if(WIN32)
    set(CMAKE_FIND_LIBRARY_PREFIXES "${PROTOBUF_ORIG_FIND_LIBRARY_PREFIXES}")
endif()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PROTOBUF DEFAULT_MSG
    PROTOBUF_LIBRARY PROTOBUF_INCLUDE_DIR)

if(PROTOBUF_FOUND)
    set(PROTOBUF_INCLUDE_DIRS ${PROTOBUF_INCLUDE_DIR})
    set(PROTOBUF_LIBRARIES    ${PROTOBUF_LIBRARY})
endif()

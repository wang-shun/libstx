/**
 * This file is part of the "libstx" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * libstx is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stx/InternMap.h"
#include "stx/test/unittest.h"

UNIT_TEST(InternMapTest);

TEST_CASE(InternMapTest, TestInternMap, [] () {
  stx::InternMap im;

  auto a = im.internString("fnord");
  auto b = im.internString("bar");

  EXPECT_EQ(im.getString(a), "fnord");
  EXPECT_EQ(im.getString(b), "bar");
});

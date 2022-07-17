#include <gtest/gtest.h>

#include <nintendough/log/module.hpp>

using namespace nintendough::log;

TEST(LogModuleTest, TestLogSingleton) {
  // verify that LoggerInitFailure custom exception is thrown
  // if Logger::instance().init(path) is not called before attempting
  // to use the loggers
  ASSERT_THROW(error(""), LoggerInitFailure);
}

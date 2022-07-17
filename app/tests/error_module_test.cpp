#include <gtest/gtest.h>

#include <nintendough/error/module.hpp>

using namespace nintendough::error;

TEST(ErrorModuleTest, TestSourceLocation) {
  ASSERT_STREQ(RUNTIME_INFO.mFile.c_str(), __FILE__);
  ASSERT_STREQ(RUNTIME_INFO.mFunc.c_str(),
               static_cast<const char *>(__PRETTY_FUNCTION__));
  ASSERT_EQ(RUNTIME_INFO.mLine, static_cast<std::uint32_t>(__LINE__));
}

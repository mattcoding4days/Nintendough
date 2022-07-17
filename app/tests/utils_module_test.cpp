#include <gtest/gtest.h>

#include <nintendough/utils/module.hpp>

using namespace nintendough::utils;

TEST(UtilsModuleTest, TestSystemDefaults) {
  ASSERT_FALSE(SystemDefault::config_dir().empty());
  ASSERT_FALSE(SystemDefault::cache_dir().empty());
  ASSERT_FALSE(SystemDefault::logging_dir().empty());
  ASSERT_FALSE(
      SystemDefault::get_config_file_path_for(ConfigFile::System).empty());
  ASSERT_FALSE(
      SystemDefault::get_config_file_path_for(ConfigFile::Controller).empty());
  ASSERT_TRUE(std::filesystem::exists(
      SystemDefault::get_config_file_path_for(ConfigFile::System)));
  ASSERT_TRUE(std::filesystem::exists(
      SystemDefault::get_config_file_path_for(ConfigFile::Controller)));
}

TEST(UtilsModuleTest, TestFileSystemWrapper) {
  std::string serialized_sys_config = FileSystem::load_config(
      SystemDefault::get_config_file_path_for(ConfigFile::System));
  ASSERT_FALSE(serialized_sys_config.empty());
  std::string serialized_controller_config = FileSystem::load_config(
      SystemDefault::get_config_file_path_for(ConfigFile::Controller));
  ASSERT_FALSE(serialized_controller_config.empty());
}

set(PACKAGE_NAME "nintendough")

#
# NOTE: `get_version()` defines the variable `${${PACKAGE_NAME}_VERSION}` which is used below to set
# the version of the library  (see `cmake/utils.cmake`)
#
get_version()

# Rename `${${PACKAGE_NAME}_VERSION}` variable to `${PACKAGE_VERSION}` for easy reference in the
# current `CMakeLists.txt` file.
set(PACKAGE_VERSION ${${PACKAGE_NAME}_VERSION})

#
# NOTE: Set our source and include directory variables for use through the build
#
set(APP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(APP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(APP_TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(APP_EXAMPLES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/examples")

#
# NOTE: add additional project options
#
option(NINTENDOUGH_BUILD_APP_TESTING "Enable test builds" ON)
option(NINTENDOUGH_BUILD_APP_EXAMPLES "Enable example builds" ON)

#
# NOTE: Prevent in source builds (can't build in src/ or in project root)
#
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR OR CMAKE_CURRENT_BINARY_DIR STREQUAL APP_SOURCE_DIR)
  print(
    FATAL_ERROR
    "In source builds are not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

#
# NOTE: Bundle modules so they can easily be included
# so all sub_directory CMakeLists.txt has access to them
# [e.g] tests and examples
#
set(LOG_MODULE "${APP_SOURCE_DIR}/log/logger.cpp" "${APP_SOURCE_DIR}/log/error.cpp")
set(UTILS_MODULE "${APP_SOURCE_DIR}/utils/error.cpp" "${APP_SOURCE_DIR}/utils/fs_wrapper.cpp"
                 "${APP_SOURCE_DIR}/utils/system_defaults.cpp")
set(ERROR_MODULE "${APP_SOURCE_DIR}/error/base_error.cpp" "${APP_SOURCE_DIR}/error/source_location.cpp")
set(COMPONENT_MODULE
    "${APP_SOURCE_DIR}/component/cpu.cpp"
    "${APP_SOURCE_DIR}/component/bus.cpp"
    "${APP_SOURCE_DIR}/component/error.cpp"
    "${APP_SOURCE_DIR}/component/instruction.cpp")
#
# NOTE: This is where 3rd party libraries should be installed via the light weight CPM dependancy
# management system. The CPM wiki is here: https://github.com/cpm-cmake/CPM.cmake/wiki/More-Snippets
#
# NOTE: googletest version >= 3.11.0 now has google mock, and google benchmark libraries built into it,
# so we get 3 for 1
#
# NOTE: Using `CPMFindPackage()` to install package only if it is not already installed.
#
if(NINTENDOUGH_BUILD_APP_TESTING)
  #
  # NOTE: Add compile defenition for test config files
  #
  add_compile_definitions(NINTENDOUGH_TEST_DATA_DIR="${CMAKE_SOURCE_DIR}/config")
  cpmfindpackage(
    NAME
    googletest
    GITHUB_REPOSITORY
    google/googletest
    GIT_TAG
    release-1.12.1
    VERSION
    1.12.1
    OPTIONS
    "BUILD_GMOCK ON"
    "INSTALL_GTEST OFF"
    "gtest_force_shared_crt ON")
  if(googletest_ADDED)
    print(STATUS "gtest configured correctly")
    set(googletest_Installed
        ON
        PARENT_SCOPE)
  elseif(googletest_Installed)
    print(STATUS "gtest already installed")
  else()
    print(WARNING "gtest was not configured properly")
  endif()

  # add tests
  enable_testing()
  print(STATUS "${PACKAGE_NAME} -- Tests Enabled")
  add_subdirectory("tests")
endif()

#
# NOTE: Add the logging library
#
cpmfindpackage(
  NAME
  spdlog
  GITHUB_REPOSITORY
  gabime/spdlog
  VERSION
  1.10.0
  OPTIONS
  "SPDLOG_BUILD_SHARED OFF"
  "SPDLOG_BUILD_EXAMPLE OFF"
  "SPDLOG_BUILD_TESTS OFF"
  "SPDLOG_ENABLE_PCH ON"
  "SPDLOG_INSTALL ON")
if(spdlog_ADDED)
  print(STATUS "spdlog configured correctly")
else()
  print(WARNING "spdlog was not configured properly")
endif()

#
# NOTE: Bundle json library into our project, as it is header only
#
print(STATUS "\nAdding the nlohmann json library")
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${APP_INCLUDE_DIR}/nlohmann)

#
# NOTE: Add the src/ subdirectory to finish building the executable
#
add_subdirectory("src")

#
# NOTE: Build project examples
#
if(NINTENDOUGH_BUILD_APP_EXAMPLES)
  print(STATUS "${PACKAGE_NAME} -- Examples Enabled")
  add_subdirectory("examples")
endif()

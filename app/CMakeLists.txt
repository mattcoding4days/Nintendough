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
# NOTE: This is where 3rd party libraries should be installed via the light weight CPM dependancy
# management system. The CPM wiki is here: https://github.com/cpm-cmake/CPM.cmake/wiki/More-Snippets
#
# NOTE: googletest version >= 3.11.0 now has google mock, and google benchmark libraries built into it,
# so we get 3 for 1
#
# NOTE: Using `CPMFindPackage()` to install package only if it is not already installed.
#
if(NINTENDOUGH_BUILD_APP_TESTING)
  cpmfindpackage(
    NAME
    googletest
    GITHUB_REPOSITORY
    google/googletest
    GIT_TAG
    release-1.11.0
    VERSION
    1.11.0
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
# NOTE: Add json library
#

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

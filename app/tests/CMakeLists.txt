include(GoogleTest)

#
# NOTE: Add all test source files
#
set(APP_TEST_SOURCES "${APP_TEST_SOURCE_DIR}/utils_module_test.cpp" "${APP_TEST_SOURCE_DIR}/log_module_test.cpp"
                     "${APP_TEST_SOURCE_DIR}/error_module_test.cpp")

#
# NOTE: Declare a custom name for the test executable
#
set(PACKAGE_UNIT_TEST_NAME "${PACKAGE_NAME}_tests")

#
# NOTE: Add all test sources to the executable, and any other sources
#
add_executable(
  ${PACKAGE_UNIT_TEST_NAME}
  ${APP_TEST_SOURCES}
  ${ERROR_MODULE}
  ${UTILS_MODULE}
  ${LOG_MODULE})

#
# NOTE: Link any libraries we need to the test executable. The most notable being
# the gtest_main library.
#
target_include_directories(${PACKAGE_UNIT_TEST_NAME} PUBLIC ${APP_INCLUDE_DIR})
target_link_libraries(
  ${PACKAGE_UNIT_TEST_NAME}
  PRIVATE project_options
          project_warnings
          gtest_main
          spdlog::spdlog
          stdc++fs)

#
# NOTE: Signal google test to discover all tests
#
gtest_discover_tests(${PACKAGE_UNIT_TEST_NAME})

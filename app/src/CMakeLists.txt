#
# NOTE: Output build param information
#
print(STATUS "Building ${PACKAGE_NAME}_v${PACKAGE_VERSION} [${CMAKE_BUILD_TYPE}]")

#
# NOTE: Name the executable here
#
set(BINARY_NAME "${PACKAGE_NAME}")

#
# NOTE: Set the main routine
#
set(MAIN_ROUTINE "${APP_SOURCE_DIR}/main.cpp")

#
# NOTE: Declare the executable, manually add all source files
#
add_executable(
  ${BINARY_NAME}
  # Add source files
  ${MAIN_ROUTINE}
  ${ERROR_MODULE}
  ${LOG_MODULE}
  ${UTILS_MODULE}
  ${CPU_MODULE})

target_include_directories(${BINARY_NAME} PUBLIC ${APP_INCLUDE_DIR})
target_link_libraries(
  ${BINARY_NAME}
  PRIVATE project_options
          project_warnings
          stdc++fs
          spdlog::spdlog
          nlohmann_json)

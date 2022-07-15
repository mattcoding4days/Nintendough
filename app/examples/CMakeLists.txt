#
# NOTE: Add executables
#
set(SCRATCH_FILE "${PACKAGE_NAME}_scratch")
add_executable(${SCRATCH_FILE} "${APP_EXAMPLES_DIR}/scratch.cpp")
target_include_directories(${SCRATCH_FILE} PUBLIC ${APP_INCLUDE_DIR})
target_link_libraries(${SCRATCH_FILE} PRIVATE project_options project_warnings stdc++fs)

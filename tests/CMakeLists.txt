cmake_minimum_required(VERSION 3.21)

project(InstructorTests LANGUAGES CXX)

# Classroom 50 can configure this directory directly and supply REPO_ROOT.
# Fall back to the repository root for a regular top-level build.
if (NOT DEFINED REPO_ROOT)
  get_filename_component(REPO_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
endif()
file(TO_CMAKE_PATH "${REPO_ROOT}" REPO_ROOT)

if (NOT IS_DIRECTORY "${REPO_ROOT}/src")
  message(FATAL_ERROR "REPO_ROOT does not contain src: ${REPO_ROOT}")
endif()

if (NOT IS_DIRECTORY "${REPO_ROOT}/include")
  message(FATAL_ERROR "REPO_ROOT does not contain include: ${REPO_ROOT}")
endif()

find_package(GTest CONFIG REQUIRED)

add_executable(memorymap_tests
  src/memorymap_tests.cpp
  "${REPO_ROOT}/src/memorymap.cpp"
)

# Compile only the assignment implementation; GTest supplies the test main().
target_link_libraries(memorymap_tests PRIVATE GTest::gtest_main)
target_include_directories(memorymap_tests PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${REPO_ROOT}/include"
)
target_compile_features(memorymap_tests PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(memorymap_tests)

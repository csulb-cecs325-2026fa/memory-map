cmake_minimum_required(VERSION 3.21)

project("MemoryMap" LANGUAGES CXX)

option(BUILD_TESTING "Build the unit tests" ON)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Release,MinSizeRel>:ProgramDatabase>>")
endif()

add_executable(memorymap_demo
  src/main.cpp
  src/memorymap.cpp
)

target_include_directories(memorymap_demo PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_compile_features(memorymap_demo PRIVATE cxx_std_20)

include(CTest)
if (BUILD_TESTING)
  add_subdirectory("tests")
endif()

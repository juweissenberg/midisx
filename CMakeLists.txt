cmake_minimum_required(VERSION "4.0")

project(midisx)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# midisx target containing core functionalities
add_library(midisx)

target_sources(midisx
PRIVATE
    src/writer.cpp
    src/reader.cpp
    src/validator.cpp
PUBLIC
FILE_SET HEADERS
FILES
    src/manufacturers.h
    src/constants.h
    src/writer.h
    src/reader.h
    src/validator.h
)

set_target_properties(midisx PROPERTIES LINKER_LANGUAGE CXX)

# midisx_test target to execute unit tests
find_package(GTest REQUIRED)

add_executable(midisx_test)

target_sources(midisx_test
PRIVATE
    src/writer_test.cpp
    src/reader_test.cpp
    src/validator_test.cpp
)

target_link_libraries(midisx_test
PRIVATE
    midisx
    GTest::gtest_main
)

gtest_discover_tests(midisx_test)

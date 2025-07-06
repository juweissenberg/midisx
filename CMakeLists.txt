cmake_minimum_required(VERSION "4.0")

project(midisx)

option(BUILD_WASM "Build WebAssembly module" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# midisx target containing core functionalities
add_library(midisx)

target_sources(midisx
PRIVATE
    src/writer.cpp
    src/reader.cpp
    src/validator.cpp
    # entrypoint required for wasm build
    #$<IF:$<BOOL:${build_wasm}>,src/wasm_bindings.cpp,>
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

if(DEFINED EMSCRIPTEN)
    # do not build tests as gtest is not found using emscripten
else()
    # midisx_test target to execute unit tests
    include(CTest)

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

endif()

if(DEFINED EMSCRIPTEN)
    add_executable(midisx_wasm)
    target_sources(midisx_wasm
    PRIVATE
        src/wasm_bindings.cpp
    )
    target_link_libraries(midisx_wasm
    PRIVATE
        midisx
    )
    set_target_properties(midisx_wasm
    PROPERTIES
        OUTPUT_NAME "midisx"
        LINK_FLAGS "--bind -s WASM=1 -s NO_DISABLE_EXCEPTION_CATCHING=1 -s NO_EXIT_RUNTIME=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS=\"['_main']\" -s EXPORTED_RUNTIME_METHODS=\"['ccall','cwrap']\""
    )
endif()
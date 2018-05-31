cmake_minimum_required (VERSION 2.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../..)

set(SRCS
    src/BinaryBuff.cpp
    )

add_library (RTypeCommon ${SRCS})

target_include_directories(RTypeCommon PUBLIC include)

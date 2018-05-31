cmake_minimum_required (VERSION 2.6)
project (R-TYPE)

find_package (Threads)

if (NOT WIN32)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")
endif()

add_subdirectory(common)

add_subdirectory(server)

add_subdirectory(client)

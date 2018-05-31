cmake_minimum_required (VERSION 2.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../..)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

if (WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
endif()
# Find SFML
find_package(SFML 2 REQUIRED audio graphics window system)

if(NOT SFML_FOUND)
       message(FATAL_ERROR "SFML couldn't be located!")
endif()

include_directories(${SFML_INCLUDE_DIR} include)

set(SRCS
    src/main.cpp
    src/Core.cpp
    src/Image.cpp
    src/Text.cpp
    src/EntityManager.cpp
    src/AEntity.cpp
    src/EntityEnemy.cpp
    src/EntityEnemy2.cpp
    src/StateMenu.cpp
    src/StateGame.cpp
    src/StateOver.cpp
    src/StateSplash.cpp
    src/ClientNetwork.cpp
    src/Animation.cpp
    src/StatePlay.cpp
    src/EntityShip.cpp
    src/EntityFire.cpp
    src/EntityExplode.cpp
    src/EntityStarfield.cpp
    src/EntityBonus.cpp
    src/EntityEFire.cpp
    )

add_executable(r-type ${SRCS})

target_link_libraries(r-type RTypeCommon ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${CMAKE_THREAD_LIBS_INIT})

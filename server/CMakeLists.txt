cmake_minimum_required (VERSION 2.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../..)

include_directories(include)


set(SRCS
    src/main.cpp
    src/ServerNetwork.cpp
    src/ServerCore.cpp
    src/ServerGame.cpp
    src/ServerPlayer.cpp
    src/AServerEntity.cpp
    src/ServerBullet.cpp
    src/ServerEnemy.cpp
    src/ServerEnemy1.cpp
    src/ServerEnemy2.cpp
    src/ServerBonus.cpp
    src/PatternLoader.cpp
    )

add_executable(rserver ${SRCS})

target_link_libraries(rserver RTypeCommon ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})

add_subdirectory(pattern)

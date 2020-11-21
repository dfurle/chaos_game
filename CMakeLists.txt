cmake_minimum_required(VERSION 3.10.2)

project(game VERSION 1.0)

file(GLOB GAME_SRC "src/*")

add_executable(game ${GAME_SRC})

target_include_directories(game PRIVATE include)

TARGET_LINK_LIBRARIES(game sfml-graphics sfml-window sfml-system sfml-audio)

cmake_minimum_required(VERSION 3.16)
project(ChessEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(chess_engine
    src/main.cpp
    src/board.cpp
    src/board.h
    src/move.h
    src/move.cpp
    src/chess_constants.h
    src/io_utils.h
    src/io_utils.cpp
)

target_include_directories(chess_engine PRIVATE
    src
)

# Enable warnings per compiler
if (MSVC)
    target_compile_options(chess_engine PRIVATE /W4 /permissive-)
else()
    target_compile_options(chess_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()
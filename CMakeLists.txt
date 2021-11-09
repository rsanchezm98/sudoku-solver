cmake_minimum_required(VERSION 3.1)
project(sudoku)

include_directories(include)
include_directories(sudoku_files)

add_executable(sudoku src/main.cc src/sudoku.cc)

install(DIRECTORY include/
        DESTINATION include/
        )   

install(DIRECTORY sudoku_files/
        DESTINATION sudoku_files/
        )  
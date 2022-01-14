cmake_minimum_required(VERSION 3.10)

project(FileSystemCalculate)

set(SRC src/main.cpp
        src/fs_cli.cpp)

add_executable(FileSystemCalculate ${SRC})


cmake_minimum_required(VERSION 3.10)

project(FileSystemCalculate)

set( SRC src/main.cpp
         src/fs_cli.cpp
         src/task.cpp
         src/task_queue.cpp )

add_executable(FileSystemCalculate ${SRC})


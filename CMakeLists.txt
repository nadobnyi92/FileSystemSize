cmake_minimum_required(VERSION 3.10)

project(FileSystemCalculate)

include(${CMAKE_SOURCE_DIR}/conan.cmake)
conan_cmake_run(
    CONANFILE conanfile.txt
    BASIC_SETUP
    BUILD missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set( SRC src/main.cpp
         src/fs_cli.cpp
         src/task.cpp
         src/task_queue.cpp )

add_executable(FileSystemCalculate ${SRC})


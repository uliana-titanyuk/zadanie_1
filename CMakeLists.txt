cmake_minimum_required(VERSION 3.1)

project(Task_1)

include_directories(${PROJECT_SOURCE_DIR})

set (Task_1_SRC  main.cpp functions.cpp Class.cpp)
set (Task_1_HDR  Class.h Header.h)

add_executable (${PROJECT_NAME} ${Task_1_SRC} ${Task_1_HDR})

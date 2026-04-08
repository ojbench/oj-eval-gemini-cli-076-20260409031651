cmake_minimum_required(VERSION 3.10)
project(MyList)
file(GLOB SOURCES "*.cpp")
add_executable(code ${SOURCES})

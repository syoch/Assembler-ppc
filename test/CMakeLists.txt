cmake_minimum_required( VERSION 2.8 )

project(Test CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories("../include")

add_executable(Test test.cpp)

file(GLOB ppcasm ../*ppcasm*)
target_link_libraries(Test ${ppcasm})
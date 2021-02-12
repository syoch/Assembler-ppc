cmake_minimum_required( VERSION 2.8 )

project(AssemblerPPC CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories("include")
include_directories("libs/strutil")

add_library(ppcasm STATIC
    src/asm.cpp
    libs/strutil/strutil.cpp
)
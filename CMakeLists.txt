
cmake_minimum_required(VERSION 3.10)

# set the project name
project(learning)

# Tau requires at least C11/C++11
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
    Tau
    URL https://github.com/jasmcaus/Tau/archive/dev.zip
)

FetchContent_MakeAvailable(Tau)


# add the executable
add_executable(learning number.c)

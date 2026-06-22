cmake_minimum_required(VERSION 3.15)

project(verilator-cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)
find_package(VERILATOR REQUIRED)

file(GLOB RTL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.sv"
)

add_subdirectory(sim)

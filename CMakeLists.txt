cmake_minimum_required(VERSION 3.15)

project(verilator-cmake_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/sdl3.cmake)

find_package(VERILATOR REQUIRED)

file(GLOB RTL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.sv"
)
file(GLOB SIM_SOURCES
    "${CMAKE_SOURCE_DIR}/sim/*.cpp"
)

add_executable(Vtop
    ${SIM_SOURCES}
)

target_link_libraries(Vtop
    PRIVATE
        SDL3::SDL3
)

verilate(Vtop
    SOURCES
        ${RTL_SOURCES}
    TOP_MODULE top
    PREFIX Vtop
    VERILATOR_ARGS
        --trace-fst
)

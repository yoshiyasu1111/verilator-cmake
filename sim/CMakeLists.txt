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

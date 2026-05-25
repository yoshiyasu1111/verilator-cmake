#pragma once

#include "Vtop.h"
#include "verilated.h"

#include <cstdint>
#include <memory>

class Simulator {
public:
    static constexpr uint64_t CLK_HALF_PERIOD = 5;

    Simulator(int argc, char** argv);

    void eval();
    void tick();
    void reset(uint32_t cycles = 5);

    uint64_t time() const;

    VerilatedContext*   context_ptr()   const { return contextp_.get(); }
    Vtop*               top_ptr()       const { return top_.get(); }

private:
    std::unique_ptr<VerilatedContext>   contextp_;
    std::unique_ptr<Vtop>               top_;
};
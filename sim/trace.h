#pragma once

#include "Vtop.h"
#include "verilated.h"
#include "verilated_fst_c.h"
#include <cstdint>
#include <memory>

class Trace {
public:
    static constexpr auto WAVE_DIR = "waves";
    static constexpr auto WAVE_FILE = "top.fst";

    std::unique_ptr<VerilatedFstC> tfp;

    Trace(VerilatedContext* contextp, Vtop* top);
    ~Trace();

    void dump(uint64_t time);
};

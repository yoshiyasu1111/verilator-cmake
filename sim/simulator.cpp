#include "simulator.h"

Simulator::Simulator(int argc, char** argv) {
    contextp = std::make_unique<VerilatedContext>();
    contextp->commandArgs(argc, argv);

    top = std::make_unique<Vtop>(contextp.get(), "");

    top->clk    = 0;
    top->rst_n  = 0;
}

void Simulator::eval() {
    top->eval();
}

void Simulator::tick() {
    // Rising edge
    top->clk = 1;
    top->eval();
    contextp->timeInc(CLK_HALF_PERIOD);

    // Falling edge
    top->clk = 0;
    top->eval();
    contextp->timeInc(CLK_HALF_PERIOD);
}

void Simulator::reset(uint32_t cycles) {
    top->rst_n = 0;
    top->eval();

    for (uint32_t i = 0; i < cycles; i++) {
        tick();
    }
    top->rst_n = 1;
}

uint64_t Simulator::time() const {
    return contextp->time();
}

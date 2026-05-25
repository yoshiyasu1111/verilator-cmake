#include "simulator.h"

Simulator::Simulator(int argc, char** argv) {
    contextp_ = std::make_unique<VerilatedContext>();
    contextp_->commandArgs(argc, argv);

    top_ = std::make_unique<Vtop>(contextp_.get(), "");

    top_->clk    = 0;
    top_->rst_n  = 0;
}

void Simulator::eval() {
    top_->eval();
}

void Simulator::tick() {
    // Rising edge
    top_->clk = 1;
    top_->eval();
    contextp_->timeInc(CLK_HALF_PERIOD);

    // Falling edge
    top_->clk = 0;
    top_->eval();
    contextp_->timeInc(CLK_HALF_PERIOD);
}

void Simulator::reset(uint32_t cycles) {
    top_->rst_n = 0;
    top_->eval();

    for (uint32_t i = 0; i < cycles; i++) {
        tick();
    }
    top_->rst_n = 1;
}

uint64_t Simulator::time() const {
    return contextp_->time();
}

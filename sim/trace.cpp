#include "trace.h"
#include <cstdint>
#include <filesystem>
#include <memory>

Trace::Trace(VerilatedContext* contextp, Vtop* top) {
    contextp->traceEverOn(true);

    tfp = std::make_unique<VerilatedFstC>();

    top->trace(tfp.get(), 99);

    std::filesystem::create_directories(WAVE_DIR);
    auto wave_path = std::filesystem::path(WAVE_DIR) / WAVE_FILE;
    tfp->open(wave_path.c_str());
}

Trace::~Trace() {
    tfp->close();
}

void Trace::dump(uint64_t time) {
    tfp->dump(time);
}

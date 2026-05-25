#include "Vtop.h"
#include "verilated.h"
#include "verilated_fst_c.h"
#include <filesystem>
#include <cstdint>

class Testbench {
public:
  // Clock half period
  static constexpr uint64_t CLK_HALF_PERIOD = 5;

  // Wave output settings
  static constexpr auto WAVE_DIR = "waves";
  static constexpr auto WAVE_FILE = "top.fst";

  std::unique_ptr<VerilatedContext> contextp;
  std::unique_ptr<Vtop> top;
  std::unique_ptr<VerilatedFstC> tfp;

  Testbench() {
    contextp = std::make_unique<VerilatedContext>();

    // Enable waveform tracing
    contextp->traceEverOn(true);

    // Create DUT instance
    top = std::make_unique<Vtop>(contextp.get(), "top");

    // Create FST tracer
    tfp = std::make_unique<VerilatedFstC>();

    // Enable tracing for all hierarchy levels
    top->trace(tfp.get(), 99);

    // Create wave output directory
    std::filesystem::create_directories(WAVE_DIR);

    // Open waveform file
    auto wave_path = std::filesystem::path(WAVE_DIR) / WAVE_FILE;
    tfp->open(wave_path.c_str());

    // Initial signal values
    top->clk = 0;
    top->rst_n = 0;

    // Dump initial state
    top->eval();
    tfp->dump(contextp->time());
  }

  ~Testbench() {
    top->final();
    tfp->close();
  }

  void eval() { top->eval(); }

  void tick() {
    // rising edge
    top->clk = 1;
    top->eval();
    contextp->timeInc(CLK_HALF_PERIOD);
    tfp->dump(contextp->time());

    // falling edge
    top->clk = 0;
    top->eval();
    contextp->timeInc(CLK_HALF_PERIOD);
    tfp->dump(contextp->time());
  }

  void reset(uint32_t cycles = 5) {
    top->rst_n = 0;

    for (uint32_t i = 0; i < cycles; i++) {
      tick();
    }
    top->rst_n = 1;
  }

  uint64_t time() const { return contextp->time(); }
};

int main(int argc, char **argv) {
  auto tb = std::make_unique<Testbench>();

  tb->contextp->commandArgs(argc, argv);
  tb->reset();

  for (uint64_t cycle = 0; cycle < 20; cycle++) {
    tb->tick();
    printf("time=%4llu cycle=%2llu count0=%3d count1=%2d\n",
        tb->time(), cycle, tb->top->count0, tb->top->count1);
  }

  return 0;
}
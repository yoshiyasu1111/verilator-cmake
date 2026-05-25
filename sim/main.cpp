#include "simulator.h"
#include "trace.h"
#include <memory>

int main(int argc, char** argv) {
  auto sim = std::make_unique<Simulator>(argc, argv);
  auto trace = std::make_unique<Trace>(sim->context_ptr(), sim->top_ptr());

  sim->eval();
  trace->dump(sim->time());

  sim->reset();

  for (uint64_t cycle = 0; cycle < 20; cycle++) {
    sim->tick();
    trace->dump(sim->time());

    printf(
      "time=%4llu cycle=%2llu count0=%3d count1=%2d\n",
      sim->time(),
      cycle,
      sim->top_ptr()->count0,
      sim->top_ptr()->count1
    );
  }
  return 0;
}

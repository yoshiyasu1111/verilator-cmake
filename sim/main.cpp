#include "simulator.h"
#include "trace.h"
#include "renderer.h"
#include <memory>

int main(int argc, char** argv) {
  auto sim = std::make_unique<Simulator>(argc, argv);
  auto trace = std::make_unique<Trace>(sim->context_ptr(), sim->top_ptr());
  auto renderer = std::make_unique<Renderer>("Vtop", 800, 600);

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
  sim->top_ptr()->final();

  while (renderer->poll_events()) {
    
  }

  return 0;
}

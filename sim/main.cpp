#include "simulator.h"

int main(int argc, char** argv) {
  auto sim = std::make_unique<Simulator>(argc, argv);

  sim->eval();
  sim->reset();

  for (uint64_t cycle = 0; cycle < 20; cycle++) {
    sim->tick();

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

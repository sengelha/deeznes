#include "test_mem.h"
#include <cpu/m6502.h>
#include <gtest/gtest.h>

using namespace deeznes::cpu;

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

TEST(cpu_fuzz_tests, random_instr) {
  // CPU should run without exception or faiulre
  uint8_t instr[16384];
  std::generate_n(instr, ARRAYSIZE(instr), std::rand);
  // TODO: Add HLT instruction to end, use this to drive program
  uint8_t ram[1024];
  test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
  m6502 cpu(&c);
  cpu.run(1024);
}
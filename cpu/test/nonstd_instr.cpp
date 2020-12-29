#include "test_mem.h"
#include <cpu/m6502.h>
#include <gtest/gtest.h>

using namespace deeznes::cpu;

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

TEST(cpu_nonstd_instr, dcpabs) {
  uint8_t instr[] = {0xCF, 0x00, 0x00};
  uint8_t mem[0x1000] = {0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x04;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x01, mem[0]);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, dcpabx) {
  uint8_t instr[] = {0xDF, 0x00, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x04;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x01, mem[1]);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(7, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, dcpaby) {
  uint8_t instr[] = {0xDB, 0x00, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x04;
  state.regs.Y = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x01, mem[1]);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(7, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, dcpixx) {
  uint8_t instr[] = {0xC3, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x04, 0x00, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x04;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x01, mem[0x04]);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, dcpixy) {
  uint8_t instr[] = {0xD3, 0x00};
  uint8_t mem[0x1000] = {0x01, 0x00, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x04;
  state.regs.Y = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x01, mem[0x02]);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, dcpzpg) {
  uint8_t instr[] = {0xC7, 0x00};
  uint8_t mem[0x1000] = {0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x04;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x01, mem[0]);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(5, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, dcpzpx) {
  uint8_t instr[] = {0xD7, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x04;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x01, mem[1]);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, isbabs) {
  uint8_t instr[] = {0xEF, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xFF;
  state.regs.P = 0x01;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(6, cpu.state().cycles);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, cpu.state().regs.A);
  ASSERT_EQ(0x80, mem[1]);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
}

TEST(cpu_nonstd_instr, isbabx) {
  uint8_t instr[] = {0xFF, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xFF;
  state.regs.X = 1;
  state.regs.P = 0x01;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(7, cpu.state().cycles);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, cpu.state().regs.A);
  ASSERT_EQ(0x80, mem[2]);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
}

TEST(cpu_nonstd_instr, isbaby) {
  uint8_t instr[] = {0xFB, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xFF;
  state.regs.Y = 1;
  state.regs.P = 0x01;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(7, cpu.state().cycles);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, cpu.state().regs.A);
  ASSERT_EQ(0x80, mem[2]);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
}

TEST(cpu_nonstd_instr, isbixx) {
  uint8_t instr[] = {0xE3, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x04, 0x00, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xFF;
  state.regs.X = 1;
  state.regs.P = 0x01;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(8, cpu.state().cycles);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, cpu.state().regs.A);
  ASSERT_EQ(0x80, mem[4]);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
}

TEST(cpu_nonstd_instr, isbixy) {
  uint8_t instr[] = {0xF3, 0x00};
  uint8_t mem[0x1000] = {0x01, 0x00, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xFF;
  state.regs.Y = 1;
  state.regs.P = 0x01;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(8, cpu.state().cycles);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, cpu.state().regs.A);
  ASSERT_EQ(0x80, mem[2]);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
}

TEST(cpu_nonstd_instr, isbzpg) {
  uint8_t instr[] = {0xE7, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xFF;
  state.regs.P = 0x01;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(5, cpu.state().cycles);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, cpu.state().regs.A);
  ASSERT_EQ(0x80, mem[1]);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
}

TEST(cpu_nonstd_instr, isbzpx) {
  uint8_t instr[] = {0xF7, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xFF;
  state.regs.X = 1;
  state.regs.P = 0x01;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(6, cpu.state().cycles);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, cpu.state().regs.A);
  ASSERT_EQ(0x80, mem[2]);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
}

TEST(cpu_nonstd_instr, laxabs) {
  uint8_t instr[] = {0xAF, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0x80};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0;
  state.regs.X = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(4, cpu.state().cycles);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x80, cpu.state().regs.A);
  ASSERT_EQ(0x80, cpu.state().regs.X);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
}

TEST(cpu_nonstd_instr, laxaby) {
  uint8_t instr[] = {0xBF, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x80};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0;
  state.regs.X = 0;
  state.regs.Y = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(4, cpu.state().cycles);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x80, cpu.state().regs.A);
  ASSERT_EQ(0x80, cpu.state().regs.X);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
}

TEST(cpu_nonstd_instr, laxixx) {
  uint8_t instr[] = {0xA3, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x04, 0x00, 0x80};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(6, cpu.state().cycles);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x80, cpu.state().regs.A);
  ASSERT_EQ(0x80, cpu.state().regs.X);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
}

TEST(cpu_nonstd_instr, laxixy) {
  uint8_t instr[] = {0xB3, 0x00, 0xB3, 0x03};
  uint8_t mem[0x1000] = {0x01, 0x00, 0x80, 0xFF, 0x00};
  mem[0x100] = 0xFF;
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.Y = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x80, cpu.state().regs.A);
  ASSERT_EQ(0x80, cpu.state().regs.X);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_EQ(5, cpu.state().cycles);

  // The below instruction crosses a page boundary
  cpu.run(1);
  ASSERT_EQ(0xC004, cpu.state().regs.PC);
  ASSERT_EQ(0xFF, cpu.state().regs.A);
  ASSERT_EQ(0xFF, cpu.state().regs.X);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_EQ(11, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, laxzpg) {
  uint8_t instr[] = {0xA7, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0x80};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0;
  state.regs.X = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(3, cpu.state().cycles);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x80, cpu.state().regs.A);
  ASSERT_EQ(0x80, cpu.state().regs.X);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
}

TEST(cpu_nonstd_instr, laxzpy) {
  uint8_t instr[] = {0xB7, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x80};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0;
  state.regs.X = 0;
  state.regs.Y = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(4, cpu.state().cycles);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x80, cpu.state().regs.A);
  ASSERT_EQ(0x80, cpu.state().regs.X);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
}

TEST(cpu_nonstd_instr, nopabs) {
  uint8_t instr[] = {0x0C, 0x00, 0x00};
  uint8_t mem[] = {0x00};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(4, cpu.state().cycles);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
}

TEST(cpu_nonstd_instr, nopabx) {
  constexpr uint8_t nopabx_opcodes[] = {0x1C, 0x3C, 0x5C, 0x7C, 0xDC, 0xFC};

  for (int i = 0; i < ARRAYSIZE(nopabx_opcodes); ++i) {
    uint8_t instr[] = {
        nopabx_opcodes[i], 0x00, 0x00, nopabx_opcodes[i], 0xFF, 0x00,
    };
    uint8_t mem[0x1000] = {0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502_state state;
    state.regs.PC = 0xC000;
    state.regs.X = 1;
    state.cycles = 0;
    m6502 cpu(state, &c);
    cpu.run(1);
    ASSERT_EQ(4, cpu.state().cycles);
    ASSERT_EQ(0xC003, cpu.state().regs.PC);

    cpu.run(1);
    ASSERT_EQ(9, cpu.state().cycles);
    ASSERT_EQ(0xC006, cpu.state().regs.PC);
  }
}

TEST(cpu_nonstd_instr, nopimm) {
  uint8_t instr[] = {0x80, 0x00};
  uint8_t mem[] = {0x00};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(2, cpu.state().cycles);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
}

TEST(cpu_nonstd_instr, nopimp) {
  constexpr uint8_t nopimp_opcodes[] = {0x1A, 0x3A, 0x5A, 0x7A, 0xDA, 0xFA};

  for (int i = 0; i < ARRAYSIZE(nopimp_opcodes); ++i) {
    uint8_t instr[] = {nopimp_opcodes[i]};
    uint8_t mem[0x1000] = {0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502_state state;
    state.regs.PC = 0xC000;
    state.regs.X = 1;
    state.cycles = 0;
    m6502 cpu(state, &c);
    cpu.run(1);
    ASSERT_EQ(2, cpu.state().cycles);
    ASSERT_EQ(0xC001, cpu.state().regs.PC);
  }
}

TEST(cpu_nonstd_instr, nopzpg) {
  constexpr uint8_t nopzpg_opcodes[] = {0x04, 0x44, 0x64};

  for (int i = 0; i < ARRAYSIZE(nopzpg_opcodes); ++i) {
    uint8_t instr[] = {nopzpg_opcodes[i], 0x00};
    uint8_t mem[0x1000] = {0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502_state state;
    state.regs.PC = 0xC000;
    state.cycles = 0;
    m6502 cpu(state, &c);
    cpu.run(1);
    ASSERT_EQ(3, cpu.state().cycles);
    ASSERT_EQ(0xC002, cpu.state().regs.PC);
  }
}

TEST(cpu_nonstd_instr, nopzpx) {
  constexpr uint8_t nopzpx_opcodes[] = {0x14, 0x34, 0x54, 0x74, 0xD4, 0xF4};

  for (int i = 0; i < ARRAYSIZE(nopzpx_opcodes); ++i) {
    uint8_t instr[] = {nopzpx_opcodes[i], 0x00, nopzpx_opcodes[i], 0xFF};
    uint8_t mem[0x1000] = {0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502_state state;
    state.regs.PC = 0xC000;
    state.regs.X = 1;
    state.cycles = 0;
    m6502 cpu(state, &c);
    cpu.run(1);
    ASSERT_EQ(4, cpu.state().cycles);
    ASSERT_EQ(0xC002, cpu.state().regs.PC);

    cpu.run(1);
    ASSERT_EQ(8, cpu.state().cycles);
    ASSERT_EQ(0xC004, cpu.state().regs.PC);
  }
}

TEST(cpu_nonstd_instr, rlaabs) {
  uint8_t instr[] = {0x2F, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xEF;
  state.regs.X = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0xFE, mem[1]);
  ASSERT_EQ(0xEE, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rlaabx) {
  uint8_t instr[] = {0x3F, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xEF;
  state.regs.X = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0xFE, mem[2]);
  ASSERT_EQ(0xEE, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(7, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rlaaby) {
  uint8_t instr[] = {0x3B, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xEF;
  state.regs.Y = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0xFE, mem[2]);
  ASSERT_EQ(0xEE, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(7, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rlaixx) {
  uint8_t instr[] = {0x23, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x04, 0x00, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xEF;
  state.regs.X = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0xFE, mem[0x04]);
  ASSERT_EQ(0xEE, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rlaixy) {
  uint8_t instr[] = {0x33, 0x00};
  uint8_t mem[0x1000] = {0x01, 0x00, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xEF;
  state.regs.Y = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0xFE, mem[0x02]);
  ASSERT_EQ(0xEE, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rlazpg) {
  uint8_t instr[] = {0x27, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xEF;
  state.regs.X = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0xFE, mem[1]);
  ASSERT_EQ(0xEE, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(5, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rlazpx) {
  uint8_t instr[] = {0x37, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x7F};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xEF;
  state.regs.X = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0xFE, mem[2]);
  ASSERT_EQ(0xEE, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rraabs) {
  uint8_t instr[] = {0x6F, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x01;
  state.regs.X = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[1]);
  ASSERT_EQ(0x81, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rraabx) {
  uint8_t instr[] = {0x7B, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x01;
  state.regs.Y = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[2]);
  ASSERT_EQ(0x81, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(7, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rraaby) {
  uint8_t instr[] = {0x7B, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x01;
  state.regs.Y = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[2]);
  ASSERT_EQ(0x81, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(7, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rraixx) {
  uint8_t instr[] = {0x63, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x04, 0x00, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x01;
  state.regs.X = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[0x04]);
  ASSERT_EQ(0x81, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rraixy) {
  uint8_t instr[] = {0x73, 0x00};
  uint8_t mem[0x1000] = {0x01, 0x00, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x01;
  state.regs.Y = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[0x02]);
  ASSERT_EQ(0x81, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rrazpg) {
  uint8_t instr[] = {0x67, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x01;
  state.regs.X = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[1]);
  ASSERT_EQ(0x81, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(5, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, rrazpx) {
  uint8_t instr[] = {0x77, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x01;
  state.regs.X = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[2]);
  ASSERT_EQ(0x81, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, saxabs) {
  uint8_t instr[] = {0x8F, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x7F;
  state.regs.X = 0xF7;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(4, cpu.state().cycles);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x77, mem[0x01]);
}

TEST(cpu_nonstd_instr, saxixx) {
  uint8_t instr[] = {0x83, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x04, 0x00, 0xCC};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x8F;
  state.regs.X = 0x01;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(6, cpu.state().cycles);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x01, mem[0x04]);
}

TEST(cpu_nonstd_instr, saxzpg) {
  uint8_t instr[] = {0x87, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x7F;
  state.regs.X = 0xF7;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(3, cpu.state().cycles);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x77, mem[0x01]);
}

TEST(cpu_nonstd_instr, saxzpy) {
  uint8_t instr[] = {0x97, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0xCC};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x7F;
  state.regs.X = 0xF7;
  state.regs.Y = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(4, cpu.state().cycles);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x77, mem[0x02]);
}

TEST(cpu_nonstd_instr, sloabs) {
  uint8_t instr[] = {0x0F, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x40;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x04, mem[1]);
  ASSERT_EQ(0x44, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, sloabx) {
  uint8_t instr[] = {0x1F, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x40;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x04, mem[2]);
  ASSERT_EQ(0x44, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(7, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, sloaby) {
  uint8_t instr[] = {0x1B, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x40;
  state.regs.Y = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x04, mem[2]);
  ASSERT_EQ(0x44, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(7, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, sloixx) {
  uint8_t instr[] = {0x03, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x04, 0x00, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x40;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x04, mem[0x04]);
  ASSERT_EQ(0x44, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, sloixy) {
  uint8_t instr[] = {0x13, 0x00};
  uint8_t mem[0x1000] = {0x01, 0x00, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x40;
  state.regs.Y = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x04, mem[0x02]);
  ASSERT_EQ(0x44, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, slozpg) {
  uint8_t instr[] = {0x07, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x40;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x04, mem[1]);
  ASSERT_EQ(0x44, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(5, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, slozpx) {
  uint8_t instr[] = {0x17, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x02};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0x40;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x04, mem[2]);
  ASSERT_EQ(0x44, cpu.state().regs.A);
  ASSERT_FALSE(cpu.state().regs.P & carry_flag);
  ASSERT_FALSE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, sreabs) {
  uint8_t instr[] = {0x4F, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xF7;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[1]);
  ASSERT_EQ(0x88, cpu.state().regs.A);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, sreabx) {
  uint8_t instr[] = {0x5F, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xF7;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[2]);
  ASSERT_EQ(0x88, cpu.state().regs.A);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(7, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, sreaby) {
  uint8_t instr[] = {0x5B, 0x01, 0x00};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xF7;
  state.regs.Y = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC003, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[2]);
  ASSERT_EQ(0x88, cpu.state().regs.A);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(7, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, sreixx) {
  uint8_t instr[] = {0x43, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0x04, 0x00, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xF7;
  state.regs.X = 1;
  state.regs.P = 0;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[0x04]);
  ASSERT_EQ(0x88, cpu.state().regs.A);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, sreixy) {
  uint8_t instr[] = {0x53, 0x00};
  uint8_t mem[0x1000] = {0x01, 0x00, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xF7;
  state.regs.Y = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[0x02]);
  ASSERT_EQ(0x88, cpu.state().regs.A);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, srezpg) {
  uint8_t instr[] = {0x47, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xF7;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[1]);
  ASSERT_EQ(0x88, cpu.state().regs.A);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(5, cpu.state().cycles);
}

TEST(cpu_nonstd_instr, srezpx) {
  uint8_t instr[] = {0x57, 0x01};
  uint8_t mem[0x1000] = {0xCC, 0xCC, 0xFF};
  test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
  m6502_state state;
  state.regs.PC = 0xC000;
  state.regs.A = 0xF7;
  state.regs.X = 1;
  state.cycles = 0;
  m6502 cpu(state, &c);

  cpu.run(1);
  ASSERT_EQ(0xC002, cpu.state().regs.PC);
  ASSERT_EQ(0x7F, mem[2]);
  ASSERT_EQ(0x88, cpu.state().regs.A);
  ASSERT_TRUE(cpu.state().regs.P & carry_flag);
  ASSERT_TRUE(cpu.state().regs.P & sign_flag);
  ASSERT_FALSE(cpu.state().regs.P & zero_flag);
  ASSERT_EQ(6, cpu.state().cycles);
}
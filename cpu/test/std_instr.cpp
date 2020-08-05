#include <cpu/m6502.h>
#include <gtest/gtest.h>
#include "test_mem.h"

using namespace deeznes::cpu;

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

TEST(cpu_std_instr, adcabs)
{
    uint8_t instr[] = {0x6D, 0x00, 0x00, 0x6D, 0x01, 0x00, 0x6D, 0x02, 0x00, 0x6D, 0x03, 0x00, 0x6D, 0x04, 0x00};
    uint8_t ram[] = {0x01, 0x01, 0xFF, 0xFF, 0x7F};
    test_mem mem(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502_state state{.regs.PC = 0xC000, .regs.A = 1, .cycles = 0};
    m6502 cpu(state, &mem);

    cpu.run(1);
    ASSERT_EQ(0x02, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x03, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(16, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(20, cpu.state().cycles);
}

TEST(cpu_std_instr, adcabx)
{
    uint8_t instr[] = {0x7D, 0x00, 0x00, 0x7D, 0x01, 0x00, 0x7D, 0x02, 0x00, 0x7D, 0x03, 0x00, 0x7D, 0x04, 0x00, 0x7D, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0x01, 0x01, 0xFF, 0xFF, 0x7F};
    mem[0x100] = 0x7F;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502_state state = {.regs.PC = 0xC000, .regs.A = 1, .regs.X = 1};
    m6502 cpu(state, &c);

    cpu.run(1);
    ASSERT_EQ(0x02, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x03, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(16, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(20, cpu.state().cycles);

    // Below operation crosses a page boundary
    state = cpu.state();
    state.regs.A = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(25, cpu.state().cycles);
}

TEST(cpu_std_instr, adcaby)
{
    uint8_t instr[] = {0x79, 0x00, 0x00, 0x79, 0x01, 0x00, 0x79, 0x02, 0x00, 0x79, 0x03, 0x00, 0x79, 0x04, 0x00, 0x79, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0x01, 0x01, 0xFF, 0xFF, 0x7F};
    mem[0x100] = 0x7F;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 1;
    state.regs.Y = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x02, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x03, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(16, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(20, cpu.state().cycles);

    // Below operation crosses a page boundary
    state = cpu.state();
    state.regs.A = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(25, cpu.state().cycles);
}

TEST(cpu_std_instr, adcimm)
{
    uint8_t instr[] = {0x69, 0x01, 0x69, 0x01, 0x69, 0xFF, 0x69, 0xFF, 0x69, 0x7F};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x02, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    ASSERT_EQ(0xC002, cpu.state().regs.PC);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x03, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    ASSERT_EQ(0xC004, cpu.state().regs.PC);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    ASSERT_EQ(0xC006, cpu.state().regs.PC);

    state = cpu.state();
    state.regs.A = 0xFF;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    ASSERT_EQ(0xC008, cpu.state().regs.PC);

    state = cpu.state();
    state.regs.A = 0;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(10, cpu.state().cycles);
    ASSERT_EQ(0xC00A, cpu.state().regs.PC);
}

TEST(cpu_std_instr, adcixx)
{
    uint8_t instr[] = {0x61, 0x01, 0x61, 0x04, 0x61, 0x07, 0x61, 0x0A, 0x61, 0x0D};
    uint8_t mem[] = {0xCC, 0xCC, 0x04, 0x00, 0x01, 0x07, 0x00, 0x01, 0x0A, 0x00, 0xFF, 0x0D, 0x00, 0xFF, 0x10, 0x00, 0x7F};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 1;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x02, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x03, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(18, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(24, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(30, cpu.state().cycles);
}

TEST(cpu_std_instr, adcixy)
{
    uint8_t instr[] = {0x71, 0x00, 0x71, 0x03, 0x71, 0x06, 0x71, 0x09, 0x71, 0x0C, 0x71, 0x0F};
    uint8_t mem[0x1000] = {0x01, 0x00, 0x01, 0x04, 0x00, 0x01, 0x07, 0x00, 0xFF, 0x0A, 0x00, 0xFF, 0x0D, 0x00, 0x7F, 0xFF, 0x00};
    mem[0x100] = 0x7F;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 1;
    state.regs.Y = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x02, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(5, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x03, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(10, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(15, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(20, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(25, cpu.state().cycles);

    // The below instruction crosses a page boundary
    state = cpu.state();
    state.regs.A = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(31, cpu.state().cycles);
}

TEST(cpu_std_instr, adczpg)
{
    uint8_t instr[] = {0x65, 0x00, 0x65, 0x01, 0x65, 0x02, 0x65, 0x03, 0x65, 0x04};
    uint8_t mem[] = {0x01, 0x01, 0xFF, 0xFF, 0x7F};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x02, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(3, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x03, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(9, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(15, cpu.state().cycles);
}

TEST(cpu_std_instr, adczpx)
{
    uint8_t instr[] = {0x75, 0x00, 0x75, 0x01, 0x75, 0x02, 0x75, 0x03, 0x75, 0x04};
    uint8_t mem[] = {0xCC, 0x01, 0x01, 0xFF, 0xFF, 0x7F};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 1;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x02, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x03, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 1;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(16, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(20, cpu.state().cycles);
}

TEST(cpu_std_instr, andabs)
{
    uint8_t instr[] = {0x2D, 0x00, 0x00, 0x2D, 0x01, 0x00};
    uint8_t mem[] = {0xF0, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0xFF;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xF0, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_std_instr, andabx)
{
    uint8_t instr[] = {0x3D, 0x00, 0x00, 0x3D, 0x01, 0x00, 0x3D, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0xF0, 0x00};
    mem[0x100] = 0x7F;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0xFF;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xF0, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    // The below crosses a page boundary
    state = cpu.state();
    state.regs.A = 0xFF;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x7F, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(13, cpu.state().cycles);
}

TEST(cpu_std_instr, andaby)
{
    uint8_t instr[] = {0x39, 0x00, 0x00, 0x39, 0x01, 0x00, 0x39, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0xF0, 0x00};
    mem[0x100] = 0x7F;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0xFF;
    state.regs.Y = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xF0, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    // The below crosses a page boundary
    state = cpu.state();
    state.regs.A = 0xFF;
    state.regs.Y = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x7F, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(13, cpu.state().cycles);
}

TEST(cpu_std_instr, andimm)
{
    uint8_t instr[] = {0x29, 0xF0, 0x29, 0x00};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0xFF;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xF0, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    ASSERT_EQ(0xC002, cpu.state().regs.PC);

    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    ASSERT_EQ(0xC004, cpu.state().regs.PC);
}

TEST(cpu_std_instr, andixx)
{
    uint8_t instr[] = {0x21, 0x01, 0x21, 0x04};
    uint8_t mem[] = {0xCC, 0xCC, 0x04, 0x00, 0xF0, 0x07, 0x00, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0xFF;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xF0, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, andixy)
{
    uint8_t instr[] = {0x31, 0x00, 0x31, 0x03, 0x31, 0x06};
    uint8_t mem[0x1000] = {0x01, 0x00, 0xF0, 0x04, 0x00, 0x00, 0xFF};
    mem[0x100] = 0x7F;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0xFF;
    state.regs.Y = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xF0, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(5, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(10, cpu.state().cycles);

    // The below instruction crosses a page boundary
    state = cpu.state();
    state.regs.A = 0xFF;
    state.regs.Y = 1;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x7F, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(16, cpu.state().cycles);
}

TEST(cpu_std_instr, andzpg)
{
    uint8_t instr[] = {0x25, 0x00, 0x25, 0x01};
    uint8_t mem[] = {0xF0, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0xFF;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xF0, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(3, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, andzpx)
{
    uint8_t instr[] = {0x35, 0x00, 0x35, 0x01};
    uint8_t mem[] = {0xCC, 0xF0, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0xFF;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xF0, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_std_instr, aslabs)
{
    uint8_t instr[] = {0x0E, 0x00, 0x00, 0x0E, 0x01, 0x00, 0x0E, 0x02, 0x00};
    uint8_t mem[] = {0x01, 0x40, 0x80};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val = c.readu8(0x0000);
    ASSERT_EQ(0x02, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, aslabx)
{
    uint8_t instr[] = {0x1E, 0x00, 0x00, 0x1E, 0x01, 0x00, 0x1E, 0x02, 0x00};
    uint8_t mem[] = {0xCC, 0x01, 0x40, 0x80};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val = c.readu8(0x0001);
    ASSERT_EQ(0x02, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(7, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(14, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0003);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(21, cpu.state().cycles);
}

TEST(cpu_std_instr, aslacc)
{
    uint8_t instr[] = {0x0A, 0x0A, 0x0A};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 1;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x02, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(2, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0x40;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0x80;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, aslzpg)
{
    uint8_t instr[] = {0x06, 0x00, 0x06, 0x01, 0x06, 0x02};
    uint8_t mem[] = {0x01, 0x40, 0x80};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val = c.readu8(0x0000);
    ASSERT_EQ(0x02, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(5, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(10, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(15, cpu.state().cycles);
}

TEST(cpu_std_instr, aslzpx)
{
    uint8_t instr[] = {0x16, 0x00, 0x16, 0x01, 0x16, 0x02};
    uint8_t mem[] = {0xCC, 0x01, 0x40, 0x80};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val = c.readu8(0x0001);
    ASSERT_EQ(0x02, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0003);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, bccrel)
{
    uint8_t instr[0x100] = {0x90, 0x01, 0x90, 0xFF, 0x90, 0x80};
    instr[0xEE] = 0x90;
    instr[0xEF] = 0x10;
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.cycles = 0;
    cpu.set_state(state);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(3, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC002, cpu.state().regs.PC);
    ASSERT_EQ(5, cpu.state().cycles);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(8, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC004, cpu.state().regs.PC);
    ASSERT_EQ(10, cpu.state().cycles);

    // Branch taken to a new page backwards
    state = cpu.state();
    state.regs.PC = 0xC004;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xBF86, cpu.state().regs.PC);
    ASSERT_EQ(14, cpu.state().cycles);

    // Branch taken to a new page forward
    state = cpu.state();
    state.regs.PC = 0xC0EE;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC100, cpu.state().regs.PC);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, bcsrel)
{
    uint8_t instr[0x100] = {0xB0, 0x01, 0xB0, 0xFF, 0xB0, 0x80};
    instr[0xEE] = 0xB0;
    instr[0xEF] = 0x10;
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.cycles = 0;
    cpu.set_state(state);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(3, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC002, cpu.state().regs.PC);
    ASSERT_EQ(5, cpu.state().cycles);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(8, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P &= ~carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC004, cpu.state().regs.PC);
    ASSERT_EQ(10, cpu.state().cycles);

    // Branch taken to a new page backwards
    state = cpu.state();
    state.regs.PC = 0xC004;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xBF86, cpu.state().regs.PC);
    ASSERT_EQ(14, cpu.state().cycles);

    // Branch taken to a new page forwards
    state = cpu.state();
    state.regs.PC = 0xC0EE;
    state.regs.P |= carry_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC100, cpu.state().regs.PC);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, beqrel)
{
    uint8_t instr[] = {0xF0, 0x01, 0xF0, 0xFF, 0xF0, 0x80};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.cycles = 0;
    cpu.set_state(state);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P |= zero_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(3, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P &= ~zero_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC002, cpu.state().regs.PC);
    ASSERT_EQ(5, cpu.state().cycles);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P |= zero_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(8, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P &= ~zero_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC004, cpu.state().regs.PC);
    ASSERT_EQ(10, cpu.state().cycles);

    // Branch taken to a new page backwards
    state = cpu.state();
    state.regs.PC = 0xC004;
    state.regs.P |= zero_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xBF86, cpu.state().regs.PC);
    ASSERT_EQ(14, cpu.state().cycles);
}

TEST(cpu_std_instr, bitabs)
{
    uint8_t instr[] = {0x2C, 0x00, 0x00, 0x2C, 0x01, 0x00};
    uint8_t mem[] = {0xFF, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0xFF;
    state.regs.P = 0;
    cpu.set_state(state);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_std_instr, bitzpg)
{
    uint8_t instr[] = {0x24, 0x00, 0x24, 0x01};
    uint8_t mem[] = {0xFF, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0xFF;
    state.regs.P = 0;
    cpu.set_state(state);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & overflow_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(3, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, bmirel)
{
    uint8_t instr[] = {0x30, 0x01, 0x30, 0xFF, 0x30, 0x80};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.cycles = 0;
    cpu.set_state(state);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P |= sign_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(3, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P &= ~sign_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC002, cpu.state().regs.PC);
    ASSERT_EQ(5, cpu.state().cycles);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P |= sign_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(8, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P &= ~sign_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC004, cpu.state().regs.PC);
    ASSERT_EQ(10, cpu.state().cycles);

    // Branch taken to a new page backwards
    state = cpu.state();
    state.regs.PC = 0xC004;
    state.regs.P |= sign_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xBF86, cpu.state().regs.PC);
    ASSERT_EQ(14, cpu.state().cycles);
}

TEST(cpu_std_instr, bnerel)
{
    uint8_t instr[] = {0xD0, 0x01, 0xD0, 0xFF, 0xD0, 0x80};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.cycles = 0;
    cpu.set_state(state);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P &= ~zero_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(3, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P |= zero_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC002, cpu.state().regs.PC);
    ASSERT_EQ(5, cpu.state().cycles);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P &= ~zero_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(8, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P |= zero_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC004, cpu.state().regs.PC);
    ASSERT_EQ(10, cpu.state().cycles);

    // Branch taken to a new page backwards
    state = cpu.state();
    state.regs.PC = 0xC004;
    state.regs.P &= ~zero_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xBF86, cpu.state().regs.PC);
    ASSERT_EQ(14, cpu.state().cycles);
}

TEST(cpu_std_instr, bplrel)
{
    uint8_t instr[] = {0x10, 0x01, 0x10, 0xFF, 0x10, 0x80};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.cycles = 0;
    cpu.set_state(state);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P &= ~sign_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(3, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P |= sign_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC002, cpu.state().regs.PC);
    ASSERT_EQ(5, cpu.state().cycles);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P &= ~sign_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(8, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P |= sign_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC004, cpu.state().regs.PC);
    ASSERT_EQ(10, cpu.state().cycles);

    // Branch taken to a new page backwards
    state = cpu.state();
    state.regs.PC = 0xC004;
    state.regs.P &= ~sign_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xBF86, cpu.state().regs.PC);
    ASSERT_EQ(14, cpu.state().cycles);
}

TEST(cpu_std_instr, brkimp)
{
    uint8_t instr[] = {0x00};
    uint8_t ram[1024];
    memset(ram, 0, sizeof(ram));
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    c.writeu8(0xFFFE, 0xEF);
    c.writeu8(0xFFFF, 0xBE);
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.S = 0xFF;
    cpu.set_state(state);

    cpu.run(1);
    uint16_t pushedPC = c.readu16(0x01FE);
    ASSERT_EQ((uint16_t)0xC001, pushedPC);
    uint8_t pushedS = c.readu8(0x01FD);
    ASSERT_EQ(0xFD, pushedS);
    ASSERT_EQ((uint16_t)0xBEEF, cpu.state().regs.PC);
    ASSERT_TRUE(cpu.state().regs.P & bit4_flag);
    ASSERT_TRUE(cpu.state().regs.P & disable_interrupts_flag);
    ASSERT_EQ(7, cpu.state().cycles);
}

TEST(cpu_std_instr, bvcrel)
{
    uint8_t instr[] = {0x50, 0x01, 0x50, 0xFF, 0x50, 0x80};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.cycles = 0;
    cpu.set_state(state);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P &= ~overflow_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(3, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P |= overflow_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC002, cpu.state().regs.PC);
    ASSERT_EQ(5, cpu.state().cycles);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P &= ~overflow_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(8, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P |= overflow_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC004, cpu.state().regs.PC);
    ASSERT_EQ(10, cpu.state().cycles);

    // Branch taken to a new page backwards
    state = cpu.state();
    state.regs.PC = 0xC004;
    state.regs.P &= ~overflow_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xBF86, cpu.state().regs.PC);
    ASSERT_EQ(14, cpu.state().cycles);
}

TEST(cpu_std_instr, bvsrel)
{
    uint8_t instr[] = {0x70, 0x01, 0x70, 0xFF, 0x70, 0x80};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.cycles = 0;
    cpu.set_state(state);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P |= overflow_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(3, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC000;
    state.regs.P &= ~overflow_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC002, cpu.state().regs.PC);
    ASSERT_EQ(5, cpu.state().cycles);

    // Branch taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P |= overflow_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC003, cpu.state().regs.PC);
    ASSERT_EQ(8, cpu.state().cycles);

    // Branch not taken
    state = cpu.state();
    state.regs.PC = 0xC002;
    state.regs.P &= ~overflow_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC004, cpu.state().regs.PC);
    ASSERT_EQ(10, cpu.state().cycles);

    // Branch taken to a new page backwards
    state = cpu.state();
    state.regs.PC = 0xC004;
    state.regs.P |= overflow_flag;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xBF86, cpu.state().regs.PC);
    ASSERT_EQ(14, cpu.state().cycles);
}

TEST(cpu_std_instr, clcimp)
{
    uint8_t instr[] = {0x18};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFE, cpu.state().regs.P);
    ASSERT_EQ(2, cpu.state().cycles);
}

TEST(cpu_std_instr, cldimp)
{
    uint8_t instr[] = {0xD8};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xF7, cpu.state().regs.P);
    ASSERT_EQ(2, cpu.state().cycles);
}

TEST(cpu_std_instr, cliimp)
{
    uint8_t instr[] = {0x58};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFB, cpu.state().regs.P);
    ASSERT_EQ(2, cpu.state().cycles);
}

TEST(cpu_std_instr, clvimp)
{
    uint8_t instr[] = {0xB8};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xBF, cpu.state().regs.P);
    ASSERT_EQ(2, cpu.state().cycles);
}

TEST(cpu_std_instr, cmpabs)
{
    uint8_t instr[] = {0xCD, 0x00, 0x00, 0xCD, 0x01, 0x00, 0xCD, 0x02, 0x00, 0xCD, 0x03, 0x00};
    uint8_t mem[] = {0x00, 0x10, 0x80, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x10;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(16, cpu.state().cycles);
}

TEST(cpu_std_instr, cmpabx)
{
    uint8_t instr[] = {0xDD, 0x00, 0x00, 0xDD, 0x01, 0x00, 0xDD, 0x02, 0x00, 0xDD, 0x03, 0x00, 0xDD, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0x00, 0x10, 0x80, 0xFF};
    mem[0x100] = 0xFF;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x10;
    state.regs.X = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(16, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(21, cpu.state().cycles);
}

TEST(cpu_std_instr, cmpaby)
{
    uint8_t instr[] = {0xD9, 0x00, 0x00, 0xD9, 0x01, 0x00, 0xD9, 0x02, 0x00, 0xD9, 0x03, 0x00, 0xD9, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0x00, 0x10, 0x80, 0xFF};
    mem[0x100] = 0xFF;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x10;
    state.regs.Y = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(16, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(21, cpu.state().cycles);
}

TEST(cpu_std_instr, cmpimm)
{
    uint8_t instr[] = {0xC9, 0x00, 0xC9, 0x10, 0xC9, 0x80, 0xC9, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x10;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(2, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_std_instr, cmpixx)
{
    uint8_t instr[] = {0xC1, 0x01, 0xC1, 0x04, 0xC1, 0x07, 0xC1, 0x0A};
    uint8_t mem[] = {0xCC, 0xCC, 0x04, 0x00, 0x00, 0x07, 0x00, 0x10, 0x0A, 0x00, 0x80, 0x0D, 0x00, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x10;
    state.regs.X = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(18, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(24, cpu.state().cycles);
}

TEST(cpu_std_instr, cmpixy)
{
    uint8_t instr[] = {0xD1, 0x00, 0xD1, 0x03, 0xD1, 0x06, 0xD1, 0x09, 0xD1, 0x0C};
    uint8_t mem[0x1000] = {0x01, 0x00, 0x00, 0x04, 0x00, 0x10, 0x07, 0x00, 0x80, 0x0A, 0x00, 0xFF, 0xFF, 0x00};
    mem[0x100] = 0xFF;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x10;
    state.regs.Y = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(5, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(10, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(15, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(20, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(26, cpu.state().cycles);
}

TEST(cpu_std_instr, cmpzpg)
{
    uint8_t instr[] = {0xC5, 0x00, 0xC5, 0x01, 0xC5, 0x02, 0xC5, 0x03};
    uint8_t mem[] = {0x00, 0x10, 0x80, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x10;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(3, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(9, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, cmpzpx)
{
    uint8_t instr[] = {0xD5, 0x00, 0xD5, 0x01, 0xD5, 0x02, 0xD5, 0x03};
    uint8_t mem[] = {0xCC, 0x00, 0x10, 0x80, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x10;
    state.regs.X = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(16, cpu.state().cycles);
}

TEST(cpu_std_instr, cpxabs)
{
    uint8_t instr[] = {0xEC, 0x00, 0x00, 0xEC, 0x01, 0x00, 0xEC, 0x02, 0x00, 0xEC, 0x03, 0x00};
    uint8_t mem[] = {0x00, 0x10, 0x80, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0x10;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(16, cpu.state().cycles);
}

TEST(cpu_std_instr, cpximm)
{
    uint8_t instr[] = {0xE0, 0x00, 0xE0, 0x10, 0xE0, 0x80, 0xE0, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0x10;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(2, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_std_instr, cpxzpg)
{
    uint8_t instr[] = {0xE4, 0x00, 0xE4, 0x01, 0xE4, 0x02, 0xE4, 0x03};
    uint8_t mem[] = {0x00, 0x10, 0x80, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0x10;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(3, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(9, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, cpyabs)
{
    uint8_t instr[] = {0xCC, 0x00, 0x00, 0xCC, 0x01, 0x00, 0xCC, 0x02, 0x00, 0xCC, 0x03, 0x00};
    uint8_t mem[] = {0x00, 0x10, 0x80, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0x10;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(16, cpu.state().cycles);
}

TEST(cpu_std_instr, cpyimm)
{
    uint8_t instr[] = {0xC0, 0x00, 0xC0, 0x10, 0xC0, 0x80, 0xC0, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0x10;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(2, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_std_instr, cpyzpg)
{
    uint8_t instr[] = {0xC4, 0x00, 0xC4, 0x01, 0xC4, 0x02, 0xC4, 0x03};
    uint8_t mem[] = {0x00, 0x10, 0x80, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0x10;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(3, cpu.state().cycles);

    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(9, cpu.state().cycles);

    cpu.run(1);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, decabs)
{
    uint8_t instr[] = {0xCE, 0x00, 0x00, 0xCE, 0x01, 0x00, 0xCE, 0x02, 0x00};
    uint8_t mem[] = {0x00, 0x01, 0x02};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0xFF, val);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, decabx)
{
    uint8_t instr[] = {0xDE, 0x00, 0x00, 0xDE, 0x01, 0x00, 0xDE, 0x02, 0x00};
    uint8_t mem[] = {0xCC, 0x00, 0x01, 0x02};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val = c.readu8(0x0001);
    ASSERT_EQ(0xFF, val);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(7, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(14, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0003);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(21, cpu.state().cycles);
}

TEST(cpu_std_instr, deczpg)
{
    uint8_t instr[] = {0xC6, 0x00, 0xC6, 0x01, 0xC6, 0x02};
    uint8_t mem[] = {0x00, 0x01, 0x02};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val = c.readu8(0x0000);
    ASSERT_EQ(0xFF, val);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(5, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(10, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(15, cpu.state().cycles);
}

TEST(cpu_std_instr, deczpx)
{
    uint8_t instr[] = {0xD6, 0x00, 0xD6, 0x01, 0xD6, 0x02};
    uint8_t mem[] = {0xCC, 0x00, 0x01, 0x02};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val = c.readu8(0x0001);
    ASSERT_EQ(0xFF, val);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    val = c.readu8(0x0003);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, deximp)
{
    uint8_t instr[] = {0xCA, 0xCA, 0xCA};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0x02;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.X);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, deyimp)
{
    uint8_t instr[] = {0x88, 0x88, 0x88};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0x02;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.Y);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, eorabs)
{
    uint8_t instr[] = {0x4D, 0x00, 0x00, 0x4D, 0x01, 0x00, 0x4D, 0x02, 0x00};
    uint8_t mem[] = {0xFF, 0xFF, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x88;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x77, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, eorabx)
{
    uint8_t instr[] = {0x5D, 0x00, 0x00, 0x5D, 0x01, 0x00, 0x5D, 0x02, 0x00, 0x5D, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0xFF, 0xFF, 0xFF};
    mem[0x100] = 0xFF;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x88;
    state.regs.X = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x77, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(17, cpu.state().cycles);
}

TEST(cpu_std_instr, eoraby)
{
    uint8_t instr[] = {0x59, 0x00, 0x00, 0x59, 0x01, 0x00, 0x59, 0x02, 0x00, 0x59, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0xFF, 0xFF, 0xFF};
    mem[0x100] = 0xFF;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x88;
    state.regs.Y = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x77, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(17, cpu.state().cycles);
}

TEST(cpu_std_instr, eorimm)
{
    uint8_t instr[] = {0x49, 0xFF, 0x49, 0xFF, 0x49, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x88;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x77, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, eorixx)
{
    uint8_t instr[] = {0x41, 0x01, 0x41, 0x04, 0x41, 0x07};
    uint8_t mem[] = {0xCC, 0xCC, 0x04, 0x00, 0xFF, 0x07, 0x00, 0xFF, 0x0A, 0x00, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x88;
    state.regs.X = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x77, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, eorixy)
{
    uint8_t instr[] = {0x51, 0x00, 0x51, 0x03, 0x51, 0x06, 0x51, 0x09};
    uint8_t mem[0x1000] = {0x01, 0x00, 0xFF, 0x04, 0x00, 0xFF, 0x07, 0x00, 0xFF, 0xFF, 0x00};
    mem[0x100] = 0xFF;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x88;
    state.regs.Y = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x77, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(5, cpu.state().cycles);

    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(10, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(15, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(21, cpu.state().cycles);
}

TEST(cpu_std_instr, eorzpg)
{
    uint8_t instr[] = {0x45, 0x00, 0x45, 0x01, 0x45, 0x02};
    uint8_t mem[] = {0xFF, 0xFF, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x88;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x77, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(3, cpu.state().cycles);
    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(9, cpu.state().cycles);
}

TEST(cpu_std_instr, eorzpx)
{
    uint8_t instr[] = {0x55, 0x00, 0x55, 0x01, 0x55, 0x02};
    uint8_t mem[] = {0xCC, 0xFF, 0xFF, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x88;
    state.regs.X = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x77, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    state = cpu.state();
    state.regs.A = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, incabs)
{
    uint8_t instr[] = {0xEE, 0x00, 0x00, 0xEE, 0x01, 0x00, 0xEE, 0x02, 0x00};
    uint8_t mem[] = {0xFE, 0xFF, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0xFF, val);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, incabx)
{
    uint8_t instr[] = {0xFE, 0x00, 0x00, 0xFE, 0x01, 0x00, 0xFE, 0x02, 0x00};
    uint8_t mem[] = {0xCC, 0xFE, 0xFF, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0xFF, val);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(7, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(14, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0003);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(21, cpu.state().cycles);
}

TEST(cpu_std_instr, inczpg)
{
    uint8_t instr[] = {0xE6, 0x00, 0xE6, 0x01, 0xE6, 0x02};
    uint8_t mem[] = {0xFE, 0xFF, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0xFF, val);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(5, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(10, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(15, cpu.state().cycles);
}

TEST(cpu_std_instr, inczpx)
{
    uint8_t instr[] = {0xF6, 0x00, 0xF6, 0x01, 0xF6, 0x02};
    uint8_t mem[] = {0xCC, 0xFE, 0xFF, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0xFF, val);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0003);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, inximp)
{
    uint8_t instr[] = {0xE8, 0xE8, 0xE8};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    state = cpu.state();
    state.regs.X = 0x7F;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.X);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    state = cpu.state();
    state.regs.X = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, inyimp)
{
    uint8_t instr[] = {0xC8, 0xC8, 0xC8};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    state = cpu.state();
    state.regs.Y = 0x7F;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.Y);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    state = cpu.state();
    state.regs.Y = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, jmpabs)
{
    uint8_t instr[] = {0x4C, 0xEF, 0xBE};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xBEEF, cpu.state().regs.PC);
    ASSERT_EQ(3, cpu.state().cycles);
}

TEST(cpu_std_instr, jmpind)
{
    uint8_t instr[] = {0x6C, 0x00, 0x00, 0x6C, 0xFF, 0x02};
    uint8_t mem[0x1000] = {0xEF, 0xBE};
    mem[0x02FF] = 0xAD;
    mem[0x0200] = 0xDE;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xBEEF, cpu.state().regs.PC);
    ASSERT_EQ(5, cpu.state().cycles);

    state = cpu.state(); state.regs.PC = 0xC003; cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xDEAD, cpu.state().regs.PC);
    ASSERT_EQ(10, cpu.state().cycles);
}

TEST(cpu_std_instr, jsrabs)
{
    uint8_t instr[] = {0x20, 0x34, 0x12};
    uint8_t ram[0x1000];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.S = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0x1234, cpu.state().regs.PC);
    ASSERT_EQ(0xFD, cpu.state().regs.S);
    uint16_t retAddr = c.readu16(0x01FE);
    ASSERT_EQ((uint16_t)0xC002, retAddr);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, ldaabs)
{
    uint8_t instr[] = {0xAD, 0x00, 0x00, 0xAD, 0x01, 0x00, 0xAD, 0x02, 0x00};
    uint8_t mem[] = {0x00, 0x45, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, ldaabx)
{
    uint8_t instr[] = {0xBD, 0x00, 0x00, 0xBD, 0x01, 0x00, 0xBD, 0x02, 0x00, 0xBD, 0xFF, 0x00};
    uint8_t mem[0x101];
    memset(mem, 0xCC, ARRAYSIZE(mem));
    mem[0x0001] = 0x00;
    mem[0x0002] = 0x45;
    mem[0x0003] = 0xFF;
    mem[0x0100] = 0x42;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    // The below instruction crosses a page boundary so it takes an extra
    // cycle
    cpu.run(1);
    ASSERT_EQ(0x42, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(17, cpu.state().cycles);
}

TEST(cpu_std_instr, ldaaby)
{
    uint8_t instr[] = {0xB9, 0x00, 0x00, 0xB9, 0x01, 0x00, 0xB9, 0x02, 0x00, 0xB9, 0xFF, 0x00};
    uint8_t mem[0x101];
    memset(mem, 0xCC, ARRAYSIZE(mem));
    mem[0x0001] = 0x00;
    mem[0x0002] = 0x45;
    mem[0x0003] = 0xFF;
    mem[0x0100] = 0x42;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    // Next instruction crosses a page boundary so it should take
    // an extra cycle.
    cpu.run(1);
    ASSERT_EQ(0x42, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(17, cpu.state().cycles);
}

TEST(cpu_std_instr, ldaimm)
{
    uint8_t instr[] = {0xA9, 0x00, 0xA9, 0x45, 0xA9, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, ldaixx)
{
    uint8_t instr[] = {0xA1, 0x01, 0xA1, 0x03, 0xA1, 0x06, 0xA1, 0xFE, 0xA1, 0xFF};
    uint8_t mem[0x1000] = {0x01, 0xCC, 0x03, 0x00, 0x06, 0x00, 0x45, 0x09, 0x00, 0xFF};
    mem[0x80] = 0x00;
    mem[0x81] = 0x02;
    mem[0x200] = 0x5A;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    c.writeu8(0x00FF, 0x23);
    c.writeu8(0x0123, 0x69);
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(18, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x69, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(24, cpu.state().cycles);

    state = cpu.state(); state.regs.X = 0x81; cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x5A, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(30, cpu.state().cycles);
}

TEST(cpu_std_instr, ldaixy)
{
    uint8_t instr[] = {0xB1, 0x00, 0xB1, 0x03, 0xB1, 0x06, 0xB1, 0x09};
    uint8_t mem[0x200];
    memset(mem, 0xCC, sizeof(mem));
    mem[0x0000] = 0x01;
    mem[0x0001] = 0x00;
    mem[0x0002] = 0x00;
    mem[0x0003] = 0x04;
    mem[0x0004] = 0x00;
    mem[0x0005] = 0x45;
    mem[0x0006] = 0x07;
    mem[0x0007] = 0x00;
    mem[0x0008] = 0xFF;
    mem[0x0009] = 0xFF;
    mem[0x000A] = 0x00;
    mem[0x0100] = 0x42;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(5, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(10, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(15, cpu.state().cycles);

    // The below instruction crosses a page boundary so it
    // takes an extra cycle
    cpu.run(1);
    ASSERT_EQ(0x42, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(21, cpu.state().cycles);
    // TODO: add zero-page wraparound logic
}

TEST(cpu_std_instr, ldazpg)
{
    uint8_t instr[] = {0xA5, 0x00, 0xA5, 0x01, 0xA5, 0x02};
    uint8_t mem[] = {0x00, 0x45, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(3, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(9, cpu.state().cycles);
}

TEST(cpu_std_instr, ldazpx)
{
    uint8_t instr[] = {0xB5, 0x00, 0xB5, 0x01, 0xB5, 0x02};
    uint8_t mem[] = {0xCC, 0x00, 0x45, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, ldxabs)
{
    uint8_t instr[] = {0xAE, 0x00, 0x00, 0xAE, 0x01, 0x00, 0xAE, 0x02, 0x00};
    uint8_t mem[] = {0x00, 0x45, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.X);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, ldxaby)
{
    uint8_t instr[] = {0xBE, 0x00, 0x00, 0xBE, 0x01, 0x00, 0xBE, 0x02, 0x00, 0xBE, 0xFF, 0x00};
    uint8_t mem[0x101];
    memset(mem, 0xCC, ARRAYSIZE(mem));
    mem[0x0001] = 0x00;
    mem[0x0002] = 0x45;
    mem[0x0003] = 0xFF;
    mem[0x0100] = 0x42;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.X);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    // The below instruction crosses a page boundary so it
    // takes an extra cycle
    cpu.run(1);
    ASSERT_EQ(0x42, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(17, cpu.state().cycles);
}

TEST(cpu_std_instr, ldximm)
{
    uint8_t instr[] = {0xA2, 0x00, 0xA2, 0x45, 0xA2, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.X);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, ldxzpg)
{
    uint8_t instr[] = {0xA6, 0x00, 0xA6, 0x01, 0xA6, 0x02};
    uint8_t mem[] = {0x00, 0x45, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(3, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.X);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(9, cpu.state().cycles);
}

TEST(cpu_std_instr, ldxzpy)
{
    uint8_t instr[] = {0xB6, 0x00, 0xB6, 0x01, 0xB6, 0x02, 0xB6, 0xFF};
    uint8_t mem[] = {0xCC, 0x00, 0x45, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.X);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xCC, cpu.state().regs.X);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(16, cpu.state().cycles);
}

TEST(cpu_std_instr, ldyabs)
{
    uint8_t instr[] = {0xAC, 0x00, 0x00, 0xAC, 0x01, 0x00, 0xAC, 0x02, 0x00};
    uint8_t mem[] = {0x00, 0x45, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.Y);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, ldyabx)
{
    uint8_t instr[] = {0xBC, 0x00, 0x00, 0xBC, 0x01, 0x00, 0xBC, 0x02, 0x00, 0xBC, 0xFF, 0x00};
    uint8_t mem[0x101];
    memset(mem, 0xCC, sizeof(mem));
    mem[1] = 0x00;
    mem[2] = 0x45;
    mem[3] = 0xFF;
    mem[0x100] = 0x42;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.Y);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    // The below instruction crosses a page boundary so it takes an extra
    // cycle
    cpu.run(1);
    ASSERT_EQ(0x42, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(17, cpu.state().cycles);
}

TEST(cpu_std_instr, ldyimm)
{
    uint8_t instr[] = {0xA0, 0x00, 0xA0, 0x45, 0xA0, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.Y);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, ldyzpg)
{
    uint8_t instr[] = {0xA4, 0x00, 0xA4, 0x01, 0xA4, 0x02};
    uint8_t mem[] = {0x00, 0x45, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(3, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.Y);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(9, cpu.state().cycles);
}

TEST(cpu_std_instr, ldyzpx)
{
    uint8_t instr[] = {0xB4, 0x00, 0xB4, 0x01, 0xB4, 0x02, 0xB4, 0xFF};
    uint8_t mem[] = {0xCC, 0x00, 0x45, 0xFF};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x45, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.Y);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    // This wraps to the beginning of the zero page
    cpu.run(1);
    ASSERT_EQ(0xCC, cpu.state().regs.Y);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(16, cpu.state().cycles);
}

TEST(cpu_std_instr, lsrabs)
{
    uint8_t instr[] = {0x4E, 0x00, 0x00, 0x4E, 0x01, 0x00, 0x4E, 0x02, 0x00};
    uint8_t mem[] = {0x03, 0x01, 0x00};
    uint8_t val;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, lsrabx)
{
    uint8_t instr[] = {0x5E, 0x00, 0x00, 0x5E, 0x01, 0x00, 0x5E, 0x02, 0x00};
    uint8_t mem[] = {0xCC, 0x03, 0x01, 0x00};
    uint8_t val;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(7, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(14, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0003);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(21, cpu.state().cycles);
}

TEST(cpu_std_instr, lsracc)
{
    uint8_t instr[] = {0x4A, 0x4A, 0x4A};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x03;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, lsrzpg)
{
    uint8_t instr[] = {0x46, 0x00, 0x46, 0x01, 0x46, 0x02};
    uint8_t mem[] = {0x03, 0x01, 0x00};
    uint8_t val;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(5, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(10, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(15, cpu.state().cycles);
}

TEST(cpu_std_instr, lsrzpx)
{
    uint8_t instr[] = {0x56, 0x00, 0x56, 0x01, 0x56, 0x02};
    uint8_t mem[] = {0xCC, 0x03, 0x01, 0x00};
    uint8_t val;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0003);
    ASSERT_EQ(0x00, val);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, nopimp)
{
    uint8_t instr[] = {0xEA};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ((uint16_t)0xC001, cpu.state().regs.PC);
    ASSERT_EQ(2, cpu.state().cycles);
}

TEST(cpu_std_instr, oraabs)
{
    uint8_t instr[] = {0x0D, 0x00, 0x00, 0x0D, 0x01, 0x00, 0x0D, 0x02, 0x00};
    uint8_t mem[] = {0x00, 0x0F, 0xF0};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x0F, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, oraabx)
{
    uint8_t instr[] = {0x1D, 0x00, 0x00, 0x1D, 0x01, 0x00, 0x1D, 0x02, 0x00, 0x1D, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0x00, 0x0F, 0xF0};
    mem[0x100] = 0x07;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0;
    state.regs.X = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x0F, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    // The below instruction crosses a page boundary
    state = cpu.state(); state.regs.A = 0x70; cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x77, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(17, cpu.state().cycles);
}

TEST(cpu_std_instr, oraaby)
{
    uint8_t instr[] = {0x19, 0x00, 0x00, 0x19, 0x01, 0x00, 0x19, 0x02, 0x00, 0x19, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0x00, 0x0F, 0xF0};
    mem[0x100] = 0x07;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0;
    state.regs.Y = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x0F, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    // The below instruction crosses a page boundary
    state = cpu.state(); state.regs.A = 0x70; cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x77, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(17, cpu.state().cycles);
}

TEST(cpu_std_instr, oraimm)
{
    uint8_t instr[] = {0x09, 0x00, 0x09, 0x0F, 0x09, 0xF0};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x0F, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, oraixx)
{
    uint8_t instr[] = {0x01, 0x01, 0x01, 0x04, 0x01, 0x07};
    uint8_t mem[] = {0xCC, 0xCC, 0x04, 0x00, 0x00, 0x07, 0x00, 0x0F, 0x0A, 0x00, 0xF0};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0;
    state.regs.X = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x0F, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, oraixy)
{
    uint8_t instr[] = {0x11, 0x00, 0x11, 0x03, 0x11, 0x06, 0x11, 0x09};
    uint8_t mem[0x1000] = {0x01, 0x00, 0x00, 0x04, 0x00, 0x0F, 0x07, 0x00, 0xF0, 0xFF, 0x00};
    mem[0x100] = 0x07;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0;
    state.regs.Y = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(5, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x0F, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(10, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(15, cpu.state().cycles);

    state = cpu.state(); state.regs.A = 0x70; cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x77, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(21, cpu.state().cycles);
}

TEST(cpu_std_instr, orazpg)
{
    uint8_t instr[] = {0x05, 0x00, 0x05, 0x01, 0x05, 0x02};
    uint8_t mem[] = {0x00, 0x0F, 0xF0};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(3, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x0F, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(9, cpu.state().cycles);
}

TEST(cpu_std_instr, orazpx)
{
    uint8_t instr[] = {0x15, 0x00, 0x15, 0x01, 0x15, 0x02};
    uint8_t mem[] = {0xCC, 0x00, 0x0F, 0xF0};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0;
    state.regs.X = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x0F, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, phaimp)
{
    uint8_t instr[] = {0x48};
    uint8_t ram[4096];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0xAB;
    state.regs.S = 0xFF;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFE, cpu.state().regs.S);
    uint8_t val = c.readu8(0x01FF);
    ASSERT_EQ(0xAB, val);
    ASSERT_EQ(3, cpu.state().cycles);
}

TEST(cpu_std_instr, phpimp)
{
    uint8_t instr[] = {0x08, 0x08};
    uint8_t ram[4096];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.S = 0xFF;
    state.regs.P = 0xFF;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    ASSERT_EQ(0xFE, cpu.state().regs.S);
    val = c.readu8(0x01FF);
    ASSERT_EQ(0xFF, val);
    ASSERT_EQ(3, cpu.state().cycles);
    // On NES, P() is | with 0x10 before pushing to stack
    state = cpu.state();
    state.regs.P = 0x0F;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFD, cpu.state().regs.S);
    val = c.readu8(0x01FE);
    ASSERT_EQ(0x1F, val);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, plaimp)
{
    uint8_t instr[] = {0x68};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    c.writeu8(0x01FF, 0x78);
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.S = 0xFE;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x78, cpu.state().regs.A);
    ASSERT_EQ(4, cpu.state().cycles);
}

TEST(cpu_std_instr, plpimp)
{
    // PLP sets the 6th bit and clears the 5th bit
    uint8_t instr[] = {0x28};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    c.writeu8(0x01FF, 0x10);
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.S = 0xFE;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x20, cpu.state().regs.P);
    ASSERT_EQ(4, cpu.state().cycles);
}

TEST(cpu_std_instr, rolabs)
{
    uint8_t instr[] = {0x2E, 0x00, 0x00, 0x2E, 0x01, 0x00, 0x2E, 0x02, 0x00};
    uint8_t mem[] = {0x80, 0x00, 0x40};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, rolabx)
{
    uint8_t instr[] = {0x3E, 0x00, 0x00, 0x3E, 0x01, 0x00, 0x3E, 0x02, 0x00};
    uint8_t mem[] = {0xCC, 0x80, 0x00, 0x40};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(7, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(14, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0003);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(21, cpu.state().cycles);
}

TEST(cpu_std_instr, rolacc)
{
    uint8_t instr[] = {0x2A, 0x2A, 0x2A};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x80;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    state = cpu.state();
    state.regs.A = 0x00;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    state = cpu.state();
    state.regs.A = 0x40;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, rolzpg)
{
    uint8_t instr[] = {0x26, 0x00, 0x26, 0x01, 0x26, 0x02};
    uint8_t mem[] = {0x80, 0x00, 0x40};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(5, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(10, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(15, cpu.state().cycles);
}

TEST(cpu_std_instr, rolzpx)
{
    uint8_t instr[] = {0x36, 0x00, 0x36, 0x01, 0x36, 0x02};
    uint8_t mem[] = {0xCC, 0x80, 0x00, 0x40};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0002);
    ASSERT_EQ(0x01, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0003);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, rorabs)
{
    uint8_t instr[] = {0x6E, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x6E, 0x00, 0x00};
    uint8_t mem[] = {0x01};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val = c.readu8(0x0000);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0x40, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, rorabx)
{
    uint8_t instr[] = {0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00};
    uint8_t mem[] = {0xCC, 0x01};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    state.regs.A = 1;
    state.regs.X = 1;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(7, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(14, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x40, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(21, cpu.state().cycles);
}

TEST(cpu_std_instr, roracc)
{
    uint8_t instr[] = {0x6A, 0x6A, 0x6A};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x40, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, rorzpg)
{
    uint8_t instr[] = {0x66, 0x00, 0x66, 0x00, 0x66, 0x00};
    uint8_t mem[] = {0x01};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(5, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(10, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0000);
    ASSERT_EQ(0x40, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(15, cpu.state().cycles);
}

TEST(cpu_std_instr, rorzpx)
{
    uint8_t instr[] = {0x76, 0x00, 0x76, 0x00, 0x76, 0x00};
    uint8_t mem[] = {0xCC, 0x01};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 1;
    state.regs.X = 1;
    state.regs.P = 0;
    cpu.set_state(state);
    uint8_t val;
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x00, val);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x80, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(12, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0001);
    ASSERT_EQ(0x40, val);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, rtiimp)
{
    uint8_t instr[] = {0x40};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    c.writeu8(0x01FD, 0x0F);
    c.writeu16(0x01FE, 0xC123);
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.S = 0xFC;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.S);
    ASSERT_EQ(0x2F, cpu.state().regs.P);
    ASSERT_EQ((uint16_t)0xC123, cpu.state().regs.PC);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, rtsimp)
{
    uint8_t instr[] = {0x60};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    c.writeu16(0x01FE, 0xC122);
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.S = 0xFD;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.S);
    ASSERT_EQ((uint16_t)0xC123, cpu.state().regs.PC);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, sbcabs)
{
    uint8_t instr[] = {0xED, 0x00, 0x00, 0xED, 0x01, 0x00, 0xED, 0x02, 0x00};
    uint8_t mem[] = {0x01, 0x01, 0x01};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x03;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, sbcabx)
{
    uint8_t instr[] = {0xFD, 0x00, 0x00, 0xFD, 0x01, 0x00, 0xFD, 0x02, 0x00, 0xFD, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0x01, 0x01, 0x01};
    mem[0x100] = 0x01;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x03;
    state.regs.X = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    state = cpu.state(); state.regs.A = 0x0F; state.regs.P = 0x01; cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x0E, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(17, cpu.state().cycles);
}

TEST(cpu_std_instr, sbcaby)
{
    uint8_t instr[] = {0xF9, 0x00, 0x00, 0xF9, 0x01, 0x00, 0xF9, 0x02, 0x00, 0xF9, 0xFF, 0x00};
    uint8_t mem[0x1000] = {0xCC, 0x01, 0x01, 0x01};
    mem[0x100] = 0x01;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x03;
    state.regs.Y = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(8, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    state = cpu.state(); state.regs.A = 0x0F; state.regs.P = 0x01; cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x0E, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(17, cpu.state().cycles);
}

TEST(cpu_std_instr, sbcimm)
{
    uint8_t instr[] = {0xE9, 0x01, 0xE9, 0x01, 0xE9, 0x01};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x03;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(2, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, sbcixx)
{
    uint8_t instr[] = {0xE1, 0x01, 0xE1, 0x04, 0xE1, 0x07};
    uint8_t mem[] = {0xCC, 0xCC, 0x04, 0x00, 0x01, 0x07, 0x00, 0x01, 0x0A, 0x00, 0x01};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x03;
    state.regs.X = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(6, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(12, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(18, cpu.state().cycles);
}

TEST(cpu_std_instr, sbcixy)
{
    uint8_t instr[] = {0xF1, 0x00, 0xF1, 0x03, 0xF1, 0x06, 0xF1, 0x09};
    uint8_t mem[0x1000] = {0x01, 0x00, 0x01, 0x04, 0x00, 0x01, 0x07, 0x00, 0x01, 0xFF, 0x00};
    mem[0x100] = 0x01;
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x03;
    state.regs.Y = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(5, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(10, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(15, cpu.state().cycles);

    state = cpu.state(); state.regs.A = 0x0F; state.regs.P = 0x01; cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x0E, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(21, cpu.state().cycles);
}

TEST(cpu_std_instr, sbczpg)
{
    uint8_t instr[] = {0xE5, 0x00, 0xE5, 0x01, 0xE5, 0x02};
    uint8_t mem[] = {0x01, 0x01, 0x01};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x03;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(3, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(9, cpu.state().cycles);
}

TEST(cpu_std_instr, sbczpx)
{
    uint8_t instr[] = {0xF5, 0x00, 0xF5, 0x01, 0xF5, 0x02};
    uint8_t mem[] = {0xCC, 0x01, 0x01, 0x01};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x03;
    state.regs.X = 0x01;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x01, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(8, cpu.state().cycles);
    cpu.run(1);
    ASSERT_EQ(0xFF, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & carry_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & overflow_flag);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, secimp)
{
    uint8_t instr[] = {0x38};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & carry_flag);
    ASSERT_EQ(2, cpu.state().cycles);
}

TEST(cpu_std_instr, sedimp)
{
    uint8_t instr[] = {0xF8};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & decimal_flag);
    ASSERT_EQ(2, cpu.state().cycles);
}

TEST(cpu_std_instr, seiimp)
{
    uint8_t instr[] = {0x78};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.P = 0;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_TRUE(cpu.state().regs.P & disable_interrupts_flag);
    ASSERT_EQ(2, cpu.state().cycles);
}

TEST(cpu_std_instr, staabs)
{
    uint8_t instr[] = {0x8D, 0x00, 0x00};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x58;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0000);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(4, cpu.state().cycles);
}

TEST(cpu_std_instr, staabx)
{
    uint8_t instr[] = {0x9D, 0x00, 0x00};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x58;
    state.regs.X = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0001);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(5, cpu.state().cycles);
}

TEST(cpu_std_instr, staaby)
{
    uint8_t instr[] = {0x99, 0x00, 0x00};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x58;
    state.regs.Y = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0001);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(5, cpu.state().cycles);
}

TEST(cpu_std_instr, staixx)
{
    uint8_t instr[] = {0x81, 0x00, 0x81, 0xFE};
    uint8_t mem[1024] = {0x01, 0x03, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    c.writeu8(0xFF, 0x23);
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x58;
    state.regs.X = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0003);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(6, cpu.state().cycles);
    cpu.run(1);
    val = c.readu8(0x0123);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(12, cpu.state().cycles);
}

TEST(cpu_std_instr, staixy)
{
    uint8_t instr[] = {0x91, 0x00};
    uint8_t mem[1024] = {0x01, 0x00};
    test_mem c(instr, ARRAYSIZE(instr), mem, ARRAYSIZE(mem));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x58;
    state.regs.Y = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0002);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, stazpg)
{
    uint8_t instr[] = {0x85, 0x00};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x58;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0000);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(3, cpu.state().cycles);
}

TEST(cpu_std_instr, stazpx)
{
    uint8_t instr[] = {0x95, 0x00};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x58;
    state.regs.X = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0001);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(4, cpu.state().cycles);
}

TEST(cpu_std_instr, stxabs)
{
    uint8_t instr[] = {0x8E, 0x00, 0x00};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0x58;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0000);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(4, cpu.state().cycles);
}

TEST(cpu_std_instr, stxzpg)
{
    uint8_t instr[] = {0x86, 0x00};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0x58;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0000);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(3, cpu.state().cycles);
}

TEST(cpu_std_instr, stxzpy)
{
    uint8_t instr[] = {0x96, 0x00, 0x96, 0xFF};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0x58;
    state.regs.Y = 0x01;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0001);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(4, cpu.state().cycles);

    cpu.run(1);
    ASSERT_EQ(0x58, ram[0]);
    ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_std_instr, styabs)
{
    uint8_t instr[] = {0x8C, 0x00, 0x00};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0x58;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0000);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(4, cpu.state().cycles);
}

TEST(cpu_std_instr, styzpg)
{
    uint8_t instr[] = {0x84, 0x00};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0x58;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0000);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(3, cpu.state().cycles);
}

TEST(cpu_std_instr, styzpx)
{
    uint8_t instr[] = {0x94, 0x00, 0x94, 0xFF};
    uint8_t ram[1024];
    test_mem c(instr, ARRAYSIZE(instr), ram, ARRAYSIZE(ram));
    m6502 cpu(&c);

    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0x01;
    state.regs.Y = 0x58;
    cpu.set_state(state);
    cpu.run(1);
    uint8_t val;
    val = c.readu8(0x0001);
    ASSERT_EQ(0x58, val);
    ASSERT_EQ(4, cpu.state().cycles);

    // The below tests zero-page wraparound
    cpu.run(1);
    ASSERT_EQ(0x58, ram[0]);
    ASSERT_EQ(8, cpu.state().cycles);
}

TEST(cpu_std_instr, taximp)
{
    uint8_t instr[] = {0xAA, 0xAA, 0xAA};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x23;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x23, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    state = cpu.state();
    state.regs.A = 0x00;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    state = cpu.state();
    state.regs.A = 0x80;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.X);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, tayimp)
{
    uint8_t instr[] = {0xA8, 0xA8, 0xA8};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.A = 0x23;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x23, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    state = cpu.state();
    state.regs.A = 0x00;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.Y);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    state = cpu.state();
    state.regs.A = 0x80;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.Y);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, tsximp)
{
    uint8_t instr[] = {0xBA, 0xBA, 0xBA};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.S = 0x23;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x23, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    state = cpu.state();
    state.regs.S = 0x00;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.X);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    state = cpu.state();
    state.regs.S = 0x80;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.X);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, txaimp)
{
    uint8_t instr[] = {0x8A, 0x8A, 0x8A};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0x23;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x23, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    state = cpu.state();
    state.regs.X = 0x00;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    state = cpu.state();
    state.regs.X = 0x80;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}

TEST(cpu_std_instr, txsimp)
{
    uint8_t instr[] = {0x9A};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.X = 0x23;
    state.regs.S = 0x00;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x23, cpu.state().regs.S);
    ASSERT_EQ(2, cpu.state().cycles);
}

TEST(cpu_std_instr, tyaimp)
{
    uint8_t instr[] = {0x98, 0x98, 0x98};
    test_mem c(instr, ARRAYSIZE(instr));
    m6502 cpu(&c);
    m6502_state state = cpu.state();
    state.regs.PC = 0xC000;
    state.cycles = 0;
    state.regs.Y = 0x23;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x23, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(2, cpu.state().cycles);
    state = cpu.state();
    state.regs.Y = 0x00;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x00, cpu.state().regs.A);
    ASSERT_FALSE(cpu.state().regs.P & sign_flag);
    ASSERT_TRUE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(4, cpu.state().cycles);
    state = cpu.state();
    state.regs.Y = 0x80;
    cpu.set_state(state);
    cpu.run(1);
    ASSERT_EQ(0x80, cpu.state().regs.A);
    ASSERT_TRUE(cpu.state().regs.P & sign_flag);
    ASSERT_FALSE(cpu.state().regs.P & zero_flag);
    ASSERT_EQ(6, cpu.state().cycles);
}
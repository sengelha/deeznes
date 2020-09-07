#include "test_mem.h"
#include <cpu/m6502.h>
#include <gtest/gtest.h>
#include <tuple>

using namespace deeznes::cpu;

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

class m6502_state_ostream_tests
    : public ::testing::TestWithParam<
          std::tuple<int, int, int, int, int, int, int, std::string>> {};

TEST_P(m6502_state_ostream_tests, ostream_format) {
    m6502_state state;
    state.regs.A = std::get<0>(GetParam());
    state.regs.X = std::get<1>(GetParam());
    state.regs.Y = std::get<2>(GetParam());
    state.regs.P = std::get<3>(GetParam());
    state.regs.S = std::get<4>(GetParam());
    state.regs.PC = std::get<5>(GetParam());
    state.cycles = std::get<6>(GetParam());

    std::string expected = std::get<7>(GetParam());
    std::stringstream ss;
    ss << state;
    std::string actual = ss.str();
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_CASE_P(
    m6502_state, m6502_state_ostream_tests,
    ::testing::Values(
        std::make_tuple(0, 0, 0, 0, 0, 0, 0,
                        "A:00 X:00 Y:00 P:00 S:00 PC:0000 CYC:0"),
        std::make_tuple(0x74, 0xBD, 0x01, 0x32, 0x44, 0x98D8, 1982734,
                        "A:74 X:BD Y:01 P:32 S:44 PC:98D8 CYC:1982734")));

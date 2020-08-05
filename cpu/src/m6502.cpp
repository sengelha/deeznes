#include <cassert>
#include <tuple>
#include <cpu/m6502.h>

namespace deeznes
{
namespace cpu
{

uint_fast32_t m6502::run(uint_fast32_t maxcycles)
{
    /* The indices of labels in the dispatch_table are the relevant opcodes */
    static constexpr void *dispatch_table[] = {
        &&brkimp, &&oraixx, &&nopimp, &&sloixx, &&nopzpg, &&orazpg, &&aslzpg, &&slozpg, // $00-$07
        &&phpimp, &&oraimm, &&aslacc, &&nopimp, &&nopabs, &&oraabs, &&aslabs, &&sloabs, // $08-$0F
        &&bplrel, &&oraixy, &&nopimp, &&sloixy, &&nopzpx, &&orazpx, &&aslzpx, &&slozpx, // $10-$17
        &&clcimp, &&oraaby, &&nopimp, &&sloaby, &&nopabx, &&oraabx, &&aslabx, &&sloabx, // $18-$1F
        &&jsrabs, &&andixx, &&nopimp, &&rlaixx, &&bitzpg, &&andzpg, &&rolzpg, &&rlazpg, // $20-$27
        &&plpimp, &&andimm, &&rolacc, &&nopimp, &&bitabs, &&andabs, &&rolabs, &&rlaabs, // $28-$2F
        &&bmirel, &&andixy, &&nopimp, &&rlaixy, &&nopzpx, &&andzpx, &&rolzpx, &&rlazpx, // $30-$37
        &&secimp, &&andaby, &&nopimp, &&rlaaby, &&nopabx, &&andabx, &&rolabx, &&rlaabx, // $38-$3F
        &&rtiimp, &&eorixx, &&nopimp, &&sreixx, &&nopzpg, &&eorzpg, &&lsrzpg, &&srezpg, // $40-$47
        &&phaimp, &&eorimm, &&lsracc, &&nopimp, &&jmpabs, &&eorabs, &&lsrabs, &&sreabs, // $48-$4F
        &&bvcrel, &&eorixy, &&nopimp, &&sreixy, &&nopzpx, &&eorzpx, &&lsrzpx, &&srezpx, // $50-$57
        &&cliimp, &&eoraby, &&nopimp, &&sreaby, &&nopabx, &&eorabx, &&lsrabx, &&sreabx, // $58-$5F
        &&rtsimp, &&adcixx, &&nopimp, &&rraixx, &&nopzpg, &&adczpg, &&rorzpg, &&rrazpg, // $60-$67
        &&plaimp, &&adcimm, &&roracc, &&nopimp, &&jmpind, &&adcabs, &&rorabs, &&rraabs, // $68-$6F
        &&bvsrel, &&adcixy, &&nopimp, &&rraixy, &&nopzpx, &&adczpx, &&rorzpx, &&rrazpx, // $70-$77
        &&seiimp, &&adcaby, &&nopimp, &&rraaby, &&nopabx, &&adcabx, &&rorabx, &&rraabx, // $78-$7F
        &&nopimm, &&staixx, &&nopimp, &&saxixx, &&styzpg, &&stazpg, &&stxzpg, &&saxzpg, // $80-$87
        &&deyimp, &&nopimp, &&txaimp, &&nopimp, &&styabs, &&staabs, &&stxabs, &&saxabs, // $88-$8F
        &&bccrel, &&staixy, &&nopimp, &&nopimp, &&styzpx, &&stazpx, &&stxzpy, &&saxzpy, // $90-$97
        &&tyaimp, &&staaby, &&txsimp, &&nopimp, &&nopimp, &&staabx, &&nopimp, &&nopimp, // $98-$9F
        &&ldyimm, &&ldaixx, &&ldximm, &&laxixx, &&ldyzpg, &&ldazpg, &&ldxzpg, &&laxzpg, // $A0-$A7
        &&tayimp, &&ldaimm, &&taximp, &&nopimp, &&ldyabs, &&ldaabs, &&ldxabs, &&laxabs, // $A8-$AF
        &&bcsrel, &&ldaixy, &&nopimp, &&laxixy, &&ldyzpx, &&ldazpx, &&ldxzpy, &&laxzpy, // $B0-$B7
        &&clvimp, &&ldaaby, &&tsximp, &&nopimp, &&ldyabx, &&ldaabx, &&ldxaby, &&laxaby, // $B8-$BF
        &&cpyimm, &&cmpixx, &&nopimp, &&dcpixx, &&cpyzpg, &&cmpzpg, &&deczpg, &&dcpzpg, // $C0-$C7
        &&inyimp, &&cmpimm, &&deximp, &&nopimp, &&cpyabs, &&cmpabs, &&decabs, &&dcpabs, // $C8-$CF
        &&bnerel, &&cmpixy, &&nopimp, &&dcpixy, &&nopzpx, &&cmpzpx, &&deczpx, &&dcpzpx, // $D0-$D7
        &&cldimp, &&cmpaby, &&nopimp, &&dcpaby, &&nopabx, &&cmpabx, &&decabx, &&dcpabx, // $D8-$DF
        &&cpximm, &&sbcixx, &&nopimp, &&isbixx, &&cpxzpg, &&sbczpg, &&inczpg, &&isbzpg, // $E0-$E7
        &&inximp, &&sbcimm, &&nopimp, &&sbcimm, &&cpxabs, &&sbcabs, &&incabs, &&isbabs, // $E8-$EF
        &&beqrel, &&sbcixy, &&nopimp, &&isbixy, &&nopzpx, &&sbczpx, &&inczpx, &&isbzpx, // $F0-$F7
        &&sedimp, &&sbcaby, &&nopimp, &&isbaby, &&nopabx, &&sbcabx, &&incabx, &&isbabx, // $F8-$FF
    };
#define DISPATCH()                                               \
    do                                                           \
    {                                                            \
        uint_fast32_t ncycles = state_.cycles - starting_cycles; \
        if (ncycles >= maxcycles)                                \
            return ncycles;                                      \
        goto *dispatch_table[cb_->readu8(state_.regs.PC++)];     \
    } while (0)

    auto starting_cycles = state_.cycles;
    DISPATCH();

adcabs:
{
    uint8_t val = readu8abs();
    uint16_t result = state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) && ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

adcabx:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    uint16_t result = state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) && ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

adcaby:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8aby();
    uint16_t result = state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) && ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

adcimm:
{
    uint8_t val = readu8imm();
    uint16_t result = state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) && ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 2;
    DISPATCH();
}

adcixx:
{
    uint8_t val = readu8ixx();
    uint16_t result = state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) && ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

adcixy:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    uint16_t result = state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) && ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
    DISPATCH();
}

adczpg:
{
    uint8_t val = readu8zpg();
    uint16_t result = state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) && ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

adczpx:
{
    uint8_t val = readu8zpx();
    uint16_t result = state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) && ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

andabs:
{
    uint8_t val = readu8abs();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

andabx:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

andaby:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8aby();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

andimm:
{
    uint8_t val = readu8imm();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
    DISPATCH();
}

andixx:
{
    uint8_t val = readu8ixx();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

andixy:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
    DISPATCH();
}

andzpg:
{
    uint8_t val = readu8zpg();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

andzpx:
{
    uint8_t val = readu8zpx();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

aslabs:
{
    uint8_t val = readu8abs();
    set_carry(val & 0x80);
    val <<= 1;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8abs(val);
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

aslabx:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    set_carry(val & 0x80);
    val <<= 1;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8abx(val);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

aslacc:
{
    set_carry(state_.regs.A & 0x80);
    state_.regs.A <<= 1;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.cycles += 2;
    DISPATCH();
}

aslzpg:
{
    uint8_t val = readu8zpg();
    set_carry(val & 0x80);
    val <<= 1;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8zpg(val);
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

aslzpx:
{
    uint8_t val = readu8zpx();
    set_carry(val & 0x80);
    val <<= 1;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8zpx(val);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

bccrel:
{
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (!(state_.regs.P & carry_flag))
    {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
    DISPATCH();
}

bcsrel:
{
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (state_.regs.P & carry_flag)
    {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
    DISPATCH();
}

beqrel:
{
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (state_.regs.P & zero_flag)
    {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
    DISPATCH();
}

bitabs:
{
    uint8_t val = readu8abs();
    set_sign(val & 0x80);
    set_overflow(val & 0x40);
    set_zero((val & state_.regs.A) == 0);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

bitzpg:
{
    uint8_t val = readu8zpg();
    set_sign(val & 0x80);
    set_overflow(val & 0x40);
    set_zero((val & state_.regs.A) == 0);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

bmirel:
{
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (state_.regs.P & sign_flag)
    {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
    DISPATCH();
}

bnerel:
{
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (!(state_.regs.P & zero_flag))
    {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
    DISPATCH();
}

bplrel:
{
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (!(state_.regs.P & sign_flag))
    {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
    DISPATCH();
}

brkimp:
{
    pushu16(state_.regs.PC);
    pushu8(state_.regs.S);
    state_.regs.P |= bit4_flag;
    state_.regs.P |= disable_interrupts_flag;
    state_.regs.PC = cb_->readu16(0xFFFE);
    state_.cycles += 7;
    DISPATCH();
}

bvcrel:
{
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (!(state_.regs.P & overflow_flag))
    {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
    DISPATCH();
}

bvsrel:
{
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (state_.regs.P & overflow_flag)
    {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
    DISPATCH();
}

clcimp:
{
    state_.regs.P &= ~carry_flag;
    state_.cycles += 2;
    DISPATCH();
}

cldimp:
{
    state_.regs.P &= ~decimal_flag;
    state_.cycles += 2;
    DISPATCH();
}

cliimp:
{
    state_.regs.P &= ~disable_interrupts_flag;
    state_.cycles += 2;
    DISPATCH();
}

clvimp:
{
    state_.regs.P &= ~overflow_flag;
    state_.cycles += 2;
    DISPATCH();
}

cmpabs:
{
    uint8_t u8 = readu8abs();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

cmpabx:
{
    uint8_t u8;
    bool page_crossed;
    std::tie(u8, page_crossed) = readu8abx();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

cmpaby:
{
    uint8_t u8;
    bool page_crossed;
    std::tie(u8, page_crossed) = readu8aby();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

cmpimm:
{
    uint8_t u8 = readu8imm();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
    DISPATCH();
}

cmpixx:
{
    uint8_t u8 = readu8ixx();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

cmpixy:
{
    uint8_t u8;
    bool page_crossed;
    std::tie(u8, page_crossed) = readu8ixy();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
    DISPATCH();
}

cmpzpg:
{
    uint8_t u8 = readu8zpg();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

cmpzpx:
{
    uint8_t u8 = readu8zpx();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

cpxabs:
{
    uint8_t u8 = readu8abs();
    uint16_t val = state_.regs.X - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

cpximm:
{
    uint8_t u8 = readu8imm();
    uint16_t val = state_.regs.X - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
    DISPATCH();
}

cpxzpg:
{
    uint8_t u8 = readu8zpg();
    uint16_t val = state_.regs.X - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

cpyabs:
{
    uint8_t u8 = readu8abs();
    uint16_t val = state_.regs.Y - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

cpyimm:
{
    uint8_t u8 = readu8imm();
    uint16_t val = state_.regs.Y - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
    DISPATCH();
}

cpyzpg:
{
    uint8_t u8 = readu8zpg();
    uint16_t val = state_.regs.Y - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

dcpabs:
{
    uint8_t val = readu8abs() - 1;
    writeu8abs(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

dcpabx:
{
    uint8_t val = readu8abx().first - 1;
    writeu8abx(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

dcpaby:
{
    uint8_t val = readu8aby().first - 1;
    writeu8aby(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

dcpixx:
{
    uint8_t val = readu8ixx() - 1;
    writeu8ixx(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

dcpixy:
{
    uint8_t val = readu8ixy().first - 1;
    writeu8ixy(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

dcpzpg:
{
    uint8_t val = readu8zpg() - 1;
    writeu8zpg(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

dcpzpx:
{
    uint8_t val = readu8zpx() - 1;
    writeu8zpx(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

decabs:
{
    uint8_t val = readu8abs() - 1;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8abs(val);
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

decabx:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    --val;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8abx(val);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

deczpg:
{
    uint8_t val = readu8zpg() - 1;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8zpg(val);
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

deczpx:
{
    uint8_t val = readu8zpx() - 1;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8zpx(val);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

deximp:
{
    --state_.regs.X;
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.cycles += 2;
    DISPATCH();
}

deyimp:
{
    --state_.regs.Y;
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.cycles += 2;
    DISPATCH();
}

eorabs:
{
    uint8_t val = readu8abs();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

eorabx:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

eoraby:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8aby();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

eorimm:
{
    uint8_t val = readu8imm();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
    DISPATCH();
}

eorixx:
{
    uint8_t val = readu8ixx();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

eorixy:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
    DISPATCH();
}

eorzpg:
{
    uint8_t val = readu8zpg();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

eorzpx:
{
    uint8_t val = readu8zpx();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

incabs:
{
    uint8_t val = readu8abs();
    ++val;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8abs(val);
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

incabx:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    ++val;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8abx(val);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

inczpg:
{
    uint8_t val = readu8zpg();
    ++val;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8zpg(val);
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

inczpx:
{
    uint8_t val = readu8zpx();
    ++val;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8zpx(val);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

inximp:
{
    ++state_.regs.X;
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.cycles += 2;
    DISPATCH();
}

inyimp:
{
    ++state_.regs.Y;
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.cycles += 2;
    DISPATCH();
}

isbabs:
{
    uint8_t val = readu8abs() + 1;
    writeu8abs(val);
    uint16_t temp = state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

isbabx:
{
    uint8_t val = readu8abx().first + 1;
    writeu8abx(val);
    uint16_t temp = state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

isbaby:
{
    uint8_t val = readu8aby().first + 1;
    writeu8aby(val);
    uint16_t temp = state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

isbixx:
{
    uint8_t val = readu8ixx() + 1;
    writeu8ixx(val);
    uint16_t temp = state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

isbixy:
{
    uint8_t val = readu8ixy().first + 1;
    writeu8ixy(val);
    uint16_t temp = state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

isbzpg:
{
    uint8_t val = readu8zpg() + 1;
    writeu8zpg(val);
    uint16_t temp = state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

isbzpx:
{
    uint8_t val = readu8zpx() + 1;
    writeu8zpx(val);
    uint16_t temp = state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

jmpabs:
{
    state_.regs.PC = readu16imm();
    state_.cycles += 3;
    DISPATCH();
}

jmpind:
{
    state_.regs.PC = readu16pgwrap(readu16imm());
    state_.cycles += 5;
    DISPATCH();
}

jsrabs:
{
    uint16_t val = readu16imm();
    pushu16(state_.regs.PC + 1);
    state_.regs.PC = val;
    state_.cycles += 6;
    DISPATCH();
}

laxabs:
{
    uint8_t val = readu8abs();
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

laxaby:
{
    uint8_t val = readu8aby().first;
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

laxixx:
{
    uint8_t val = readu8ixx();
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    ++state_.regs.PC;
    state_.cycles += 6;
    DISPATCH();
}

laxixy:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    ++state_.regs.PC;
    state_.cycles += (page_crossed ? 6 : 5);
    DISPATCH();
}

laxzpg:
{
    uint8_t val = readu8zpg();
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    ++state_.regs.PC;
    state_.cycles += 3;
    DISPATCH();
}

laxzpy:
{
    uint8_t val = readu8zpy();
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    ++state_.regs.PC;
    state_.cycles += 4;
    DISPATCH();
}

ldaabs:
{
    state_.regs.A = readu8abs();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

ldaabx:
{
    bool page_crossed;
    std::tie(state_.regs.A, page_crossed) = readu8abx();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

ldaaby:
{
    bool page_crossed;
    std::tie(state_.regs.A, page_crossed) = readu8aby();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

ldaimm:
{
    state_.regs.A = readu8imm();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
    DISPATCH();
}

ldaixx:
{
    state_.regs.A = readu8ixx();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

ldaixy:
{
    bool page_crossed;
    std::tie(state_.regs.A, page_crossed) = readu8ixy();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
    DISPATCH();
}

ldazpg:
{
    state_.regs.A = readu8zpg();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

ldazpx:
{
    state_.regs.A = readu8zpx();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

ldxabs:
{
    state_.regs.X = readu8abs();
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

ldxaby:
{
    bool page_crossed;
    std::tie(state_.regs.X, page_crossed) = readu8aby();
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

ldximm:
{
    state_.regs.X = readu8imm();
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
    DISPATCH();
}

ldxzpg:
{
    state_.regs.X = readu8zpg();
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

ldxzpy:
{
    state_.regs.X = readu8zpy();
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

ldyabs:
{
    state_.regs.Y = readu8abs();
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

ldyabx:
{
    bool page_crossed;
    std::tie(state_.regs.Y, page_crossed) = readu8abx();
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

ldyimm:
{
    state_.regs.Y = readu8imm();
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
    DISPATCH();
}

ldyzpg:
{
    state_.regs.Y = readu8zpg();
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

ldyzpx:
{
    state_.regs.Y = readu8zpx();
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

lsrabs:
{
    uint8_t val = readu8abs();
    set_carry(val & 0x01);
    val >>= 1;
    set_zero(val == 0);
    state_.regs.P &= ~sign_flag;
    writeu8abs(val);
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

lsrabx:
{
    uint8_t val = readu8abx().first;
    set_carry(val & 0x01);
    val >>= 1;
    set_zero(val == 0);
    state_.regs.P &= ~sign_flag;
    writeu8abx(val);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

lsracc:
{
    set_carry(state_.regs.A & 0x01);
    state_.regs.A >>= 1;
    set_zero(state_.regs.A == 0);
    state_.regs.P &= ~sign_flag;
    state_.cycles += 2;
    DISPATCH();
}

lsrzpg:
{
    uint8_t val = readu8zpg();
    set_carry(val & 0x01);
    val >>= 1;
    set_zero(val == 0);
    state_.regs.P &= ~sign_flag;
    writeu8zpg(val);
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

lsrzpx:
{
    uint8_t val = readu8zpx();
    set_carry(val & 0x01);
    val >>= 1;
    set_zero(val == 0);
    state_.regs.P &= ~sign_flag;
    writeu8zpx(val);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

nopabs:
{
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

nopabx:
{
    bool page_crossed = readu8abx().second;
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

nopimm:
{
    ++state_.regs.PC;
    state_.cycles += 2;
    DISPATCH();
}

nopimp:
{
    state_.cycles += 2;
    DISPATCH();
}

nopzpg:
{
    ++state_.regs.PC;
    state_.cycles += 3;
    DISPATCH();
}

nopzpx:
{
    ++state_.regs.PC;
    state_.cycles += 4;
    DISPATCH();
}

oraabs:
{
    state_.regs.A |= readu8abs();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

oraabx:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    state_.regs.A |= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

oraaby:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8aby();
    state_.regs.A |= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

oraimm:
{
    state_.regs.A |= readu8imm();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
    DISPATCH();
}

oraixx:
{
    state_.regs.A |= readu8ixx();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

oraixy:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    state_.regs.A |= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
    DISPATCH();
}

orazpg:
{
    state_.regs.A |= readu8zpg();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

orazpx:
{
    state_.regs.A |= readu8zpx();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

phaimp:
{
    pushu8(state_.regs.A);
    state_.cycles += 3;
    DISPATCH();
}

phpimp:
{
    pushu8(state_.regs.P | bit4_flag);
    state_.cycles += 3;
    DISPATCH();
}

plaimp:
{
    state_.regs.A = popu8();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.cycles += 4;
    DISPATCH();
}

plpimp:
{
    uint8_t val = popu8();
    state_.regs.P = (val | 0x20) & 0xEF;
    state_.cycles += 4;
    DISPATCH();
}

rlaabs:
{
    uint8_t val = readu8abs();
    uint8_t new_val = val << 1;
    if (state_.regs.P & carry_flag)
        new_val |= 0x01;
    writeu8abs(new_val);
    state_.regs.A &= new_val;
    set_carry(val & 0x80);
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

rlaabx:
{
    uint8_t val = readu8abx().first;
    uint8_t new_val = val << 1;
    if (state_.regs.P & carry_flag)
        new_val |= 0x01;
    writeu8abx(new_val);
    state_.regs.A &= new_val;
    set_carry(val & 0x80);
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

rlaaby:
{
    uint8_t val = readu8aby().first;
    uint8_t new_val = val << 1;
    if (state_.regs.P & carry_flag)
        new_val |= 0x01;
    writeu8aby(new_val);
    state_.regs.A &= new_val;
    set_carry(val & 0x80);
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

rlaixx:
{
    uint8_t val = readu8ixx();
    uint8_t new_val = val << 1;
    if (state_.regs.P & carry_flag)
        new_val |= 0x01;
    writeu8ixx(new_val);
    state_.regs.A &= new_val;
    set_carry(val & 0x80);
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

rlaixy:
{
    uint8_t val = readu8ixy().first;
    uint8_t new_val = val << 1;
    if (state_.regs.P & carry_flag)
        new_val |= 0x01;
    writeu8ixy(new_val);
    state_.regs.A &= new_val;
    set_carry(val & 0x80);
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

rlazpg:
{
    uint8_t val = readu8zpg();
    uint8_t new_val = val << 1;
    if (state_.regs.P & carry_flag)
        new_val |= 0x01;
    writeu8zpg(new_val);
    state_.regs.A &= new_val;
    set_carry(val & 0x80);
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

rlazpx:
{
    uint8_t val = readu8zpx();
    uint8_t new_val = val << 1;
    if (state_.regs.P & carry_flag)
        new_val |= 0x01;
    writeu8zpx(new_val);
    state_.regs.A &= new_val;
    set_carry(val & 0x80);
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

rolabs:
{
    uint8_t val = readu8abs();
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(val & 0x80);
    val <<= 1;
    if (was_carry)
        val |= 0x01;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8abs(val);
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

rolabx:
{
    uint8_t val = readu8abx().first;
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(val & 0x80);
    val <<= 1;
    if (was_carry)
        val |= 0x01;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8abx(val);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

rolacc:
{
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(state_.regs.A & 0x80);
    state_.regs.A <<= 1;
    if (was_carry)
        state_.regs.A |= 0x01;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.cycles += 2;
    DISPATCH();
}

rolzpg:
{
    uint8_t val = readu8zpg();
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(val & 0x80);
    val <<= 1;
    if (was_carry)
        val |= 0x01;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8zpg(val);
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

rolzpx:
{
    uint8_t val = readu8zpx();
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(val & 0x80);
    val <<= 1;
    if (was_carry)
        val |= 0x01;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8zpx(val);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

rorabs:
{
    uint8_t val = readu8abs();
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(val & 0x01);
    val >>= 1;
    if (was_carry)
        val |= 0x80;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8abs(val);
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

rorabx:
{
    uint8_t val = readu8abx().first;
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(val & 0x01);
    val >>= 1;
    if (was_carry)
        val |= 0x80;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8abx(val);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

roracc:
{
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(state_.regs.A & 0x01);
    state_.regs.A >>= 1;
    if (was_carry)
        state_.regs.A |= 0x80;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.cycles += 2;
    DISPATCH();
}

rorzpg:
{
    uint8_t val = readu8zpg();
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(val & 0x01);
    val >>= 1;
    if (was_carry)
        val |= 0x80;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8zpg(val);
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

rorzpx:
{
    uint8_t val = readu8zpx();
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(val & 0x01);
    val >>= 1;
    if (was_carry)
        val |= 0x80;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8zpx(val);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

rraabs:
{
    uint8_t val = readu8abs();
    bool was_lsb_set = val & 0x01;
    val >>= 1;
    if (state_.regs.P & carry_flag)
        val |= 0x80;
    writeu8abs(val);
    uint16_t temp = val + state_.regs.A + (was_lsb_set ? 1 : 0);
    set_carry(temp > 0xFF);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false); // TODO
    state_.regs.A = (uint8_t)temp;
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

rraabx:
{
    uint8_t val = readu8abx().first;
    bool was_lsb_set = val & 0x01;
    val >>= 1;
    if (state_.regs.P & carry_flag)
        val |= 0x80;
    writeu8abx(val);
    uint16_t temp = val + state_.regs.A + (was_lsb_set ? 1 : 0);
    set_carry(temp > 0xFF);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false); // TODO
    state_.regs.A = (uint8_t)temp;
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

rraaby:
{
    uint8_t val = readu8aby().first;
    bool was_lsb_set = val & 0x01;
    val >>= 1;
    if (state_.regs.P & carry_flag)
        val |= 0x80;
    writeu8aby(val);
    uint16_t temp = val + state_.regs.A + (was_lsb_set ? 1 : 0);
    set_carry(temp > 0xFF);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false); // TODO
    state_.regs.A = (uint8_t)temp;
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

rraixx:
{
    uint8_t val = readu8ixx();
    bool was_lsb_set = val & 0x01;
    val >>= 1;
    if (state_.regs.P & carry_flag)
        val |= 0x80;
    writeu8ixx(val);
    uint16_t temp = val + state_.regs.A + (was_lsb_set ? 1 : 0);
    set_carry(temp > 0xFF);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false); // TODO
    state_.regs.A = (uint8_t)temp;
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

rraixy:
{
    uint8_t val = readu8ixy().first;
    bool was_lsb_set = val & 0x01;
    val >>= 1;
    if (state_.regs.P & carry_flag)
        val |= 0x80;
    writeu8ixy(val);
    uint16_t temp = val + state_.regs.A + (was_lsb_set ? 1 : 0);
    set_carry(temp > 0xFF);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false); // TODO
    state_.regs.A = (uint8_t)temp;
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

rrazpg:
{
    uint8_t val = readu8zpg();
    bool was_lsb_set = val & 0x01;
    val >>= 1;
    if (state_.regs.P & carry_flag)
        val |= 0x80;
    writeu8zpg(val);
    uint16_t temp = val + state_.regs.A + (was_lsb_set ? 1 : 0);
    set_carry(temp > 0xFF);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false); // TODO
    state_.regs.A = (uint8_t)temp;
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

rrazpx:
{
    uint8_t val = readu8zpx();
    bool was_lsb_set = val & 0x01;
    val >>= 1;
    if (state_.regs.P & carry_flag)
        val |= 0x80;
    writeu8zpx(val);
    uint16_t temp = val + state_.regs.A + (was_lsb_set ? 1 : 0);
    set_carry(temp > 0xFF);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false); // TODO
    state_.regs.A = (uint8_t)temp;
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

rtiimp:
{
    state_.regs.P = popu8() | bit5_flag;
    state_.regs.PC = popu16();
    state_.cycles += 6;
    DISPATCH();
}

rtsimp:
{
    state_.regs.PC = popu16() + 1;
    state_.cycles += 6;
    DISPATCH();
}

saxabs:
{
    writeu8abs(state_.regs.A & state_.regs.X);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

saxixx:
{
    writeu8ixx(state_.regs.A & state_.regs.X);
    ++state_.regs.PC;
    state_.cycles += 6;
    DISPATCH();
}

saxzpg:
{
    writeu8zpg(state_.regs.A & state_.regs.X);
    ++state_.regs.PC;
    state_.cycles += 3;
    DISPATCH();
}

saxzpy:
{
    writeu8zpy(state_.regs.A & state_.regs.X);
    ++state_.regs.PC;
    state_.cycles += 4;
    DISPATCH();
}

sbcabs:
{
    uint8_t val = readu8abs();
    uint16_t result = state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) && ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

sbcabx:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    uint16_t result = state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) && ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

sbcaby:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8aby();
    uint16_t result = state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) && ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
    DISPATCH();
}

sbcimm:
{
    uint8_t val = readu8imm();
    uint16_t result = state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) && ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 2;
    DISPATCH();
}

sbcixx:
{
    uint8_t val = readu8ixx();
    uint16_t result = state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) && ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

sbcixy:
{
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    uint16_t result = state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) && ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
    DISPATCH();
}

sbczpg:
{
    uint8_t val = readu8zpg();
    uint16_t result = state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) && ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

sbczpx:
{
    uint8_t val = readu8zpx();
    uint16_t result = state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) && ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

secimp:
{
    state_.regs.P |= carry_flag;
    state_.cycles += 2;
    DISPATCH();
}

sedimp:
{
    state_.regs.P |= decimal_flag;
    state_.cycles += 2;
    DISPATCH();
}

seiimp:
{
    state_.regs.P |= disable_interrupts_flag;
    state_.cycles += 2;
    DISPATCH();
}

sloabs:
{
    uint8_t prevVal = readu8abs();
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8abs(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

sloabx:
{
    uint8_t prevVal = readu8abx().first;
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8abx(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

sloaby:
{
    uint8_t prevVal = readu8aby().first;
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8aby(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

sloixx:
{
    uint8_t prevVal = readu8ixx();
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8ixx(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

sloixy:
{
    uint8_t prevVal = readu8ixy().first;
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8ixy(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

slozpg:
{
    uint8_t prevVal = readu8zpg();
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8zpg(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

slozpx:
{
    uint8_t prevVal = readu8zpx();
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8zpx(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

sreabs:
{
    uint8_t prev_val = readu8abs();
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8abs(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 6;
    DISPATCH();
}

sreabx:
{
    uint8_t prev_val = readu8abx().first;
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8abx(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

sreaby:
{
    uint8_t prev_val = readu8aby().first;
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8aby(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
    DISPATCH();
}

sreixx:
{
    uint8_t prev_val = readu8ixx();
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8ixx(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

sreixy:
{
    uint8_t prev_val = readu8ixy().first;
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8ixy(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
    DISPATCH();
}

srezpg:
{
    uint8_t prev_val = readu8zpg();
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8zpg(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 5;
    DISPATCH();
}

srezpx:
{
    uint8_t prev_val = readu8zpx();
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8zpx(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

staabs:
{
    writeu8abs(state_.regs.A);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

staabx:
{
    writeu8abx(state_.regs.A);
    state_.regs.PC += 2;
    state_.cycles += 5;
    DISPATCH();
}

staaby:
{
    writeu8aby(state_.regs.A);
    state_.regs.PC += 2;
    state_.cycles += 5;
    DISPATCH();
}

staixx:
{
    writeu8ixx(state_.regs.A);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

staixy:
{
    writeu8ixy(state_.regs.A);
    state_.regs.PC += 1;
    state_.cycles += 6;
    DISPATCH();
}

stazpg:
{
    writeu8zpg(state_.regs.A);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

stazpx:
{
    writeu8zpx(state_.regs.A);
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

stxabs:
{
    writeu8abs(state_.regs.X);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

stxzpg:
{
    writeu8zpg(state_.regs.X);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

stxzpy:
{
    writeu8zpy(state_.regs.X);
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

styabs:
{
    writeu8abs(state_.regs.Y);
    state_.regs.PC += 2;
    state_.cycles += 4;
    DISPATCH();
}

styzpg:
{
    writeu8zpg(state_.regs.Y);
    state_.regs.PC += 1;
    state_.cycles += 3;
    DISPATCH();
}

styzpx:
{
    writeu8zpx(state_.regs.Y);
    state_.regs.PC += 1;
    state_.cycles += 4;
    DISPATCH();
}

taximp:
{
    state_.regs.X = state_.regs.A;
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.cycles += 2;
    DISPATCH();
}

tayimp:
{
    state_.regs.Y = state_.regs.A;
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.cycles += 2;
    DISPATCH();
}

tsximp:
{
    state_.regs.X = state_.regs.S;
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.cycles += 2;
    DISPATCH();
}

txaimp:
{
    state_.regs.A = state_.regs.X;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.cycles += 2;
    DISPATCH();
}

txsimp:
{
    state_.regs.S = state_.regs.X;
    state_.cycles += 2;
    DISPATCH();
}

tyaimp:
{
    state_.regs.A = state_.regs.Y;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.cycles += 2;
    DISPATCH();
}
}

} // namespace cpu
} // namespace deeznes

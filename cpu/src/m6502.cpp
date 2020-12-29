#include <boost/assert.hpp>
#include <boost/format.hpp>
#include <cpu/m6502.h>
#include <tuple>

namespace deeznes {
namespace cpu {

uint_fast32_t m6502::run(uint_fast32_t maxcycles) {
    uint_fast32_t starting_cycles = state_.cycles;

    for (;;) {
        uint8_t opcode = cb_->readu8(state_.regs.PC++);
        switch (opcode) {
        case 0x00:
            brkimp();
            break;
        case 0x01:
            oraixx();
            break;
        case 0x02:
            nopimp();
            break;
        case 0x03:
            sloixx();
            break;
        case 0x04:
            nopzpg();
            break;
        case 0x05:
            orazpg();
            break;
        case 0x06:
            aslzpg();
            break;
        case 0x07:
            slozpg();
            break;
        case 0x08:
            phpimp();
            break;
        case 0x09:
            oraimm();
            break;
        case 0x0A:
            aslacc();
            break;
        case 0x0B:
            nopimp();
            break;
        case 0x0C:
            nopabs();
            break;
        case 0x0D:
            oraabs();
            break;
        case 0x0E:
            aslabs();
            break;
        case 0x0F:
            sloabs();
            break;
        case 0x10:
            bplrel();
            break;
        case 0x11:
            oraixy();
            break;
        case 0x12:
            nopimp();
            break;
        case 0x13:
            sloixy();
            break;
        case 0x14:
            nopzpx();
            break;
        case 0x15:
            orazpx();
            break;
        case 0x16:
            aslzpx();
            break;
        case 0x17:
            slozpx();
            break;
        case 0x18:
            clcimp();
            break;
        case 0x19:
            oraaby();
            break;
        case 0x1A:
            nopimp();
            break;
        case 0x1B:
            sloaby();
            break;
        case 0x1C:
            nopabx();
            break;
        case 0x1D:
            oraabx();
            break;
        case 0x1E:
            aslabx();
            break;
        case 0x1F:
            sloabx();
            break;
        case 0x20:
            jsrabs();
            break;
        case 0x21:
            andixx();
            break;
        case 0x22:
            nopimp();
            break;
        case 0x23:
            rlaixx();
            break;
        case 0x24:
            bitzpg();
            break;
        case 0x25:
            andzpg();
            break;
        case 0x26:
            rolzpg();
            break;
        case 0x27:
            rlazpg();
            break;
        case 0x28:
            plpimp();
            break;
        case 0x29:
            andimm();
            break;
        case 0x2A:
            rolacc();
            break;
        case 0x2B:
            nopimp();
            break;
        case 0x2C:
            bitabs();
            break;
        case 0x2D:
            andabs();
            break;
        case 0x2E:
            rolabs();
            break;
        case 0x2F:
            rlaabs();
            break;
        case 0x30:
            bmirel();
            break;
        case 0x31:
            andixy();
            break;
        case 0x32:
            nopimp();
            break;
        case 0x33:
            rlaixy();
            break;
        case 0x34:
            nopzpx();
            break;
        case 0x35:
            andzpx();
            break;
        case 0x36:
            rolzpx();
            break;
        case 0x37:
            rlazpx();
            break;
        case 0x38:
            secimp();
            break;
        case 0x39:
            andaby();
            break;
        case 0x3A:
            nopimp();
            break;
        case 0x3B:
            rlaaby();
            break;
        case 0x3C:
            nopabx();
            break;
        case 0x3D:
            andabx();
            break;
        case 0x3E:
            rolabx();
            break;
        case 0x3F:
            rlaabx();
            break;
        case 0x40:
            rtiimp();
            break;
        case 0x41:
            eorixx();
            break;
        case 0x42:
            nopimp();
            break;
        case 0x43:
            sreixx();
            break;
        case 0x44:
            nopzpg();
            break;
        case 0x45:
            eorzpg();
            break;
        case 0x46:
            lsrzpg();
            break;
        case 0x47:
            srezpg();
            break;
        case 0x48:
            phaimp();
            break;
        case 0x49:
            eorimm();
            break;
        case 0x4A:
            lsracc();
            break;
        case 0x4B:
            nopimp();
            break;
        case 0x4C:
            jmpabs();
            break;
        case 0x4D:
            eorabs();
            break;
        case 0x4E:
            lsrabs();
            break;
        case 0x4F:
            sreabs();
            break;
        case 0x50:
            bvcrel();
            break;
        case 0x51:
            eorixy();
            break;
        case 0x52:
            nopimp();
            break;
        case 0x53:
            sreixy();
            break;
        case 0x54:
            nopzpx();
            break;
        case 0x55:
            eorzpx();
            break;
        case 0x56:
            lsrzpx();
            break;
        case 0x57:
            srezpx();
            break;
        case 0x58:
            cliimp();
            break;
        case 0x59:
            eoraby();
            break;
        case 0x5A:
            nopimp();
            break;
        case 0x5B:
            sreaby();
            break;
        case 0x5C:
            nopabx();
            break;
        case 0x5D:
            eorabx();
            break;
        case 0x5E:
            lsrabx();
            break;
        case 0x5F:
            sreabx();
            break;
        case 0x60:
            rtsimp();
            break;
        case 0x61:
            adcixx();
            break;
        case 0x62:
            nopimp();
            break;
        case 0x63:
            rraixx();
            break;
        case 0x64:
            nopzpg();
            break;
        case 0x65:
            adczpg();
            break;
        case 0x66:
            rorzpg();
            break;
        case 0x67:
            rrazpg();
            break;
        case 0x68:
            plaimp();
            break;
        case 0x69:
            adcimm();
            break;
        case 0x6A:
            roracc();
            break;
        case 0x6B:
            nopimp();
            break;
        case 0x6C:
            jmpind();
            break;
        case 0x6D:
            adcabs();
            break;
        case 0x6E:
            rorabs();
            break;
        case 0x6F:
            rraabs();
            break;
        case 0x70:
            bvsrel();
            break;
        case 0x71:
            adcixy();
            break;
        case 0x72:
            nopimp();
            break;
        case 0x73:
            rraixy();
            break;
        case 0x74:
            nopzpx();
            break;
        case 0x75:
            adczpx();
            break;
        case 0x76:
            rorzpx();
            break;
        case 0x77:
            rrazpx();
            break;
        case 0x78:
            seiimp();
            break;
        case 0x79:
            adcaby();
            break;
        case 0x7A:
            nopimp();
            break;
        case 0x7B:
            rraaby();
            break;
        case 0x7C:
            nopabx();
            break;
        case 0x7D:
            adcabx();
            break;
        case 0x7E:
            rorabx();
            break;
        case 0x7F:
            rraabx();
            break;
        case 0x80:
            nopimm();
            break;
        case 0x81:
            staixx();
            break;
        case 0x82:
            nopimp();
            break;
        case 0x83:
            saxixx();
            break;
        case 0x84:
            styzpg();
            break;
        case 0x85:
            stazpg();
            break;
        case 0x86:
            stxzpg();
            break;
        case 0x87:
            saxzpg();
            break;
        case 0x88:
            deyimp();
            break;
        case 0x89:
            nopimp();
            break;
        case 0x8A:
            txaimp();
            break;
        case 0x8B:
            nopimp();
            break;
        case 0x8C:
            styabs();
            break;
        case 0x8D:
            staabs();
            break;
        case 0x8E:
            stxabs();
            break;
        case 0x8F:
            saxabs();
            break;
        case 0x90:
            bccrel();
            break;
        case 0x91:
            staixy();
            break;
        case 0x92:
            nopimp();
            break;
        case 0x93:
            nopimp();
            break;
        case 0x94:
            styzpx();
            break;
        case 0x95:
            stazpx();
            break;
        case 0x96:
            stxzpy();
            break;
        case 0x97:
            saxzpy();
            break;
        case 0x98:
            tyaimp();
            break;
        case 0x99:
            staaby();
            break;
        case 0x9A:
            txsimp();
            break;
        case 0x9B:
            nopimp();
            break;
        case 0x9C:
            nopimp();
            break;
        case 0x9D:
            staabx();
            break;
        case 0x9E:
            nopimp();
            break;
        case 0x9F:
            nopimp();
            break;
        case 0xA0:
            ldyimm();
            break;
        case 0xA1:
            ldaixx();
            break;
        case 0xA2:
            ldximm();
            break;
        case 0xA3:
            laxixx();
            break;
        case 0xA4:
            ldyzpg();
            break;
        case 0xA5:
            ldazpg();
            break;
        case 0xA6:
            ldxzpg();
            break;
        case 0xA7:
            laxzpg();
            break;
        case 0xA8:
            tayimp();
            break;
        case 0xA9:
            ldaimm();
            break;
        case 0xAA:
            taximp();
            break;
        case 0xAB:
            nopimp();
            break;
        case 0xAC:
            ldyabs();
            break;
        case 0xAD:
            ldaabs();
            break;
        case 0xAE:
            ldxabs();
            break;
        case 0xAF:
            laxabs();
            break;
        case 0xB0:
            bcsrel();
            break;
        case 0xB1:
            ldaixy();
            break;
        case 0xB2:
            nopimp();
            break;
        case 0xB3:
            laxixy();
            break;
        case 0xB4:
            ldyzpx();
            break;
        case 0xB5:
            ldazpx();
            break;
        case 0xB6:
            ldxzpy();
            break;
        case 0xB7:
            laxzpy();
            break;
        case 0xB8:
            clvimp();
            break;
        case 0xB9:
            ldaaby();
            break;
        case 0xBA:
            tsximp();
            break;
        case 0xBB:
            nopimp();
            break;
        case 0xBC:
            ldyabx();
            break;
        case 0xBD:
            ldaabx();
            break;
        case 0xBE:
            ldxaby();
            break;
        case 0xBF:
            laxaby();
            break;
        case 0xC0:
            cpyimm();
            break;
        case 0xC1:
            cmpixx();
            break;
        case 0xC2:
            nopimp();
            break;
        case 0xC3:
            dcpixx();
            break;
        case 0xC4:
            cpyzpg();
            break;
        case 0xC5:
            cmpzpg();
            break;
        case 0xC6:
            deczpg();
            break;
        case 0xC7:
            dcpzpg();
            break;
        case 0xC8:
            inyimp();
            break;
        case 0xC9:
            cmpimm();
            break;
        case 0xCA:
            deximp();
            break;
        case 0xCB:
            nopimp();
            break;
        case 0xCC:
            cpyabs();
            break;
        case 0xCD:
            cmpabs();
            break;
        case 0xCE:
            decabs();
            break;
        case 0xCF:
            dcpabs();
            break;
        case 0xD0:
            bnerel();
            break;
        case 0xD1:
            cmpixy();
            break;
        case 0xD2:
            nopimp();
            break;
        case 0xD3:
            dcpixy();
            break;
        case 0xD4:
            nopzpx();
            break;
        case 0xD5:
            cmpzpx();
            break;
        case 0xD6:
            deczpx();
            break;
        case 0xD7:
            dcpzpx();
            break;
        case 0xD8:
            cldimp();
            break;
        case 0xD9:
            cmpaby();
            break;
        case 0xDA:
            nopimp();
            break;
        case 0xDB:
            dcpaby();
            break;
        case 0xDC:
            nopabx();
            break;
        case 0xDD:
            cmpabx();
            break;
        case 0xDE:
            decabx();
            break;
        case 0xDF:
            dcpabx();
            break;
        case 0xE0:
            cpximm();
            break;
        case 0xE1:
            sbcixx();
            break;
        case 0xE2:
            nopimp();
            break;
        case 0xE3:
            isbixx();
            break;
        case 0xE4:
            cpxzpg();
            break;
        case 0xE5:
            sbczpg();
            break;
        case 0xE6:
            inczpg();
            break;
        case 0xE7:
            isbzpg();
            break;
        case 0xE8:
            inximp();
            break;
        case 0xE9:
            sbcimm();
            break;
        case 0xEA:
            nopimp();
            break;
        case 0xEB:
            sbcimm();
            break;
        case 0xEC:
            cpxabs();
            break;
        case 0xED:
            sbcabs();
            break;
        case 0xEE:
            incabs();
            break;
        case 0xEF:
            isbabs();
            break;
        case 0xF0:
            beqrel();
            break;
        case 0xF1:
            sbcixy();
            break;
        case 0xF2:
            nopimp();
            break;
        case 0xF3:
            isbixy();
            break;
        case 0xF4:
            nopzpx();
            break;
        case 0xF5:
            sbczpx();
            break;
        case 0xF6:
            inczpx();
            break;
        case 0xF7:
            isbzpx();
            break;
        case 0xF8:
            sedimp();
            break;
        case 0xF9:
            sbcaby();
            break;
        case 0xFA:
            nopimp();
            break;
        case 0xFB:
            isbaby();
            break;
        case 0xFC:
            nopabx();
            break;
        case 0xFD:
            sbcabx();
            break;
        case 0xFE:
            incabx();
            break;
        case 0xFF:
            isbabx();
            break;
        default:
            std::cerr << "Unhandled opcode $" << std::hex << (int)opcode
                      << "\n";
            abort();
        }

        uint_fast32_t ncycles = state_.cycles - starting_cycles;
        if (ncycles >= maxcycles)
            return ncycles;
    }
}

void m6502::adcabs() {
    uint8_t val = readu8abs();
    uint16_t result =
        state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) &&
                 ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::adcabx() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    uint16_t result =
        state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) &&
                 ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::adcaby() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8aby();
    uint16_t result =
        state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) &&
                 ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::adcimm() {
    uint8_t val = readu8imm();
    uint16_t result =
        state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) &&
                 ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 2;
}

void m6502::adcixx() {
    uint8_t val = readu8ixx();
    uint16_t result =
        state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) &&
                 ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::adcixy() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    uint16_t result =
        state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) &&
                 ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
}

void m6502::adczpg() {
    uint8_t val = readu8zpg();
    uint16_t result =
        state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) &&
                 ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::adczpx() {
    uint8_t val = readu8zpx();
    uint16_t result =
        state_.regs.A + val + (state_.regs.P & carry_flag ? 1 : 0);
    set_carry(result > 0xFF);
    set_overflow(!((state_.regs.A ^ val) & 0x80) &&
                 ((state_.regs.A ^ result) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::andabs() {
    uint8_t val = readu8abs();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::andabx() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::andaby() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8aby();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::andimm() {
    uint8_t val = readu8imm();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
}

void m6502::andixx() {
    uint8_t val = readu8ixx();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::andixy() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
}

void m6502::andzpg() {
    uint8_t val = readu8zpg();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::andzpx() {
    uint8_t val = readu8zpx();
    state_.regs.A &= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::aslabs() {
    uint8_t val = readu8abs();
    set_carry(val & 0x80);
    val <<= 1;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8abs(val);
    state_.regs.PC += 2;
    state_.cycles += 6;
}

void m6502::aslabx() {
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
}

void m6502::aslacc() {
    set_carry(state_.regs.A & 0x80);
    state_.regs.A <<= 1;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.cycles += 2;
}

void m6502::aslzpg() {
    uint8_t val = readu8zpg();
    set_carry(val & 0x80);
    val <<= 1;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8zpg(val);
    state_.regs.PC += 1;
    state_.cycles += 5;
}

void m6502::aslzpx() {
    uint8_t val = readu8zpx();
    set_carry(val & 0x80);
    val <<= 1;
    set_sign(val & 0x80);
    set_zero(val == 0);
    writeu8zpx(val);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::bccrel() {
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (!(state_.regs.P & carry_flag)) {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
}

void m6502::bcsrel() {
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (state_.regs.P & carry_flag) {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
}

void m6502::beqrel() {
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (state_.regs.P & zero_flag) {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
}

void m6502::bitabs() {
    uint8_t val = readu8abs();
    set_sign(val & 0x80);
    set_overflow(val & 0x40);
    set_zero((val & state_.regs.A) == 0);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::bitzpg() {
    uint8_t val = readu8zpg();
    set_sign(val & 0x80);
    set_overflow(val & 0x40);
    set_zero((val & state_.regs.A) == 0);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::bmirel() {
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (state_.regs.P & sign_flag) {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
}

void m6502::bnerel() {
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (!(state_.regs.P & zero_flag)) {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
}

void m6502::bplrel() {
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (!(state_.regs.P & sign_flag)) {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
}

void m6502::brkimp() {
    pushu16(state_.regs.PC);
    pushu8(state_.regs.S);
    state_.regs.P |= bit4_flag;
    state_.regs.P |= disable_interrupts_flag;
    state_.regs.PC = cb_->readu16(0xFFFE);
    state_.cycles += 7;
}

void m6502::bvcrel() {
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (!(state_.regs.P & overflow_flag)) {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
}

void m6502::bvsrel() {
    int8_t param = reads8imm();
    state_.regs.PC += 1;
    state_.cycles += 2;
    if (state_.regs.P & overflow_flag) {
        uint16_t oldPC = state_.regs.PC;
        state_.regs.PC += param;
        bool page_crossed = ((state_.regs.PC & 0xFF00) != (oldPC & 0xFF00));
        state_.cycles += (page_crossed ? 2 : 1);
    }
}

void m6502::clcimp() {
    state_.regs.P &= ~carry_flag;
    state_.cycles += 2;
}

void m6502::cldimp() {
    state_.regs.P &= ~decimal_flag;
    state_.cycles += 2;
}

void m6502::cliimp() {
    state_.regs.P &= ~disable_interrupts_flag;
    state_.cycles += 2;
}

void m6502::clvimp() {
    state_.regs.P &= ~overflow_flag;
    state_.cycles += 2;
}

void m6502::cmpabs() {
    uint8_t u8 = readu8abs();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::cmpabx() {
    uint8_t u8;
    bool page_crossed;
    std::tie(u8, page_crossed) = readu8abx();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::cmpaby() {
    uint8_t u8;
    bool page_crossed;
    std::tie(u8, page_crossed) = readu8aby();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::cmpimm() {
    uint8_t u8 = readu8imm();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
}

void m6502::cmpixx() {
    uint8_t u8 = readu8ixx();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::cmpixy() {
    uint8_t u8;
    bool page_crossed;
    std::tie(u8, page_crossed) = readu8ixy();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
}

void m6502::cmpzpg() {
    uint8_t u8 = readu8zpg();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::cmpzpx() {
    uint8_t u8 = readu8zpx();
    uint16_t val = state_.regs.A - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::cpxabs() {
    uint8_t u8 = readu8abs();
    uint16_t val = state_.regs.X - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::cpximm() {
    uint8_t u8 = readu8imm();
    uint16_t val = state_.regs.X - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
}

void m6502::cpxzpg() {
    uint8_t u8 = readu8zpg();
    uint16_t val = state_.regs.X - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::cpyabs() {
    uint8_t u8 = readu8abs();
    uint16_t val = state_.regs.Y - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::cpyimm() {
    uint8_t u8 = readu8imm();
    uint16_t val = state_.regs.Y - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
}

void m6502::cpyzpg() {
    uint8_t u8 = readu8zpg();
    uint16_t val = state_.regs.Y - u8;
    set_carry(val < 0x100);
    set_zero(val == 0);
    set_sign(val & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::dcpabs() {
    uint8_t val = readu8abs() - 1;
    writeu8abs(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 2;
    state_.cycles += 6;
}

void m6502::dcpabx() {
    uint8_t val = readu8abx().first - 1;
    writeu8abx(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
}

void m6502::dcpaby() {
    uint8_t val = readu8aby().first - 1;
    writeu8aby(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
}

void m6502::dcpixx() {
    uint8_t val = readu8ixx() - 1;
    writeu8ixx(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
}

void m6502::dcpixy() {
    uint8_t val = readu8ixy().first - 1;
    writeu8ixy(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
}

void m6502::dcpzpg() {
    uint8_t val = readu8zpg() - 1;
    writeu8zpg(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 1;
    state_.cycles += 5;
}

void m6502::dcpzpx() {
    uint8_t val = readu8zpx() - 1;
    writeu8zpx(val);
    uint16_t temp = state_.regs.A - val;
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::decabs() {
    uint8_t val = readu8abs() - 1;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8abs(val);
    state_.regs.PC += 2;
    state_.cycles += 6;
}

void m6502::decabx() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    --val;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8abx(val);
    state_.regs.PC += 2;
    state_.cycles += 7;
}

void m6502::deczpg() {
    uint8_t val = readu8zpg() - 1;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8zpg(val);
    state_.regs.PC += 1;
    state_.cycles += 5;
}

void m6502::deczpx() {
    uint8_t val = readu8zpx() - 1;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8zpx(val);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::deximp() {
    --state_.regs.X;
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.cycles += 2;
}

void m6502::deyimp() {
    --state_.regs.Y;
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.cycles += 2;
}

void m6502::eorabs() {
    uint8_t val = readu8abs();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::eorabx() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::eoraby() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8aby();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::eorimm() {
    uint8_t val = readu8imm();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
}

void m6502::eorixx() {
    uint8_t val = readu8ixx();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::eorixy() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
}

void m6502::eorzpg() {
    uint8_t val = readu8zpg();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::eorzpx() {
    uint8_t val = readu8zpx();
    state_.regs.A ^= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::incabs() {
    uint8_t val = readu8abs();
    ++val;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8abs(val);
    state_.regs.PC += 2;
    state_.cycles += 6;
}

void m6502::incabx() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    ++val;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8abx(val);
    state_.regs.PC += 2;
    state_.cycles += 7;
}

void m6502::inczpg() {
    uint8_t val = readu8zpg();
    ++val;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8zpg(val);
    state_.regs.PC += 1;
    state_.cycles += 5;
}

void m6502::inczpx() {
    uint8_t val = readu8zpx();
    ++val;
    set_zero(val == 0);
    set_sign(val & 0x80);
    writeu8zpx(val);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::inximp() {
    ++state_.regs.X;
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.cycles += 2;
}

void m6502::inyimp() {
    ++state_.regs.Y;
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.cycles += 2;
}

void m6502::isbabs() {
    uint8_t val = readu8abs() + 1;
    writeu8abs(val);
    uint16_t temp =
        state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 2;
    state_.cycles += 6;
}

void m6502::isbabx() {
    uint8_t val = readu8abx().first + 1;
    writeu8abx(val);
    uint16_t temp =
        state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 2;
    state_.cycles += 7;
}

void m6502::isbaby() {
    uint8_t val = readu8aby().first + 1;
    writeu8aby(val);
    uint16_t temp =
        state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 2;
    state_.cycles += 7;
}

void m6502::isbixx() {
    uint8_t val = readu8ixx() + 1;
    writeu8ixx(val);
    uint16_t temp =
        state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 1;
    state_.cycles += 8;
}

void m6502::isbixy() {
    uint8_t val = readu8ixy().first + 1;
    writeu8ixy(val);
    uint16_t temp =
        state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 1;
    state_.cycles += 8;
}

void m6502::isbzpg() {
    uint8_t val = readu8zpg() + 1;
    writeu8zpg(val);
    uint16_t temp =
        state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 1;
    state_.cycles += 5;
}

void m6502::isbzpx() {
    uint8_t val = readu8zpx() + 1;
    writeu8zpx(val);
    uint16_t temp =
        state_.regs.A - val - ((state_.regs.P & carry_flag) ? 0 : 1);
    set_carry(temp < 0x100);
    set_sign(temp & 0x80);
    set_zero((temp & 0xFF) == 0);
    set_overflow(false);
    state_.regs.A = temp;
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::jmpabs() {
    state_.regs.PC = readu16imm();
    state_.cycles += 3;
}

void m6502::jmpind() {
    state_.regs.PC = readu16pgwrap(readu16imm());
    state_.cycles += 5;
}

void m6502::jsrabs() {
    uint16_t val = readu16imm();
    pushu16(state_.regs.PC + 1);
    state_.regs.PC = val;
    state_.cycles += 6;
}

void m6502::laxabs() {
    uint8_t val = readu8abs();
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::laxaby() {
    uint8_t val = readu8aby().first;
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::laxixx() {
    uint8_t val = readu8ixx();
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    ++state_.regs.PC;
    state_.cycles += 6;
}

void m6502::laxixy() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    ++state_.regs.PC;
    state_.cycles += (page_crossed ? 6 : 5);
}

void m6502::laxzpg() {
    uint8_t val = readu8zpg();
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    ++state_.regs.PC;
    state_.cycles += 3;
}

void m6502::laxzpy() {
    uint8_t val = readu8zpy();
    state_.regs.X = state_.regs.A = val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    ++state_.regs.PC;
    state_.cycles += 4;
}

void m6502::ldaabs() {
    state_.regs.A = readu8abs();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::ldaabx() {
    bool page_crossed;
    std::tie(state_.regs.A, page_crossed) = readu8abx();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::ldaaby() {
    bool page_crossed;
    std::tie(state_.regs.A, page_crossed) = readu8aby();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::ldaimm() {
    state_.regs.A = readu8imm();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
}

void m6502::ldaixx() {
    state_.regs.A = readu8ixx();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::ldaixy() {
    bool page_crossed;
    std::tie(state_.regs.A, page_crossed) = readu8ixy();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
}

void m6502::ldazpg() {
    state_.regs.A = readu8zpg();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::ldazpx() {
    state_.regs.A = readu8zpx();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::ldxabs() {
    state_.regs.X = readu8abs();
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::ldxaby() {
    bool page_crossed;
    std::tie(state_.regs.X, page_crossed) = readu8aby();
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::ldximm() {
    state_.regs.X = readu8imm();
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
}

void m6502::ldxzpg() {
    state_.regs.X = readu8zpg();
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::ldxzpy() {
    state_.regs.X = readu8zpy();
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::ldyabs() {
    state_.regs.Y = readu8abs();
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::ldyabx() {
    bool page_crossed;
    std::tie(state_.regs.Y, page_crossed) = readu8abx();
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::ldyimm() {
    state_.regs.Y = readu8imm();
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
}

void m6502::ldyzpg() {
    state_.regs.Y = readu8zpg();
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::ldyzpx() {
    state_.regs.Y = readu8zpx();
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::lsrabs() {
    uint8_t val = readu8abs();
    set_carry(val & 0x01);
    val >>= 1;
    set_zero(val == 0);
    state_.regs.P &= ~sign_flag;
    writeu8abs(val);
    state_.regs.PC += 2;
    state_.cycles += 6;
}

void m6502::lsrabx() {
    uint8_t val = readu8abx().first;
    set_carry(val & 0x01);
    val >>= 1;
    set_zero(val == 0);
    state_.regs.P &= ~sign_flag;
    writeu8abx(val);
    state_.regs.PC += 2;
    state_.cycles += 7;
}

void m6502::lsracc() {
    set_carry(state_.regs.A & 0x01);
    state_.regs.A >>= 1;
    set_zero(state_.regs.A == 0);
    state_.regs.P &= ~sign_flag;
    state_.cycles += 2;
}

void m6502::lsrzpg() {
    uint8_t val = readu8zpg();
    set_carry(val & 0x01);
    val >>= 1;
    set_zero(val == 0);
    state_.regs.P &= ~sign_flag;
    writeu8zpg(val);
    state_.regs.PC += 1;
    state_.cycles += 5;
}

void m6502::lsrzpx() {
    uint8_t val = readu8zpx();
    set_carry(val & 0x01);
    val >>= 1;
    set_zero(val == 0);
    state_.regs.P &= ~sign_flag;
    writeu8zpx(val);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::nopabs() {
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::nopabx() {
    bool page_crossed = readu8abx().second;
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::nopimm() {
    ++state_.regs.PC;
    state_.cycles += 2;
}

void m6502::nopimp() { state_.cycles += 2; }

void m6502::nopzpg() {
    ++state_.regs.PC;
    state_.cycles += 3;
}

void m6502::nopzpx() {
    ++state_.regs.PC;
    state_.cycles += 4;
}

void m6502::oraabs() {
    state_.regs.A |= readu8abs();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::oraabx() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    state_.regs.A |= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::oraaby() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8aby();
    state_.regs.A |= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::oraimm() {
    state_.regs.A |= readu8imm();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 2;
}

void m6502::oraixx() {
    state_.regs.A |= readu8ixx();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::oraixy() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    state_.regs.A |= val;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
}

void m6502::orazpg() {
    state_.regs.A |= readu8zpg();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::orazpx() {
    state_.regs.A |= readu8zpx();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::phaimp() {
    pushu8(state_.regs.A);
    state_.cycles += 3;
}

void m6502::phpimp() {
    pushu8(state_.regs.P | bit4_flag);
    state_.cycles += 3;
}

void m6502::plaimp() {
    state_.regs.A = popu8();
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.cycles += 4;
}

void m6502::plpimp() {
    uint8_t val = popu8();
    state_.regs.P = (val | 0x20) & 0xEF;
    state_.cycles += 4;
}

void m6502::rlaabs() {
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
}

void m6502::rlaabx() {
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
}

void m6502::rlaaby() {
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
}

void m6502::rlaixx() {
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
}

void m6502::rlaixy() {
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
}

void m6502::rlazpg() {
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
}

void m6502::rlazpx() {
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
}

void m6502::rolabs() {
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
}

void m6502::rolabx() {
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
}

void m6502::rolacc() {
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(state_.regs.A & 0x80);
    state_.regs.A <<= 1;
    if (was_carry)
        state_.regs.A |= 0x01;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.cycles += 2;
}

void m6502::rolzpg() {
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
}

void m6502::rolzpx() {
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
}

void m6502::rorabs() {
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
}

void m6502::rorabx() {
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
}

void m6502::roracc() {
    bool was_carry = (state_.regs.P & carry_flag);
    set_carry(state_.regs.A & 0x01);
    state_.regs.A >>= 1;
    if (was_carry)
        state_.regs.A |= 0x80;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.cycles += 2;
}

void m6502::rorzpg() {
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
}

void m6502::rorzpx() {
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
}

void m6502::rraabs() {
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
}

void m6502::rraabx() {
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
}

void m6502::rraaby() {
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
}

void m6502::rraixx() {
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
}

void m6502::rraixy() {
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
}

void m6502::rrazpg() {
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
}

void m6502::rrazpx() {
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
}

void m6502::rtiimp() {
    state_.regs.P = popu8() | bit5_flag;
    state_.regs.PC = popu16();
    state_.cycles += 6;
}

void m6502::rtsimp() {
    state_.regs.PC = popu16() + 1;
    state_.cycles += 6;
}

void m6502::saxabs() {
    writeu8abs(state_.regs.A & state_.regs.X);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::saxixx() {
    writeu8ixx(state_.regs.A & state_.regs.X);
    ++state_.regs.PC;
    state_.cycles += 6;
}

void m6502::saxzpg() {
    writeu8zpg(state_.regs.A & state_.regs.X);
    ++state_.regs.PC;
    state_.cycles += 3;
}

void m6502::saxzpy() {
    writeu8zpy(state_.regs.A & state_.regs.X);
    ++state_.regs.PC;
    state_.cycles += 4;
}

void m6502::sbcabs() {
    uint8_t val = readu8abs();
    uint16_t result =
        state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) &&
                 ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::sbcabx() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8abx();
    uint16_t result =
        state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) &&
                 ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::sbcaby() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8aby();
    uint16_t result =
        state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) &&
                 ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 2;
    state_.cycles += (page_crossed ? 5 : 4);
}

void m6502::sbcimm() {
    uint8_t val = readu8imm();
    uint16_t result =
        state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) &&
                 ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 2;
}

void m6502::sbcixx() {
    uint8_t val = readu8ixx();
    uint16_t result =
        state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) &&
                 ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::sbcixy() {
    uint8_t val;
    bool page_crossed;
    std::tie(val, page_crossed) = readu8ixy();
    uint16_t result =
        state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) &&
                 ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += (page_crossed ? 6 : 5);
}

void m6502::sbczpg() {
    uint8_t val = readu8zpg();
    uint16_t result =
        state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) &&
                 ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::sbczpx() {
    uint8_t val = readu8zpx();
    uint16_t result =
        state_.regs.A - val - (state_.regs.P & carry_flag ? 0 : 1);
    set_carry(result < 0x100);
    set_overflow(((state_.regs.A ^ result) ^ 0x80) &&
                 ((state_.regs.A ^ val) & 0x80));
    set_zero((result & 0xFF) == 0);
    set_sign(result & 0x80);
    state_.regs.A = (uint8_t)result;
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::secimp() {
    state_.regs.P |= carry_flag;
    state_.cycles += 2;
}

void m6502::sedimp() {
    state_.regs.P |= decimal_flag;
    state_.cycles += 2;
}

void m6502::seiimp() {
    state_.regs.P |= disable_interrupts_flag;
    state_.cycles += 2;
}

void m6502::sloabs() {
    uint8_t prevVal = readu8abs();
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8abs(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 6;
}

void m6502::sloabx() {
    uint8_t prevVal = readu8abx().first;
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8abx(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
}

void m6502::sloaby() {
    uint8_t prevVal = readu8aby().first;
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8aby(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
}

void m6502::sloixx() {
    uint8_t prevVal = readu8ixx();
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8ixx(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
}

void m6502::sloixy() {
    uint8_t prevVal = readu8ixy().first;
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8ixy(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
}

void m6502::slozpg() {
    uint8_t prevVal = readu8zpg();
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8zpg(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 5;
}

void m6502::slozpx() {
    uint8_t prevVal = readu8zpx();
    set_carry(prevVal & 0x80);
    uint8_t val = (prevVal << 1);
    writeu8zpx(val);
    state_.regs.A |= val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::sreabs() {
    uint8_t prev_val = readu8abs();
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8abs(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 6;
}

void m6502::sreabx() {
    uint8_t prev_val = readu8abx().first;
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8abx(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
}

void m6502::sreaby() {
    uint8_t prev_val = readu8aby().first;
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8aby(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 2;
    state_.cycles += 7;
}

void m6502::sreixx() {
    uint8_t prev_val = readu8ixx();
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8ixx(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
}

void m6502::sreixy() {
    uint8_t prev_val = readu8ixy().first;
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8ixy(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 8;
}

void m6502::srezpg() {
    uint8_t prev_val = readu8zpg();
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8zpg(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 5;
}

void m6502::srezpx() {
    uint8_t prev_val = readu8zpx();
    set_carry(prev_val & 0x01);
    uint8_t new_val = prev_val >> 1;
    writeu8zpx(new_val);
    state_.regs.A ^= new_val;
    set_sign(state_.regs.A & 0x80);
    set_zero(state_.regs.A == 0);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::staabs() {
    writeu8abs(state_.regs.A);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::staabx() {
    writeu8abx(state_.regs.A);
    state_.regs.PC += 2;
    state_.cycles += 5;
}

void m6502::staaby() {
    writeu8aby(state_.regs.A);
    state_.regs.PC += 2;
    state_.cycles += 5;
}

void m6502::staixx() {
    writeu8ixx(state_.regs.A);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::staixy() {
    writeu8ixy(state_.regs.A);
    state_.regs.PC += 1;
    state_.cycles += 6;
}

void m6502::stazpg() {
    writeu8zpg(state_.regs.A);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::stazpx() {
    writeu8zpx(state_.regs.A);
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::stxabs() {
    writeu8abs(state_.regs.X);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::stxzpg() {
    writeu8zpg(state_.regs.X);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::stxzpy() {
    writeu8zpy(state_.regs.X);
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::styabs() {
    writeu8abs(state_.regs.Y);
    state_.regs.PC += 2;
    state_.cycles += 4;
}

void m6502::styzpg() {
    writeu8zpg(state_.regs.Y);
    state_.regs.PC += 1;
    state_.cycles += 3;
}

void m6502::styzpx() {
    writeu8zpx(state_.regs.Y);
    state_.regs.PC += 1;
    state_.cycles += 4;
}

void m6502::taximp() {
    state_.regs.X = state_.regs.A;
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.cycles += 2;
}

void m6502::tayimp() {
    state_.regs.Y = state_.regs.A;
    set_zero(state_.regs.Y == 0);
    set_sign(state_.regs.Y & 0x80);
    state_.cycles += 2;
}

void m6502::tsximp() {
    state_.regs.X = state_.regs.S;
    set_zero(state_.regs.X == 0);
    set_sign(state_.regs.X & 0x80);
    state_.cycles += 2;
}

void m6502::txaimp() {
    state_.regs.A = state_.regs.X;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.cycles += 2;
}

void m6502::txsimp() {
    state_.regs.S = state_.regs.X;
    state_.cycles += 2;
}

void m6502::tyaimp() {
    state_.regs.A = state_.regs.Y;
    set_zero(state_.regs.A == 0);
    set_sign(state_.regs.A & 0x80);
    state_.cycles += 2;
}

// Flag operations
void m6502::set_carry(bool c) {
    if (c) {
        state_.regs.P |= carry_flag;
    } else {
        state_.regs.P &= ~carry_flag;
    }
}

void m6502::set_overflow(bool c) {
    if (c) {
        state_.regs.P |= overflow_flag;
    } else {
        state_.regs.P &= ~overflow_flag;
    }
}

void m6502::set_zero(bool c) {
    if (c) {
        state_.regs.P |= zero_flag;
    } else {
        state_.regs.P &= ~zero_flag;
    }
}

void m6502::set_sign(bool c) {
    if (c) {
        state_.regs.P |= sign_flag;
    } else {
        state_.regs.P &= ~sign_flag;
    }
}

// Memory operations
int8_t m6502::reads8imm() { return (int8_t)readu8imm(); }

uint8_t m6502::readu8abs() { return cb_->readu8(readu16imm()); }

std::pair<uint8_t, bool> m6502::readu8abx() {
    uint16_t addr = readu16imm();
    uint16_t addr2 = addr + state_.regs.X;
    bool page_crossed = (addr & 0xFF00) != (addr2 & 0xFF00);
    return std::make_pair(cb_->readu8(addr2), page_crossed);
}

void m6502::nmi(uint16_t addr) {
    pushu16(state_.regs.PC);
    pushu8(state_.regs.S);
    state_.regs.PC = cb_->readu16(addr);
}

} // namespace cpu
} // namespace deeznes

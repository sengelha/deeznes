#pragma once

namespace deeznes {
namespace cpu {
    
enum class m6502_addrmode
{
    ABS,
    ABX,
    ABY,
    ACC,
    IMM,
    IMP,
    IND,
    IXX,
    IXY,
    REL,
    ZPG,
    ZPX,
    ZPY,
};

}
}
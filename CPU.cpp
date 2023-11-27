#include "CPU.h"
#include <iostream>
using namespace std;

void CPU::fetch(int memory[]) {
    opcode = (memory[pc] >> 4) & 0xF;
    regIndex = memory[pc++] & 0xF;
    address = memory[pc++];
}

void CPU::execute(int memory[]) {
    switch (opcode)         //(RXY)
    {
        case 0x1: // LOAD the register R with the bit pattern found in the memory cell whose address is XY
            registers[regIndex] = memory[address];
            break;
        case 0x2: // LOAD the register R with the bit pattern XY.
            registers[regIndex] = address;
            break;
        case 0x3: // STORE the bit pattern found in register R in the memory cell whose address is XY.
            memory[address]=registers[regIndex];
            break;
        case 0x4: // (0RS) MOVE the bit pattern found in register R to register S.
            registers[address & 0xF] = registers[(address >> 4) & 0xF];
            break;
        case 0x5: // ADD the bit patterns in registers S and T as though they were two’s complement representations
        {
            int sIndex = (address >> 4) & 0xF;
            int tIndex = address & 0xF;
            addRegistersTwoComplement(regIndex, sIndex, tIndex);
            break;
        }


        case 0xB: // JUMP
            if (registers[regIndex] == registers[0])
            {
                pc = address;
            }
            break;
        case 0xC: // HALT
        {
            cout << "Program halted." << endl;
            return;
        }
        default:
            cout << "Invalid opcode: " << opcode << endl;
            return;
    }
}

void CPU::addRegistersTwoComplement(int rIndex, int sIndex, int tIndex) {
    int sValue = registers[sIndex];
    int tValue = registers[tIndex];
    int sum = sValue + tValue;
    sum&=((1 << 8) - 1);
    registers[rIndex] = sum;
}

bool CPU::halted() {
    return opcode==0xC;
}

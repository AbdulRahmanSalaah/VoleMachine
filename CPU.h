
class CPU {
public:
    int registers[16];
    int opcode,regIndex,address,pc;
    void fetch(int memory[]);
    void execute(int memory[]);
    void addRegistersTwoComplement(int rIndex, int sIndex, int tIndex);
    bool halted();
};



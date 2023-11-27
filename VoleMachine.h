#include "CPU.h"
using namespace std;
#include <bits/stdc++.h>
class VoleMachine {
private:
    int memory[256];
    CPU MachineCpu;
public:
    void set();
    void LoadInstruction();
    void displayStatus();
    void Start();
};

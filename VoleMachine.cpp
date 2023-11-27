#include "VoleMachine.h"
#include <iostream>
using namespace std;

void VoleMachine::LoadInstruction() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    fstream file (filename);
    cout<<"Start Address: ";
    cin>>hex>>MachineCpu.pc;

    if(file.is_open()){
        int first,bit1,sec,bit2,cnt=MachineCpu.pc;
        while (file.good()){
            file >> hex >> first >> sec >> bit2;
            bit1= (first << 4) | sec;
            memory[cnt++]=bit1;
            memory[cnt++]=bit2;
        }
        cout << "Program loaded successfully." << endl;
    }
    else{
        cout << "Error: Unable to open the file." << endl;
    }
}

void VoleMachine::displayStatus() {
    cout << "Registers:" << endl;
    for (int i = 0; i < 16; ++i)
    {
        cout << "Register " << dec << i << ": " << hex << MachineCpu.registers[i] << endl;
    }

    cout << "Memory:" << endl;
    for (int i = 0; i < 256; ++i)
    {
        cout << hex << i << ": " << memory[i] << endl;
    }

    cout << "Program Counter: " << hex << MachineCpu.pc << dec << endl;
    cout << "Instruction Register: " << hex << MachineCpu.opcode << MachineCpu.regIndex << MachineCpu.address << endl;
    cout << "----------------------" << endl;
}

void VoleMachine::Start() {
    char choice;
    do
    {
        cout << "Menu:" << endl;
        cout << "1. Load Program from File" << endl;
        cout << "2. Step Execution" << endl;
        cout << "3. Run Until halt" << endl;
        cout << "4. Display Status" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case '1':
            {
                set();
                LoadInstruction();
                break;
            }
            case '2':
            {
                MachineCpu.fetch(memory);
                MachineCpu.execute(memory);
                break;
            }
            case '3':
            {
                while(!MachineCpu.halted()){
                    MachineCpu.fetch(memory);
                    MachineCpu.execute(memory);
                }
                break;
            }
            case '4':
                displayStatus();
                break;
            case '5':
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != '5');
}

void VoleMachine::set() {
    for (int i = 0; i < 256; ++i) {
        memory[i]=0;
    }
    for (int i = 0; i < 16; ++i) {
        MachineCpu.registers[i]=0;
    }
}

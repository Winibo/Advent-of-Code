#include "bits/stdc++.h"

using namespace std;

enum command {
    Halt,
    Input,
    Output,
    Error
};

class Computer {
    public:
        Computer(string input) {
            memory.resize(100000, 0);
            stringstream inputStream(input);
            long long value;
            char temp;
            long long index = 0;
            while (!inputStream.eof()) {
                inputStream >> value >> temp;
                memory[index++] = value;
            }
        }

        Computer(vector<long long> newMemory) {
            memory = newMemory;
            memory.resize(100000, 0);
        }

        command calculate() {
            while (true) {
                long long instruction = memory[intPtr] % 100, mode = memory[intPtr] / 100;
                long long inA = memory[intPtr + 1], inB = memory[intPtr + 2], inC = memory[intPtr + 3];
                switch (instruction) {
                    case 1:
                        memory[inC] = getValue(inA, mode % 10) + getValue(inB, (mode / 10) % 10);
                        intPtr += 4;
                        break;
                    case 2:
                        memory[inC] = getValue(inA, mode % 10) * getValue(inB, (mode / 10) % 10);
                        intPtr += 4;
                        break;
                    case 3:
                        if (!inputSet)
                            return command::Input;
                        inputSet = false;
                        //Set Input
                        memory[inA] = in;
                        intPtr += 2;
                        break;
                    case 4:
                        //Set Output
                        out = getValue(inA, mode % 10);
                        intPtr += 2;
                        return command::Output;
                    case 5:
                        if (getValue(inA, mode % 10) != 0) {
                            intPtr = getValue(inB, (mode / 10) % 10);
                        } else {
                            intPtr += 3;
                        }
                        break;
                    case 6:
                        if (getValue(inA, mode % 10) == 0) {
                            intPtr = getValue(inB, (mode / 10) % 10);
                        } else {
                            intPtr += 3;
                        }
                        break;
                    case 7:
                        memory[inC] = getValue(inA, mode % 10) < getValue(inB, (mode / 10) % 10);
                        intPtr += 4;
                        break;
                    case 8:
                        memory[inC] = getValue(inA, mode % 10) == getValue(inB, (mode / 10) % 10);
                        intPtr += 4;
                        break;
                    case 99:
                        return command::Halt;
                    default:
                        return command::Error;
                }
            }
        }

        vector<long long> getMemory() {
            return memory;
        }

        long long getintPtr() {
            return intPtr;
        }

        void input(long long value) {
            in = value;
            inputSet = true;
        }

        long long output() {
            return out;
        }

    private:
        vector<long long> memory;
        unsigned long long intPtr = 0;
        bool inputSet = false;
        long long out = 0, in = 0;

        long long getValue(long long val, int mode) {
            switch (mode) {
                case 0:
                    return memory[val];
                case 1:
                    return val;
            }
            return -424242;
        }
};

int main() {
    string input;
    getline(cin, input);
    Computer comp = Computer(input);
    while (true) {
        command result = comp.calculate();
        if (result == command::Input) {
            comp.input(5);
        } else if (result == command::Output) {
            cout << comp.output() << endl;
        } else if (result == command::Halt) {
            return 0;
        } else if (result == command::Error) {
            cout << "Computer Crashed. Dumping Memory:" << endl;
            vector<long long> mem = comp.getMemory();
            cout << "intPtr:" << comp.getintPtr() << endl;
            for (auto x : mem) {
                cout << x << ',';
            }
            return 0;
        }
    }
    cout << "Something went wrong" << endl;
    return 0;
}
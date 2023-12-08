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

long long runProgram(Computer& c, long long previousInput, int setting) {
    
    c.input(setting);
    c.calculate();
    c.input(previousInput);
    command test = c.calculate();
    return c.output();
}

long long tryCombination(Computer& base, vector<int> combination) {
    long long previous = 0;
    for (int x : combination) {
        Computer newComp(base.getMemory());
        previous = runProgram(newComp, previous, x);
    }
    return previous;
}

vector<vector<int>> getCombinations(vector<int> values) {
    vector<vector<int>> combinations;
    for (int x = 0; x < values.size(); x++) {
        int temp = values[x];
        if (temp == -1)
            continue;
        values[x] = -1;
        vector<vector<int>> combos = getCombinations(values);
        for (auto& y : combos) {
            y.push_back(temp);
            combinations.push_back(y);
        }
        values[x] = temp;
    }
    if (combinations.size() == 0) {
        vector<int> temp;
        combinations.push_back(temp);
        return combinations;
    }
    return combinations;
}

int main() {
    vector<int> baseCombos = {0, 1, 2, 3, 4};
    string input;
    getline(cin, input);
    Computer base(input);
    vector<vector<int>> combinations = getCombinations(baseCombos);
    long long best = 0;
    for (vector<int> combination : combinations) {
        best = max(tryCombination(base, combination), best);
    }
    cout << best << endl;
    return 0;
}
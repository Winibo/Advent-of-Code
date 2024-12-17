#include <bits/stdc++.h>

using namespace std;

struct computer {
  long long instptr = 0;
  vector<long long> registers;
  vector<long long> output;
};

vector<long long> program;

long long getComboOperand(computer c, int operand) {
    switch (operand) {
        case 0:
            return 0;
            break;
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        case 3:
            return 3;
            break;
        case 4:
            return c.registers[0];
            break;
        case 5:
            return c.registers[1];
            break;
        case 6:
            return c.registers[2];
            break;
        case 7:
        default:
            // HCF
            return -999;
            break;
    }
    return 0;
}

void printCPU(computer c) {
    cout << "ptr: " << c.instptr << endl;
    cout << "Memory:" << endl;
    for (int i : c.registers) {
        cout << i << endl;
    }
    cout << "Output" << endl;
}

pair<bool,computer> step_calculate(computer c) {
    if (c.instptr >= program.size()) {
        return make_pair(true, c);
    }
    int opcode = program[c.instptr++];
    int operand = program[c.instptr++];
    long long comboOp = getComboOperand(c, operand);
    long long divisor = 1;
    switch (opcode) {
        case 0:
            for (int i = 0; i < comboOp; i++) {
                divisor *= 2;
            }
            c.registers[0] = c.registers[0] / divisor;
            break;
        case 1:
            c.registers[1] = c.registers[1] ^ operand;
            break;
        case 2:
            c.registers[1] = comboOp % 8;
            break;
        case 3:
            if (c.registers[0] != 0) c.instptr = operand;
            break;
        case 4:
            c.registers[1] = c.registers[1] ^ c.registers[2];
            break;
        case 5:
            c.output.push_back(comboOp % 8);
            break;
        case 6:
            for (int i = 0; i < comboOp; i++) {
                divisor *= 2;
            }
            c.registers[1] = c.registers[0] / divisor;
            break;
        case 7:
            for (int i = 0; i < comboOp; i++) {
                divisor *= 2;
            }
            c.registers[2] = c.registers[0] / divisor;
            break;
    }
    return make_pair(false, c);
}

int main()
{
    computer c;
    for (int i = 0; i < 3; i++) {
        string tempS; int tempI;
        cin >> tempS >> tempS >> tempI;
        c.registers.push_back(tempI);
        if (i == 2) cin >> tempS; //yeah, yeah, this is bad
    }

    while (!cin.eof()) {
        int tempI; char tempC;
        cin >> tempI >> tempC;
        program.push_back(tempI);
    }
    pair<bool, computer> data = make_pair(false, c);
    while (!data.first) {
        data = step_calculate(data.second);
    }
    for (int x : data.second.output) {
        cout << x << ',';
    }
    cout << endl;
    return 0;
}
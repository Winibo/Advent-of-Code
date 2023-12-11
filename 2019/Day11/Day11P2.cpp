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
                long long inA = getValue(intPtr + 1, mode % 10), inB = getValue(intPtr + 2, (mode / 10) % 10), inC = getValue(intPtr + 3, (mode / 100) % 10);
                switch (instruction) {
                    case 1:
                        memory[inC] = memory[inA] + memory[inB];
                        intPtr += 4;
                        break;
                    case 2:
                        memory[inC] = memory[inA] * memory[inB];
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
                        out = memory[inA];
                        intPtr += 2;
                        return command::Output;
                    case 5:
                        if (memory[inA] != 0) {
                            intPtr = memory[inB];
                        } else {
                            intPtr += 3;
                        }
                        break;
                    case 6:
                        if (memory[inA] == 0) {
                            intPtr = memory[inB];
                        } else {
                            intPtr += 3;
                        }
                        break;
                    case 7:
                        memory[inC] = memory[inA] < memory[inB];
                        intPtr += 4;
                        break;
                    case 8:
                        memory[inC] = memory[inA] == memory[inB];
                        intPtr += 4;
                        break;
                    case 9:
                        relativeBase += memory[inA];
                        intPtr += 2;
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
        long long relativeBase = 0;

        bool inputSet = false;
        long long out = 0, in = 0;

        long long getValue(long long val, int mode) {
            switch (mode) {
                case 0:
                    return memory[val];
                case 1:
                    return val;
                case 2:
                    return memory[val] + relativeBase;
            }
            return -424242;
        }
};

map<pair<int, int>, int> coveredPanels;


pair<int, int> updatePosition(pair<int, int> position, int direction) {
    switch (direction) {
        case 0: //Up
            position.second--;
            break;
        case 1: //Right
            position.first++;
            break;
        case 2: //Down
            position.second++;
            break;
        case 3: //Left
            position.first--;
            break;
        default:
            cout << "Direction is invalid" << endl;
            break;
    }
    return position;
}

int main() {
    string program;
    getline(cin, program);
    Computer comp(program);
    command result = command::Error;
    pair<int, int> position = make_pair(0,0);
    coveredPanels[position] = 1;
    int direction = 0;
    while (result != command::Halt) {
        result = comp.calculate();
        int colour;
        int turn;
        switch (result) {
            case command::Input:
                comp.input(coveredPanels[position]);
                break;
            case command::Output:
                //We always get 2 outputs in a row
                colour = comp.output(); comp.calculate();
                coveredPanels[position] = colour;
                turn = comp.output();
                direction = (direction + (turn == 0 ? -1 : 1));
                if (direction < 0) direction += 4;
                if (direction > 3) direction -= 4;
                position = updatePosition(position, direction);
                break;
            case command::Error:
                cout << "An Error Occurred" << endl;
                return 0;
                break;
            case command::Halt:
                break;
        }
    }
    cout << coveredPanels.size() << endl;
    cout << endl;
    //Find Corners
    int leftEdge = INT_MAX, rightEdge = INT_MIN, topEdge = INT_MAX, bottomEdge = INT_MIN;
    for (auto x : coveredPanels) {
        if (x.first.first < leftEdge)
            leftEdge = x.first.first;
        if (x.first.first > rightEdge)
            rightEdge = x.first.first;
        if (x.first.second < topEdge)
            topEdge = x.first.second;
        if (x.first.second > bottomEdge)
            bottomEdge = x.first.second;
    }
    // cout << "Left:" << leftEdge << " Right:" << rightEdge << " Top:" << topEdge << " Bottom:" << bottomEdge << endl;
    for (int row = topEdge - 1; row <= bottomEdge; row++) {
        for (int column = leftEdge -1; column <= rightEdge; column++) {
            if (coveredPanels[make_pair(column, row)] == 0) {
                cout << ' ';
            } else {
                cout << '1';
            }
        }
        cout << endl;
    }
    return 0;   
}
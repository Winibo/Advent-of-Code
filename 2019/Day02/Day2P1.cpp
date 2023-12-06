#include "bits/stdc++.h"

using namespace std;

class Computer {
    public:
        Computer(string input) {
            stringstream inputStream(input);
            int value;
            char temp;
            while (!inputStream.eof()) {
                inputStream >> value >> temp;
                memory.push_back(value);
            }
        }

        void calculate() {
            while (true) {
                if (intPtr % 4 != 0) {
                    throwError("Instruction Pointer Misaligned: ");
                }
                int instruction = memory[intPtr];
                if (instruction == 99) {
                    break;
                }
                int inA = memory[intPtr + 1], inB = memory[intPtr + 2], out = memory[intPtr + 3];
                switch (instruction) {
                    case 1:
                        memory[out] = memory[inA] + memory[inB];
                        break;
                    case 2:
                        memory[out] = memory[inA] * memory[inB];
                        break;
                    default:
                        throwError("Unexpected Opcode at: ");
                        break;
                }
                intPtr += 4;
            }
        }

        vector<int> getMemory() {
            return memory;
        }

    private:
        vector<int> memory;
        unsigned int intPtr = 0;

        void throwError(string message) {
            string errorMessage = message + to_string(intPtr) + " Dumping Memory: \n";
            for (int x : memory) {
                errorMessage += to_string(x) + ",";
            }
            throw runtime_error(errorMessage);
        }
};

int main() {
    string input;
    getline(cin, input);
    Computer comp = Computer(input);
    comp.calculate();
    vector<int> result = comp.getMemory();
    cout << result[0] << endl;
    return 0;
}
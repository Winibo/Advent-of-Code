#include "bits/stdc++.h"

using namespace std;

const int width = 25;
const int height = 6;

vector<string> layers;

int main() {
    while (!cin.eof()) {
        string layer = "";
        for (int i = 0; i < (width*height); i++) {
            char x = '5';
            cin >> x;
            if (x == '5')
                break;
            layer += x;
        }
        if (layer != "")
            layers.push_back(layer);
    }

    string answer(width*height, '2');
    for (string layer : layers) {
        for (int i = 0; i < layer.length(); i++) {
            if (answer[i] == '2') {
                answer[i] = layer[i];
            }
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (answer[width*i + j] == '1') {
                cout << answer[width*i + j];
            } else {
                cout << ' ';
            }   
        }
        cout << endl;
    }
    return 0;
}
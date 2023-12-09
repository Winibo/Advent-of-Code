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

    int layerIndex = 0, bestCount = INT_MAX;
    for (int idx = 0; idx < layers.size(); idx++) {
        string layer = layers[idx];
        int amount = count(layer.begin(), layer.end(), '0');
        if (amount < bestCount) {
            bestCount = amount;
            layerIndex = idx;
        }
    }
    string layer = layers[layerIndex];
    cout << count(layer.begin(), layer.end(), '1') << endl;
    cout << count(layer.begin(), layer.end(), '2') << endl;
    cout << count(layer.begin(), layer.end(), '1') * count(layer.begin(), layer.end(), '2') << endl;
    return 0;
}
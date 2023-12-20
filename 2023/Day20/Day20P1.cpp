#include "bits/stdc++.h"

using namespace std;

struct module {
    int type = 0; //Broadcaster, Flip Flop, Conjunction
    string name;
    vector<string> children;
    bool state = false;
    map<string, bool> sentStates;
};

map<string, module> network;

void parseModule(string m) {
    module next;
    stringstream ms(m);
    char temp;
    if (m[0] == '%') { //Flip Flop
        next.type = 1;
        ms >> temp;
    } else if (m[0] == '&') { //Inverter
        next.type = 2;
        ms >> temp;
    }
    ms >> next.name;
    ms >> temp >> temp;
    while (!ms.eof()) {
        string child;
        ms >> child;
        if (child[child.length() - 1] == ',') {
            child = child.substr(0, child.length() - 1);
        }
        next.children.push_back(child);
    }
    network[next.name] = next;
}

pair<int, int> pressButton() {
    int lowPulses = 1, highPulses = 0;
    queue<pair<module, pair<string, bool>>> pulseQueue;
    pulseQueue.push(make_pair(network["broadcaster"], make_pair("broadcaster", false)));
    while (!pulseQueue.empty()) {
        module current = pulseQueue.front().first;
        bool previousPulse = pulseQueue.front().second.second;
        string sender = pulseQueue.front().second.first; pulseQueue.pop();
        if (previousPulse == true && current.type == 1)
            continue; //Flip flops ignore high pulses
        bool sentPulse;
        switch (current.type) {
            case 0:
                sentPulse = false;
                break;
            case 1:
                network[current.name].state = sentPulse = !current.state;
                break;
            case 2:
            sentPulse = false;
            network[current.name].sentStates[sender] = previousPulse; //Update Conjunction stuff
            current.sentStates[sender] = previousPulse;
            for (auto x : current.sentStates) {
                if (x.second == false) {
                    sentPulse = true;
                    break;
                }
            }
                break;
        }
        for (string reciever : current.children) {
            if (sentPulse == false) {
                lowPulses++;
            } else {
                highPulses++;
            }
            pulseQueue.push(make_pair(network[reciever], make_pair(current.name, sentPulse))); //Add to queue          
        }
    }
    return make_pair(lowPulses,highPulses);
}

void setupNetwork() {
    for (auto x : network) {
        for (string y : x.second.children) {
            if (network[y].type == 2) {
                network[y].sentStates[x.second.name] = false;
            }
        }
    }
}

int main() {
    while (!cin.eof()) {
        string next = "";
        getline(cin, next);
        if (next == "")
            break;
        parseModule(next);
    }
    setupNetwork();
    pair<int, int> pulses;
    for (int i = 0; i < 1000; i++) {
        pair<int, int> temp = pressButton();
        pulses.first += temp.first;
        pulses.second += temp.second;
    }
    cout << pulses.first << endl;
    cout << pulses.second << endl;
    cout << pulses.first * pulses.second << endl;
    return 0;
}
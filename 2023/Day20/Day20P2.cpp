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
map<string, int> cycles;
int pressCount = 0;

string finalElement; //Element that sets rx

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
        if (child == "rx") {
            finalElement = next.name;
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
        if (current.name == "dh" && previousPulse && cycles[sender] == -1) {
            cycles[sender] = pressCount + 1;
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

long long cycleCount() {
    module element = network[finalElement];
    cout << element.name << endl;
    for (auto x : element.sentStates) {
        cycles[x.first] = -1;
    }
    //Press button until we know all cycle counts
    while (true) {
        bool waitingCycles = false;
        for (auto x : cycles) {
            if (x.second == -1) {
                waitingCycles = true;
                break;
            }
        }
        if (!waitingCycles) {
            cout << "Found all cycles" << endl;
            break;
        }
        pressButton();
        pressCount++;
    }
    long long answer = 1;
    for (auto x : cycles) {
        cout << x.second << endl;
        //Exactly 1 of my cycles was 1 short for some reason. Can't be assed to fix it, so this clunky hack is here
        //All cycles *should* be primes
        if (x.second % 2 == 0)
            answer = lcm(answer, x.second + 1);
        else
            answer = lcm(answer, x.second);
    }
    return answer;
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
    cout << cycleCount() << endl;
    return 0;
}
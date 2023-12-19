#include "bits/stdc++.h"

using namespace std;

struct rule {
    bool rule = true;
    char condition;
    char xmasValue;
    int compValue;
    string destination;
};

struct part {
    int x;
    int m;
    int a;
    int s;
};
//This is a DAG
map<string,vector<rule>> workflows; //Each workflow is a vector of rules

bool evaluate(part toEval) { //True means accepted, false means rejected
    vector<rule> currentFlow;
    currentFlow = workflows["in"];
    while (true) {
        for (rule x : currentFlow) {
            if (!x.rule) {
                if (x.destination == "A" || x.destination == "R") { //Will eventually be true
                    return x.destination == "A";
                }
                cout << "Next Label: " << x.destination << endl;
                currentFlow = workflows[x.destination];
                break;
            }
            int partValue;
            bool conditionFailed = false;
            switch (x.xmasValue) {
                case 'x':
                    partValue = toEval.x;
                    break;
                case 'm':
                    partValue = toEval.m;
                    break;
                case 'a':
                    partValue = toEval.a;
                    break;
                case 's':
                    partValue = toEval.s;
                    break;
            }
            if (x.condition == '>') {
                if (partValue > x.compValue) {
                    if (x.destination == "A" || x.destination == "R") {
                        return x.destination == "A";
                    }
                    cout << "Next Label: " << x.destination << endl;
                    currentFlow = workflows[x.destination];
                    break;
                }
            } else {
                if (partValue < x.compValue) {
                    if (x.destination == "A" || x.destination == "R") {
                        return x.destination == "A";
                    }
                    cout << "Next Label: " << x.destination << endl;
                    currentFlow = workflows[x.destination];
                    break;
                }
            }
        }
    }
}


rule parseRule(string trule) {
    rule x;
    if (trule.find(':') != string::npos) {
        // cout << "Parsing " << trule << endl;
        stringstream srule(trule);
        srule >> x.xmasValue >> x.condition;
        string temp;
        getline(srule, temp, ':');
        x.compValue = stoi(temp);
        srule >> x.destination;
    } else {
        x.rule = false;
        x.destination = trule.substr(0,trule.length() - 1); //All but the }
    }
    return x;
}

void parseWorkflow(string spart) {
    // cout << "Parsing Workflow: " << spart << endl;
    stringstream ps(spart);
    string label;
    getline(ps, label, '{');
    vector<rule> workflow;
    while (!ps.eof()) {
        string r;
        getline(ps,r,',');
        // cout << "Parsing Rule: " << r << endl;
        workflow.push_back(parseRule(r));
    }
    workflows[label] = workflow;
}

part parsePart(string spart) {
    char temp;
    part x;
    stringstream ps(spart);
    ps >> temp >> temp >> temp >> x.x; //Wow, I'm lazy!
    ps >> temp >> temp >> temp >> x.m;
    ps >> temp >> temp >> temp >> x.a;
    ps >> temp >> temp >> temp >> x.s;
    return x;
}

int main() {
    while (true) {
        string next = "";
        getline(cin, next);
        if (next == "")
            break;
        parseWorkflow(next);
    }
    long long accepted = 0;
    while (!cin.eof()) {
        string next = "";
        getline(cin, next);
        if (next == "")
            break;
        part x = parsePart(next);
        cout << "Evaluating:" << next << endl;
        if (evaluate(x)) {
            accepted += x.x + x.m + x.a + x.s;
        }
    }
    cout << accepted << endl;
    return 0;
}
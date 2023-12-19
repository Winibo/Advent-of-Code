#include "bits/stdc++.h"

using namespace std;

struct rule {
    bool rule = true;
    char condition;
    char xmasValue;
    int compValue;
    string destination;
    string printable;
};

//This is a Tree
map<string,vector<rule>> workflows; //Each workflow is a vector of rules

struct requirements {
    vector<int> range; //Min, Max for each x,m,a,s
};

long long solve(requirements limits, string workflow = "in") {
    vector<rule> current = workflows[workflow];
    long long answer = 0;
    for (rule x : current) {
        // cout << "Current Workflow: " << workflow << endl;
        // cout << "Current Rule: " << x.printable << endl;
        if (!x.rule) {
            if (x.destination == "A" || x.destination == "R") {
                if (x.destination == "A") { //Add nothing if we would reject when true
                    long long temp = 1;
                    for (int i = 0; i < 8; i += 2) {
                        // cout << limits.range[i] << ' ' << limits.range[i + 1] << endl;
                        temp *= (limits.range[i + 1] - limits.range[i]) + 1;
                    }
                    answer += temp;
                }
            } else {
                answer += solve(limits, x.destination);
            }
            // cout << workflow << endl;
            // cout << answer << endl;
            return answer;
        }
        int baseIdx = 0;
        switch (x.xmasValue) {
                case 'x':
                    baseIdx = 0;
                    break;
                case 'm':
                    baseIdx = 2;
                    break;
                case 'a':
                    baseIdx = 4;
                    break;
                case 's':
                    baseIdx = 6;
                    break;
            }
        if (x.condition == '<') {
            if (limits.range[baseIdx+1] < x.compValue) { //If the rule *must* be true
                if (x.destination == "A" || x.destination == "R") {
                    if (x.destination == "A") { //Add nothing if we would reject when true
                        long long temp = 1;
                        for (int i = 0; i < 8; i += 2) {
                            // cout << limits.range[i] << ' ' << limits.range[i + 1] << endl;
                            temp *= (limits.range[i + 1] - limits.range[i]) + 1;
                        }
                        answer += temp;
                    }
                } else {
                    answer += solve(limits, x.destination);
                }
                // cout << workflow << endl;
                // cout << answer << endl;
                return answer;
            } else {
                //Assume true
                if (x.destination == "A" || x.destination == "R") {
                    long long temp = limits.range[baseIdx + 1];
                    limits.range[baseIdx + 1] = x.compValue - 1;
                    if (x.destination == "A") { //Add nothing if we would reject when true
                        long long temp = 1;
                        for (int i = 0; i < 8; i += 2) {
                            // cout << limits.range[i] << ' ' << limits.range[i + 1] << endl;
                            temp *= (limits.range[i + 1] - limits.range[i]) + 1;
                        }
                        answer += temp;
                    }
                    limits.range[baseIdx + 1] = temp;
                } else {
                    long long temp = limits.range[baseIdx + 1];
                    limits.range[baseIdx + 1] = x.compValue - 1;
                    answer += solve(limits, x.destination);
                    limits.range[baseIdx + 1] = temp;
                }
                //Assume false
                limits.range[baseIdx] = max(x.compValue, limits.range[baseIdx]);
            }
        } else { // Condition is >
            if (limits.range[baseIdx] > x.compValue) { //If the rule *must* be true
                if (x.destination == "A" || x.destination == "R") {
                    if (x.destination == "A") { //Add nothing if we would reject when true
                        long long temp = 1;
                        for (int i = 0; i < 8; i += 2) {
                            // cout << limits.range[i] << ' ' << limits.range[i + 1] << endl;
                            temp *= (limits.range[i + 1] - limits.range[i]) + 1;
                        }
                        answer += temp;
                    }
                } else {
                    answer += solve(limits, x.destination);
                }
                // cout << workflow << endl;
                // cout << answer << endl;
                return answer;
            } else {
                //Assume true
                if (x.destination == "A" || x.destination == "R") {
                    long long temp = limits.range[baseIdx];
                    limits.range[baseIdx] = x.compValue + 1;
                    if (x.destination == "A") { //Add nothing if we would reject when true
                        // cout << "Rule Accepts:" << endl;
                        long long temp = 1;
                        for (int i = 0; i < 8; i += 2) {
                            // cout << limits.range[i] << ' ' << limits.range[i + 1] << endl;
                            temp *= (limits.range[i + 1] - limits.range[i]) + 1;
                        }
                        // cout << "Adding: " << temp << endl;
                        answer += temp;
                    }
                    limits.range[baseIdx] = temp;
                } else {
                    long long temp = limits.range[baseIdx];
                    limits.range[baseIdx] = x.compValue + 1;
                    answer += solve(limits, x.destination);
                    limits.range[baseIdx] = temp;
                }
                //Assume false
                limits.range[baseIdx + 1] = min(x.compValue, limits.range[baseIdx + 1]);
            }
        }
    }
    // cout << workflow << endl;
    // cout << answer << endl;
    return answer;
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
        x.printable = trule;
    } else {
        x.rule = false;
        x.destination = trule.substr(0,trule.length() - 1); //All but the }
        x.printable = trule.substr(0,trule.length() - 1);
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

int main() {
    while (true) {
        string next = "";
        getline(cin, next);
        if (next == "")
            break;
        parseWorkflow(next);
    }
    
    requirements x;
    for (int i = 0; i < 8; i++) {
        if (i % 2 == 0) {
            x.range.push_back(1);
        } else {
            x.range.push_back(4000);
        }
    }

    cout << solve(x) << endl;
    return 0;
}
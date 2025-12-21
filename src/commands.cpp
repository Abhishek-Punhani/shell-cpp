#include<bits/stdc++.h>
#include"headers/commands.hpp"
using namespace std;


void handleCommand(const std::vector<std::string>& tokens) {
    if (tokens[0] == "echo") {
        handleEcho(tokens);
    } else {
        cout << tokens[0] << ": command not found" << endl;
    }
}

void handleEcho(const std::vector<std::string>& tokens) {
    for (size_t i = 1; i < tokens.size(); ++i) {
        cout << tokens[i];
        if (i < tokens.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}


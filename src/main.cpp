#include <bits/stdc++.h>
#include "headers/commands.hpp"
using namespace std;

int main() {
    cout << std::unitbuf;
    cerr << std::unitbuf;
    
    while (true) {
        cout << "$ ";
        string input;
        getline(cin, input);
        
        if (input == "exit") {
            break;
        }
        
        vector<string> tokens;
        string token;
        bool in_quotes = false;
        for (size_t i = 0; i < input.length(); ++i) {
            char c = input[i];
            if (c == '\'' && !in_quotes) {
                in_quotes = true;
                token += c;  // Include the quote
            } else if (c == '\'' && in_quotes) {
                in_quotes = false;
                token += c;  // Include the quote
                tokens.push_back(token);
                token.clear();
            } else if (isspace(c) && !in_quotes) {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            } else {
                token += c;
            }
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }
        
        if (tokens.empty()) {
            continue;
        }
        
        handleCommand(tokens);
    }
    
    return 0;
}
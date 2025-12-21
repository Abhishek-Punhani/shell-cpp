#include<bits/stdc++.h>
#include"headers/commands.hpp"
using namespace std;
int main() {
  cout << std::unitbuf;
  cerr << std::unitbuf;
  while (true)
  {
    cout << "$ ";
    string input;

    getline(cin, input);
    if (input == "exit") {
      break;
    }
    stringstream ss(input);
    vector<string> tokens;
    string token;
    while (ss >> token) {
      tokens.push_back(token);
    }
    if (tokens.empty()) {
      continue;
    }

    handleCommand(tokens);
  }
  
  }

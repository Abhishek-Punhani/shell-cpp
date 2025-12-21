#include<bits/stdc++.h>
using namespace std;
int main() {
  // Flush after every std::cout / std:cerr
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
    if(tokens[0]=="echo"){
      for(size_t i=1;i<tokens.size();i++){
        cout<<tokens[i];
        if(i!=tokens.size()-1)cout<<" ";
      }
      cout<<endl;
      continue;
    }
    cout << input << ": command not found" << endl;

  }
  
  }

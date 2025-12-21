#include<bits/stdc++.h>
#include"headers/commands.hpp"
using namespace std;

vector<string> shell_builtin_commands={"echo","type","exit"};

bool is_executable(const string &token) {
    const char* path = getenv("PATH");
    if (!path) {
        return false;
    }
    string path_str = path;
    stringstream ss(path_str);
    string dir;
    while (getline(ss, dir, ':')) {
        string full_path = dir + "/" + token;
        if (access(full_path.c_str(), X_OK) == 0) {  // Check if executable
            cout << token << " is " << full_path << endl;
            return true;
        }
    }
    return false;
}

void handleCommand(const std::vector<std::string>& tokens) {
    if (tokens[0] == "echo") {
        handleEcho(tokens);
    }
    else if (tokens[0] == "type") {
        handleType(tokens);
    }
     else {
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

void handleType(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        cout << "type: missing operand" << endl;
        return;
    }

    const string token=tokens[1];
    if(shell_builtin_commands.end()!=find(shell_builtin_commands.begin(),shell_builtin_commands.end(),token)){
        cout<<token<<" is a shell builtin"<<endl;
    }else if(is_executable(token)){
        // is_executable already prints the path
    }else{
        cout<<token<<": not found" << endl;
    }

}


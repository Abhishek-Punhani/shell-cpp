#include<bits/stdc++.h>
#include"headers/commands.hpp"
#include<unistd.h>
#include <sys/wait.h>
using namespace std;

vector<string> shell_builtin_commands={"echo","type","exit","pwd","cd"};

string is_executable(const string &token) {
    const char* path = getenv("PATH");
    if (!path) {
        return "";  // PATH not set
    }
    string path_str = path;
    stringstream ss(path_str);
    string dir;
    while (getline(ss, dir, ':')) {
        string full_path = dir + "/" + token;
        if (access(full_path.c_str(), X_OK) == 0) {  // Check if executable
            return full_path;
        }
    }
    return "";
}

void execute_executables(const string &exec_path, const vector<string> &tokens) {
    pid_t pid = fork();
    if (pid == 0) {  // Child process
        vector<char*> args;
        for (const auto& token : tokens) {
            args.push_back(const_cast<char*>(token.c_str()));
        }
        args.push_back(nullptr);
        execv(exec_path.c_str(), args.data());
        // If execv returns, an error occurred
        cerr << "Failed to execute " << exec_path << endl;
        exit(1);
    } else if (pid > 0) {  // Parent process
        int status;
        waitpid(pid, &status, 0);
    } else {
        cerr << "Fork failed" << endl;
    }

}

void handleCommand(const std::vector<std::string>& tokens) {
    if (tokens[0] == "echo") {
        handleEcho(tokens);
    }
    else if (tokens[0] == "type") {
        handleType(tokens);
    }
     else {
        string exec_path=is_executable(tokens[0]);
        if(!exec_path.empty()){
           execute_executables(exec_path,tokens);
            return;
        }
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
    }else {
        string exec_path=is_executable(token);
        if(!exec_path.empty()){
            cout<<token<<" is "<<exec_path<<endl;
        }else{
            cout<<token<<": not found"<<endl;
        }
    }

}


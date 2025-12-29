#include <bits/stdc++.h>
#include "headers/commands.hpp"
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

bool isEmptyQuoted(const string &token)
{
    return token.length() >= 2 && ((token[0] == '\'' && token[1] == '\'') || (token[0] == '"' && token[1] == '"')) && (token.substr(1, token.length() - 2).empty());
}
string is_executable(const string &token)
{
    const char *path = getenv("PATH");
    if (!path)
    {
        return ""; // PATH not set
    }
    string path_str = path;
    stringstream ss(path_str);
    string dir;
    while (getline(ss, dir, ':'))
    {
        string full_path = dir + "/" + token;
        if (access(full_path.c_str(), X_OK) == 0)
        { // Check if executable
            return full_path;
        }
    }
    return "";
}

string parse_qoutes(const vector<string> &tokens)
{
    string res = "";
    if (tokens.size() < 2)
    {
        return res;
    }
    for (size_t i = 1; i < tokens.size(); ++i)
    {
        if (isEmptyQuoted(tokens[i]))
            continue;
        if (!tokens[i].empty())
        {
            res += tokens[i];
        }
        if (i + 1 < tokens.size() && (!isEmptyQuoted(tokens[i + 1])))
        {
            res += " ";
        }
    }
    return res;
}
void execute_executables(const string &exec_path, const vector<string> &tokens)
{
    pid_t pid = fork();
    if (pid == 0)
    { // Child process
        vector<string> processed_args;
        vector<char *> args;

        // argv[0] is the command name
        args.push_back(const_cast<char *>(tokens[0].c_str()));

        // Process arguments individually using parse_qoutes logic
        for (size_t i = 1; i < tokens.size(); ++i)
        {
            vector<string> single_arg_vec = {"placeholder", tokens[i]};
            string processed_token = parse_qoutes(single_arg_vec);
            processed_args.push_back(processed_token);
        }

        // Convert string vector to char* vector for execv
        for (auto &arg : processed_args)
        {
            args.push_back(const_cast<char *>(arg.c_str()));
        }
        args.push_back(nullptr);

        execv(exec_path.c_str(), args.data());
        // If execv returns, an error occurred
        cerr << "Failed to execute " << exec_path << endl;
        exit(1);
    }
    else if (pid > 0)
    { // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
    else
    {
        cerr << "Fork failed" << endl;
    }
}

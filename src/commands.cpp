#include <bits/stdc++.h>
#include "headers/commands.hpp"
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

vector<string> shell_builtin_commands = {"echo", "type", "exit", "pwd", "cd"};
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

        // Process arguments individually to preserve spaces within quotes
        for (size_t i = 1; i < tokens.size(); ++i)
        {
            string token = tokens[i];
            processed_args.push_back(token);
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

void handleCommand(const std::vector<std::string> &tokens)
{
    if (tokens[0] == "echo")
    {
        handleEcho(tokens);
    }
    else if (tokens[0] == "type")
    {
        handleType(tokens);
    }
    else if (tokens[0] == "pwd")
    {
        handlePwd();
    }
    else if (tokens[0] == "cd")
    {
        handleCd(tokens);
    }
    else
    {
        string exec_path = is_executable(tokens[0]);
        if (!exec_path.empty())
        {
            execute_executables(exec_path, tokens);
            return;
        }
        cout << tokens[0] << ": command not found" << endl;
    }
}

void handleEcho(const std::vector<std::string> &tokens)
{
    cout << parse_qoutes(tokens) << endl;
}

void handleType(const std::vector<std::string> &tokens)
{
    if (tokens.size() < 2)
    {
        cout << "type: missing operand" << endl;
        return;
    }

    const string token = tokens[1];
    if (shell_builtin_commands.end() != find(shell_builtin_commands.begin(), shell_builtin_commands.end(), token))
    {
        cout << token << " is a shell builtin" << endl;
    }
    else
    {
        string exec_path = is_executable(token);
        if (!exec_path.empty())
        {
            cout << token << " is " << exec_path << endl;
        }
        else
        {
            cout << token << ": not found" << endl;
        }
    }
}

void handlePwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr)
    {
        cout << cwd << endl;
    }
    else
    {
        cerr << "pwd: failed to get current directory" << endl;
    }
}

void handleCd(const std::vector<std::string> &tokens)
{
    if (tokens.size() < 2)
    {
        cerr << "cd: missing operand" << endl;
        return;
    }
    if (tokens.size() > 2)
    {
        cerr << "cd: too many arguments" << endl;
        return;
    }
    const string &path = tokens[1];
    if (path == "~")
    {
        const char *home = getenv("HOME");
        if (home)
        {
            if (chdir(home) != 0)
            {
                cerr << "cd: " << home << ": No such file or directory" << endl;
            }
        }
        else
        {
            cerr << "cd: HOME not set" << endl;
        }
        return;
    }
    if (chdir(path.c_str()) != 0)
    {
        cerr << "cd: " << path << ": No such file or directory" << endl;
    }
}

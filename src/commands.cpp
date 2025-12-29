#include <bits/stdc++.h>
#include "headers/commands.hpp"
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

vector<string> shell_builtin_commands = {"echo", "type", "exit", "pwd", "cd"};

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

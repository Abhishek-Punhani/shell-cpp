#include <bits/stdc++.h>
#include "headers/commands.hpp"
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

vector<string> shell_builtin_commands = {"echo", "type", "exit", "pwd", "cd"};

ExecutionResult handleCommand(const vector<string> &tokens, bool redirect_stdout, bool redirect_stderr)
{
    ExecutionResult r{"", "", -1};

    if (tokens[0] == "echo")
    {
        r = handleEcho(tokens);
    }
    else if (tokens[0] == "type")
    {
        r = handleType(tokens);
    }
    else if (tokens[0] == "pwd")
    {
        r = handlePwd();
    }
    else if (tokens[0] == "cd")
    {
        r = handleCd(tokens);
    }
    else
    {
        string exec_path = is_executable(tokens[0]);
        if (!exec_path.empty())
        {
            r = execute_executables(exec_path, tokens);
        }
        else
        {
            r.err = tokens[0] + ": command not found\n";
            r.exit_code = 127;
        }
    }

    // Print results unless caller requested redirection
    if (!redirect_stdout && !r.out.empty())
        cout << r.out;
    if (!redirect_stderr && !r.err.empty())
        cerr << r.err;

    return r;
}

ExecutionResult handleEcho(const vector<string> &tokens)
{
    ExecutionResult r{"", "", 0};
    r.out = parse_qoutes(tokens);
    if (!r.out.empty() && r.out.back() != '\n')
        r.out += '\n';
    return r;
}

ExecutionResult handleType(const vector<string> &tokens)
{
    ExecutionResult r{"", "", 0};
    if (tokens.size() < 2)
    {
        r.err = "type: missing operand\n";
        r.exit_code = 2;
        return r;
    }

    const string token = tokens[1];
    if (shell_builtin_commands.end() != find(shell_builtin_commands.begin(), shell_builtin_commands.end(), token))
    {
        r.out = token + " is a shell builtin\n";
    }
    else
    {
        string exec_path = is_executable(token);
        if (!exec_path.empty())
        {
            r.out = token + " is " + exec_path + "\n";
        }
        else
        {
            r.err = token + ": not found\n";
            r.exit_code = 1;
        }
    }
    return r;
}

ExecutionResult handlePwd()
{
    ExecutionResult r{"", "", 0};
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr)
    {
        r.out = string(cwd) + "\n";
    }
    else
    {
        r.err = "pwd: failed to get current directory\n";
        r.exit_code = 1;
    }
    return r;
}

ExecutionResult handleCd(const vector<string> &tokens)
{
    ExecutionResult r{"", "", 0};
    if (tokens.size() < 2)
    {
        r.err = "cd: missing operand\n";
        r.exit_code = 2;
        return r;
    }
    if (tokens.size() > 2)
    {
        r.err = "cd: too many arguments\n";
        r.exit_code = 2;
        return r;
    }
    const string &path = tokens[1];
    if (path == "~")
    {
        const char *home = getenv("HOME");
        if (home)
        {
            if (chdir(home) != 0)
            {
                r.err = string("cd: ") + home + ": No such file or directory\n";
                r.exit_code = 1;
            }
        }
        else
        {
            r.err = "cd: HOME not set\n";
            r.exit_code = 1;
        }
        return r;
    }
    if (chdir(path.c_str()) != 0)
    {
        r.err = string("cd: ") + path + ": No such file or directory\n";
        r.exit_code = 1;
    }
    return r;
}

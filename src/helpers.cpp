#include <bits/stdc++.h>
#include "headers/commands.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

void pushToken(string &token, vector<string> &tokens, bool &redirect_stdout, bool &redirect_stderr, bool &override_stdout, bool &override_stderr, ExecutionResult &prev_res)
{
    if (token == ">" || token == "1>" || token == ">>" || token == "1>>")
    {
        redirect_stdout = true;
        prev_res = handleCommand(tokens, redirect_stdout, redirect_stderr);
        tokens.clear();
        if (token == ">>" || token == "1>>")
            override_stdout = false;
    }
    else if (token == "2>" || token == "2>>")
    {
        redirect_stderr = true;
        prev_res = handleCommand(tokens, redirect_stdout, redirect_stderr);
        tokens.clear();
        if (token == "2>>")
            override_stderr = false;
    }
    else
    {
        tokens.push_back(token);
    }
    token.clear();
}

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

ExecutionResult execute_executables(const string &exec_path, const vector<string> &tokens)
{
    int out_pipe[2];
    int err_pipe[2];
    pipe(out_pipe);
    pipe(err_pipe);

    pid_t pid = fork();
    if (pid == 0)
    {
        // child: redirect stdout/stderr to pipes
        dup2(out_pipe[1], STDOUT_FILENO);
        dup2(err_pipe[1], STDERR_FILENO);

        // close unused fds
        close(out_pipe[0]);
        close(out_pipe[1]);
        close(err_pipe[0]);
        close(err_pipe[1]);

        // build argv
        vector<string> processed_args;
        vector<char *> args;
        args.push_back(const_cast<char *>(tokens[0].c_str()));
        for (size_t i = 1; i < tokens.size(); ++i)
        {
            vector<string> single_arg_vec = {"placeholder", tokens[i]};
            processed_args.push_back(parse_qoutes(single_arg_vec));
        }
        for (auto &arg : processed_args)
            args.push_back(const_cast<char *>(arg.c_str()));
        args.push_back(nullptr);

        execv(exec_path.c_str(), args.data());
        _exit(127);
    }

    // parent
    close(out_pipe[1]);
    close(err_pipe[1]);

    string stdout_out;
    string stderr_out;
    char buf[4096];
    ssize_t n;

    // read stdout
    while ((n = read(out_pipe[0], buf, sizeof(buf))) > 0)
        stdout_out.append(buf, n);
    // read stderr
    while ((n = read(err_pipe[0], buf, sizeof(buf))) > 0)
        stderr_out.append(buf, n);

    close(out_pipe[0]);
    close(err_pipe[0]);

    int status = 0;
    waitpid(pid, &status, 0);
    int exit_code = -1;
    if (WIFEXITED(status))
        exit_code = WEXITSTATUS(status);

    return ExecutionResult{stdout_out, stderr_out, exit_code};
}

void write_execution_result_to_file(const ExecutionResult &result, const std::string &path, bool is_err, bool override)
{
    int flags = O_WRONLY | O_CREAT;
    if (override)
    {
        flags |= O_TRUNC;
    }
    else
        flags |= O_APPEND;
    int fd = open(
        path.c_str(),
        flags,
        0644);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    if (!result.out.empty() && !is_err)
        write(fd, result.out.data(), result.out.size());

    if (!result.err.empty() && is_err)
        write(fd, result.err.data(), result.err.size());

    close(fd);
}

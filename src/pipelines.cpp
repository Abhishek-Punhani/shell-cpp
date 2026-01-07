#include "headers/commands.hpp"
void exec_child(const vector<string> &tokens)
{
    ExecutionResult r;

    if (tokens[0] == "echo")
        r = handleEcho(tokens);
    else if (tokens[0] == "pwd")
        r = handlePwd();
    else if (tokens[0] == "type")
        r = handleType(tokens);
    else
        _exit(127);

    // write directly to fds (NOT cout)
    if (!r.out.empty())
        write(STDOUT_FILENO, r.out.data(), r.out.size());
    if (!r.err.empty())
        write(STDERR_FILENO, r.err.data(), r.err.size());

    _exit(r.exit_code);
}

void execute_pipelines(vector<vs> &pipeline)
{
    int prev_read = STDIN_FILENO;
    for (size_t i = 0; i < pipeline.size(); i++)
    {
        int pipefd[2];
        bool last = (i == pipeline.size() - 1);
        if (!last)
            pipe(pipefd);
        pid_t pid = fork();
        if (pid == 0)
        { // stdin
            if (prev_read != STDIN_FILENO)
            {
                dup2(prev_read, STDIN_FILENO);
                close(prev_read);
            }
            // stdout
            if (!last)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }
            if (find(all(custom_commands), pipeline[i][0]) != custom_commands.end())
            {
                exec_child(pipeline[i]);
            }
            else
            {
                vector<char *> argv;
                for (auto &s : pipeline[i])
                    argv.push_back(const_cast<char *>(s.c_str()));
                argv.push_back(nullptr);
                execvp(argv[0], argv.data());
                perror("execvp");
                _exit(127);
            }
        }
        // parent
        if (prev_read != STDIN_FILENO)
            close(prev_read);
        if (!last)
        {
            close(pipefd[1]);
            prev_read = pipefd[0];
        }
    }
    while (wait(nullptr) > 0)
        ;
}
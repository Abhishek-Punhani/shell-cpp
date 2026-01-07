#include "headers/commands.hpp"
using namespace std;
int main()
{
    cout << std::unitbuf;
    cerr << std::unitbuf;

    listen_bindings();
    while (true)
    {
        string input;
        char *line_c = readline("$ ");
        if (!line_c)
            break;
        input = line_c;
        add_to_history(input);
        if (input == "exit")
        {
            break;
        }

        vector<string> tokens;
        Config cfg;
        vector<vs> pipelines;
        ExecutionResult prev_res{"", "", -1};
        tokenize(tokens, cfg, pipelines, prev_res, input);
        if (pipelines.size() > 0)
        {
            if (!tokens.empty())
                pipelines.push_back(tokens);
            execute_pipelines(pipelines);
            continue;
        }
        if (tokens.empty())
        {
            continue;
        }
        if (cfg.redirect_stderr)
        {
            write_execution_result_to_file(prev_res, tokens[0], true, cfg.override_stderr);
            cfg.reset();
        }
        else if (cfg.redirect_stdout)
        {
            write_execution_result_to_file(prev_res, tokens[0], false, cfg.override_stdout);
            cfg.reset();
        }
        else
            handleCommand(tokens, cfg.redirect_stdout, cfg.redirect_stderr);
    }

    return 0;
}
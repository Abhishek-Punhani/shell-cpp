#include <bits/stdc++.h>
#include "headers/commands.hpp"
using namespace std;

int main()
{
    cout << std::unitbuf;
    cerr << std::unitbuf;

    while (true)
    {
        cout << "$ ";
        string input;
        if (!getline(cin, input))
        {
            break;
        }

        if (input == "exit")
        {
            break;
        }

        vector<string> tokens;
        string token;
        bool in_quotes = false;
        bool in_double_quotes = false;
        bool in_backslash = false;
        bool redirect_stdout = false;
        bool redirect_stderr = false;
        bool override_stdout = false;
        bool override_stderr = false;
        ExecutionResult prev_res{"", "", -1};
        for (size_t i = 0; i < input.length(); ++i)
        {
            char c = input[i];
            if (in_backslash)
            {
                if (in_double_quotes)
                {
                    if (c == '$' || c == '`' || c == '"' || c == '\\' || c == '\n')
                    {
                        token += c;
                    }
                    else
                    {
                        token += '\\';
                        token += c;
                    }
                }
                else
                {
                    token += c;
                }
                in_backslash = false;
                continue;
            }
            if (c == '\\')
            {
                if (!in_quotes || in_double_quotes)
                {
                    in_backslash = true;
                    continue;
                }
                else
                {
                    token += c;
                    continue;
                }
            }
            if ((c == '\'' || c == '"') && !in_quotes)
            {
                if (c == '"')
                    in_double_quotes = true;
                in_quotes = true;
            }
            else if ((c == '\'' || c == '"') && in_quotes)
            {
                if (c == '\'' && in_double_quotes)
                {
                    token += c;
                    continue;
                }
                if (c == '"' && in_quotes && !in_double_quotes)
                {
                    token += c;
                    continue;
                }
                in_quotes = false;
                in_double_quotes = false;
            }
            else if (isspace(c) && !in_quotes)
            {
                if (!token.empty())
                {
                    pushToken(token, tokens, redirect_stdout, redirect_stderr, override_stdout, override_stderr, prev_res);
                }
            }
            else
            {
                token += c;
            }
        }
        if (!token.empty() || in_quotes)
        {
            pushToken(token, tokens, redirect_stdout, redirect_stderr, override_stdout, override_stderr, prev_res);
        }

        if (tokens.empty())
        {
            continue;
        }
        if (redirect_stderr)
        {
            write_execution_result_to_file(prev_res, tokens[0], true, override_stderr);
            redirect_stderr = override_stderr = false;
        }
        else if (redirect_stdout)
        {
            write_execution_result_to_file(prev_res, tokens[0], false, override_stdout);
            redirect_stdout = override_stdout = false;
        }
        else
            handleCommand(tokens, redirect_stdout, redirect_stderr);
    }

    return 0;
}
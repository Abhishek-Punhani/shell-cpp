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
        bool token_has_quotes = false;
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
                token_has_quotes = true;
            }
            else if ((c == '\'' || c == '"') && in_quotes)
            {
                if (c == '\'' && in_double_quotes)
                {
                    token += c;
                    continue;
                }
                in_quotes = false;
                in_double_quotes = false;
            }
            else if (isspace(c) && !in_quotes)
            {
                if (!token.empty() || token_has_quotes)
                {
                    tokens.push_back(token);
                    token.clear();
                    token_has_quotes = false;
                }
            }
            else
            {
                token += c;
            }
        }
        if (!token.empty() || token_has_quotes)
        {
            tokens.push_back(token);
        }

        if (tokens.empty())
        {
            continue;
        }

        handleCommand(tokens);
    }

    return 0;
}
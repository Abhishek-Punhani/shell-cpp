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
        bool in_double_quotes=false;
        for (size_t i = 0; i < input.length(); ++i)
        {
            char c = input[i];
            if (i > 0 && ((input[i] == '\'' && !in_quotes && input[i - 1] == '\'' )|| (input[i] == '"' && !in_quotes && input[i - 1] == '"' )))
            {
                tokens.push_back("''");
            }

            if ((c == '\'' || c=='"') && !in_quotes)
            {   if(c=='"') in_double_quotes=true;
                if (!token.empty())
                {
                    tokens.push_back(token);
                    token.clear();
                }
                in_quotes = true;
                token += c; // Include the quote
            }
            else if ((c == '\'' || c=='"') && in_quotes)
            {   
                if(c == '\'' && in_double_quotes){
                    token+=c;
                    continue;
                }
                in_quotes = false;
                in_double_quotes=false;
                token += c; // Include the quote
                tokens.push_back(token);
                token.clear();
            }
            else if (isspace(c) && !in_quotes)
            {
                if (!token.empty())
                {
                    tokens.push_back(token);
                    token.clear();
                }
            }
            else
            {
                token += c;
            }
        }
        if (!token.empty())
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
#include "headers/commands.hpp"

vs history;

void add_to_history(string &s)
{
    history.pb(s);
}

void print_history(int last)
{
    if (last == -1)
    {
        rep(i, (int)history.size()) cout << i << " " << history[i] << endl;
    }
    else
    {
        int idx = max(0, (int)history.size() - last);
        rep1(i, idx, (int)history.size() - 1)
        {
            cout << "  " << i + 1 << " " << history[i] << endl;
        }
    }
}
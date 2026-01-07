#include "headers/commands.hpp"

vs history;
int history_idx = -1;

void add_to_history(string &s)
{
    history.pb(s);
    history_idx = history.size() - 1;
}

void inc_history_idx()
{
    if (!history.empty() && history_idx != -1)
    {
        history_idx++;
    }
}

void dec_history_idx()
{
    if (!history.empty() && history_idx != 0)
    {
        history_idx--;
    }
}

string get_history_idx()
{
    if (!history.empty() && history_idx != -1)
    {
        return history[history_idx];
    }
    return "";
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
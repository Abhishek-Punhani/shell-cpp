#include "headers/commands.hpp"

vs history;
int history_idx = -1;
string curr = "";
void add_to_history(string &s)
{
    if (!s.empty())
        history.pb(s);
    history_idx = -1;
}

void inc_history_idx()
{

    if (!history.empty() && history_idx != -1)
    {
        string line(rl_line_buffer);
        history[history_idx] = line;
        if (history_idx < (int)history.size() - 1)
            history_idx++;
        else
            history_idx = -1;
        return;
    }
}

void dec_history_idx()
{
    if (history.empty())
        return;

    string line(rl_line_buffer);
    if (history_idx == -1)
    {
        curr = line;
        history_idx = (int)history.size() - 1;
    }
    else if (history_idx > 0)
    {
        history[history_idx] = line;
        history_idx--;
    }
}

string get_history_idx()
{
    if (!history.empty() && history_idx != -1)
    {
        return history[history_idx];
    }
    else
        return curr;
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
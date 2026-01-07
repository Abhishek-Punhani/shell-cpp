#include "headers/commands.hpp"

vs history;
int history_idx = -1;
size_t history_written_upto = 0;

string curr = "";
void check_path(string &path)
{
    if (path == HISTORY_FILE)
    {
        const char *hispath = getenv("HISTFILE");
        if (!hispath)
        {
            return;
        }

        path = string(hispath);
    }
}
void load_history(string path)
{
    check_path(path);
    int fd = open(path.c_str(), O_RDONLY);
    if (fd < 0)
    {
        // history file missing
        return;
    }

    char buffer[4096];
    string curr;
    ssize_t n;

    while ((n = read(fd, buffer, sizeof(buffer))) > 0)
    {
        for (ssize_t i = 0; i < n; i++)
        {
            if (buffer[i] == '\n')
            {
                if (!curr.empty())
                    history.pb(curr);
                curr.clear();
            }
            else
            {
                curr.push_back(buffer[i]);
            }
        }
    }

    if (!curr.empty())
    {
        history.pb(curr);
    }
    close(fd);
    history_written_upto = history.size();
}

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
void write_history(string path, bool append)
{   
    check_path(path);
    int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
    size_t start = append ? history_written_upto : 0;
    int fd = open(path.c_str(), flags, 0644);
    if (fd < 0)
    {
        perror("history_write");
        return;
    }

    for (size_t i = start; i < history.size(); i++)

    {
        ssize_t n = write(fd, history[i].data(), history[i].size());
        if (n < 0)
        {
            perror("write");
            break;
        }
        write(fd, "\n", 1);
    }

    close(fd);
    history_written_upto=history.size();
}

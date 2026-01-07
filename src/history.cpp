#include "headers/commands.hpp"

vs history;
int history_idx = -1;
string curr = "";
void check_path(string &path)
{
    if (path == HISTORY_FILE)
    {
        const char *home = getenv("HOME");
        if (!home)
        {
            return;
        }

        path = string(home) + "/" + path;
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
void write_history(string path)
{
    check_path(path);

    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror("history_write");
        return;
    }

    for (const auto &cmd : history)
    {
        ssize_t n = write(fd, cmd.data(), cmd.size());
        if (n < 0)
        {
            perror("write");
            break;
        }
        write(fd, "\n", 1);
    }

    close(fd);
}

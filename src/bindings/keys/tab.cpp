#include "../../headers/commands.hpp"

int on_tab(int count, int key)
{
    string line(rl_line_buffer);
    int cursor = rl_point;
    string completion = "";
    if (line == "ec")
    {
        completion = "echo";
    }
    else if (line == "ex")
    {
        completion = "exit";
    }
    if (!completion.empty())
    {
        rl_replace_line(completion.c_str(), 0);
        rl_point = rl_end;
    }
    rl_redisplay();
    return 0;
}
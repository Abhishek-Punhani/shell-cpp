#include "../../headers/commands.hpp"

void handle_update()
{
    string to_replace = get_history_idx();
    if (!to_replace.empty())
    {
        rl_replace_line(to_replace.c_str(), 0);
        rl_redisplay();
        rl_point = rl_end;
    }
}
int previous_input(int count, int key)
{
    dec_history_idx();
    handle_update();
    return 0;
}

int next_input(int count, int key)
{
    inc_history_idx();
    handle_update();
    return 0;
}

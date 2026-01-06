#include "../../headers/commands.hpp"

int on_tab(int count, int key)
{
    static int tab_cnt = 0;
    string line(rl_line_buffer);
    if (line.empty())
        return 0;
    int cursor = rl_point;
    vs res = autocomplete(line);
    if (res.size() == 0)
    {
        write(STDOUT_FILENO, "\a", 1);
        tab_cnt = 0;
        return 0;
    }
    else if (res.size() == 1)
    {
        res[0] += " ";
        rl_replace_line(res[0].c_str(), 0);
        rl_point = rl_end;
        tab_cnt = 0;
    }
    else
    {
        tab_cnt++;
        if (tab_cnt == 1)
        {
            write(STDOUT_FILENO, "\a", 1);
        }
        else
        {
            sort(all(res));
            cout << endl;
            print(res);
            rl_on_new_line();
            rl_replace_line(line.c_str(), 0);
            rl_point = cursor;
            tab_cnt = 0;
        }
    }
    rl_redisplay();
    return 0;
}
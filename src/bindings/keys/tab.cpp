#include "../../headers/commands.hpp"

int on_tab(int count, int key)
{
    string line(rl_line_buffer);
    int cursor = rl_point;
    vs res = autocomplete(line);
    if (res.size() == 0)
    {   
        cout<<'\x07';
        return 0;
    }
    else if (res.size() == 1)
    {
        res[0] += " ";
        rl_replace_line(res[0].c_str(), 0);
        rl_point = rl_end;
    }
    else
    {
        cout << endl;
        print(res);
    }
    rl_redisplay();
    return 0;
}
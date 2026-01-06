#include "../../headers/commands.hpp"

vs autocomplete_builtins(const string &prefix)
{
    vs res;
    for (const auto &b : shell_builtin_commands)
        if (b.rfind(prefix, 0) == 0)
            res.push_back(b);
    sort(all(res));
    res.erase(unique(all(res)), res.end());
    return res;
}

vs autocomplete_executables(const string &prefix)
{
    vs res;
    for (const auto &e : get_path_executables())
        if (e.rfind(prefix, 0) == 0)
            res.push_back(e);
    sort(all(res));
    res.erase(unique(all(res)), res.end());
    return res;
}

vs autocomplete(string input)
{
    vs res = autocomplete_builtins(input);
    vs ex = autocomplete_executables(input);
    res.insert(res.end(), ex.begin(), ex.end());
    sort(all(res));
    res.erase(unique(all(res)), res.end());
    return res;
}

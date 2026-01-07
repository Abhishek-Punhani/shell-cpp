#include "../headers/commands.hpp"

void listen_bindings()
{
    rl_bind_key('\t', on_tab);
    rl_bind_keyseq("\e[A", previous_input); // Up arrow
    rl_bind_keyseq("\e[B", next_input);     // Down arrow
}

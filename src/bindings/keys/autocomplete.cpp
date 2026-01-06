#include "../../headers/commands.hpp"

vs autocomplete(string input)
{
    Trie *trie = new Trie();
    trie->insertArray(shell_builtin_commands);
    vs res;
    trie->get_prefix_matches(input, res, input, trie->getPrefixNode(input));
    return res;
}

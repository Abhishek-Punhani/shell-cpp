#include "../../headers/commands.hpp"

vs autocomplete(string input)
{
    Trie *trie = new Trie();
    trie->insertArray(shell_builtin_commands);
    vs res;
    Node *prefixNode = trie->getPrefixNode(input);
    if (prefixNode != nullptr)
        trie->get_prefix_matches(input, res, input, prefixNode);
    return res;
}

#include "headers/commands.hpp"

Node::Node() : flag(false)
{
    for (int i = 0; i < 26; i++)
        links[i] = nullptr;
}

Node::~Node()
{
    for (int i = 0; i < 26; i++)
        delete links[i];
}

bool Node::containsKey(char ch) const
{
    return links[ch - 'a'] != nullptr;
}

void Node::put(char ch, Node *node)
{
    links[ch - 'a'] = node;
}

Node *Node::get(char ch) const
{
    return links[ch - 'a'];
}

void Node::setEnd()
{
    flag = true;
}

bool Node::isEnd() const
{
    return flag;
}

Trie::Trie() : root(new Node()) {}
Trie::~Trie() { delete this->root; }

void Trie::insert(const string &word)
{
    Node *node = this->root;
    for (char ch : word)
    {
        if (!node->containsKey(ch))
            node->put(ch, new Node());
        node = node->get(ch);
    }
    node->setEnd();
}

Node *Trie::getPrefixNode(const string &input)
{
    Node *node = this->root;
    for (char ch : input)
    {
        if (!node->containsKey(ch))
            return nullptr;
        node = node->get(ch);
    }
    return node;
}

void Trie::get_prefix_matches(const string &input, vector<string> &res, string curr, Node *node)
{   
    if (node->isEnd())
        res.pb(curr);
    rep(i, 26)
    {
        if (node->links[i] != nullptr)
        {
            char ch = ('a' + i);
            curr.push_back(ch);
            get_prefix_matches(input, res, curr, node->get(ch));
        }
    }
}

void Trie::insertArray(const vector<string> &strings)
{
    for (const auto &s : strings)
        insert(s);
}
Node *Trie::getRoot()
{
    return this->root;
}
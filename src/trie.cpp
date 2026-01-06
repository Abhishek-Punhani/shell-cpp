#include "headers/commands.hpp"

Node::Node() : flag(false) {}
Node::~Node()
{
    for (auto &p : links)
        delete p.second;
}

bool Node::containsKey(char ch) const
{
    return links.find(ch) != links.end();
}

void Node::put(char ch, Node *node)
{
    links[ch] = node;
}

Node *Node::get(char ch) const
{
    auto it = links.find(ch);
    return it != links.end() ? it->second : nullptr;
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
Trie::~Trie() { delete root; }

void Trie::insert(const string &word)
{
    Node *node = root;
    for (unsigned char uch : word)
    {
        char ch = static_cast<char>(uch);
        if (!node->containsKey(ch))
            node->put(ch, new Node());
        node = node->get(ch);
        if (!node)
            return; // defensive
    }
    node->setEnd();
}

Node *Trie::getPrefixNode(const string &input)
{
    Node *node = root;
    for (unsigned char uch : input)
    {
        char ch = static_cast<char>(uch);
        if (!node->containsKey(ch))
            return nullptr;
        node = node->get(ch);
        if (!node)
            return nullptr;
    }
    return node;
}

void Trie::get_prefix_matches(const string &input, vector<string> &res, string curr, Node *node)
{
    if (!node)
        return;
    if (node->isEnd())
        res.push_back(curr);
    for (const auto &kv : node->links)
    {
        char ch = kv.first;
        string next = curr;
        next.push_back(ch);
        get_prefix_matches(input, res, next, kv.second);
    }
}

void Trie::insertArray(const vector<string> &strings)
{
    for (const auto &s : strings)
        insert(s);
}

Node *Trie::getRoot()
{
    return root;
}
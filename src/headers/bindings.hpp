#ifndef BINDINGS_HPP
#define BINDINGS_HPP

#include <bits/stdc++.h>
using namespace std;
void listen_bindings();
vector<string> autocomplete(string input);
vector<string> autocomplete_builtins(const string &prefix);
vector<string> autocomplete_executables(const string &prefix);

// key_bindings
int on_tab(int count, int key);

#endif
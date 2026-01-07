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
int previous_input(int count, int key);
int next_input(int count, int key);
void inc_history_idx();
void dec_history_idx();
string get_history_idx();
#endif
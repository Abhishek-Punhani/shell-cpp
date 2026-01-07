#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <bits/stdc++.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <cstdlib>
#include <dirent.h>

// custom headers
#include "bindings.hpp"

using namespace std;

// custom definitions
#define vi vector<int>
#define vvi vector<vi>
#define vs vector<string>
#define vb vector<bool>
#define pb push_back
#define pii pair<int, int>
#define sti set<int>
#define vpi vector<pii>
#define vst vector<sti>
#define rep(i, n) for (int i = 0; i < n; i++)
#define rep1(i, k, n) for (int i = k; i <= n; i++)
#define rep2(i, k, n) for (int i = k; i >= n; i--)
#define print(a)                          \
    rep(i, a.size()) cout << a[i] << ' '; \
    cout << endl;
#define printvpi(a) \
    rep(i, a.size()) cout << a[i].f << ' ' << a[i].s << endl;
#define printset(a)                                \
    for (auto it = a.begin(); it != a.end(); it++) \
        cout << *it << ' ';                        \
    cout << endl;
#define all(a) a.begin(), a.end()

// structs and classes

struct ExecutionResult
{
    std::string out;
    std::string err;
    int exit_code;
};

struct Node
{
    std::unordered_map<char, Node *> links;
    bool flag;

    Node();
    ~Node();

    bool containsKey(char ch) const;
    void put(char ch, Node *node);
    Node *get(char ch) const;
    void setEnd();
    bool isEnd() const;
};

class Trie
{
public:
    Trie();
    ~Trie();

    void insert(const std::string &word);
    Node *getPrefixNode(const std::string &input);
    void get_prefix_matches(const std::string &input,
                            std::vector<std::string> &res,
                            std::string curr,
                            Node *node);
    void insertArray(const std::vector<std::string> &strings);
    Node *getRoot();

private:
    Node *root;
};

// constants
extern const vector<string> shell_builtin_commands;
extern const vector<string> custom_commands;
ExecutionResult handleCommand(const std::vector<std::string> &tokens, bool redirect_stdout, bool redirect_stderr);

// command handlers
ExecutionResult handleEcho(const std::vector<std::string> &tokens);
ExecutionResult handleType(const std::vector<std::string> &tokens);
ExecutionResult handlePwd();
ExecutionResult handleCd(const std::vector<std::string> &tokens);

// helpers
bool isEmptyQuoted(const string &token);
string is_executable(const string &token);
string parse_qoutes(const vector<string> &tokens);
ExecutionResult execute_executables(const string &exec_path, const vector<string> &tokens);
void pushToken(string &token, vector<string> &tokens, bool &redirect_stdout, bool &redirect_stderr, bool &override_stdout, bool &override_stderr, ExecutionResult &prev_res,vector<vs> &pipelines);
void write_execution_result_to_file(const ExecutionResult &result, const std::string &path, bool is_err, bool override);
vector<string> get_path_executables();

// pipelines
void execute_pipelines(vector<vs> &pipeline);
#endif
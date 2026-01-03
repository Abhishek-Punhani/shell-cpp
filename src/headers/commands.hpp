#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <bits/stdc++.h>
using namespace std;

struct ExecutionResult
{
    std::string out;
    std::string err;
    int exit_code;
};

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
void pushToken(string &token, vector<string> &tokens, bool &redirect_stdout, bool &redirect_stderr, bool &override, ExecutionResult &prev_res);
void write_execution_result_to_file(const ExecutionResult &result, const std::string &path, bool is_err , bool override);
#endif
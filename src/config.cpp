#include "headers/commands.hpp"

Config::Config() : in_quotes(false),
                   in_double_quotes(false),
                   in_backslash(false),
                   redirect_stdout(false),
                   redirect_stderr(false),
                   override_stdout(true),
                   override_stderr(true)
{
}

void Config::reset()
{
    bool in_quotes = false;
    bool in_double_quotes = false;
    bool in_backslash = false;
    bool redirect_stdout = false;
    bool redirect_stderr = false;
    bool override_stdout = true;
    bool override_stderr = true;
}
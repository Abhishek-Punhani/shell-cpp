#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <vector>

void handleCommand(const std::vector<std::string>& tokens);

// command handlers
void handleEcho(const std::vector<std::string>& tokens);
void handleType(const std::vector<std::string>& tokens);    
void handlePwd();
void handleCd(const std::vector<std::string>& tokens);

#endif
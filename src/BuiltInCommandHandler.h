#ifndef BUILTIN_COMMAND_HANDLER_H
#define BUILTIN_COMMAND_HANDLER_H

#include <string>
#include <set>

class BuiltInCommandHandler {
public:
    // Returns true if the command was handled as a built-in.
    bool handleCommand(const std::string &input);

private:
    // Helper functions for each built-in command.
    std::set<std::string> builtins = {"exit", "echo", "type", "pwd", "cd"};
    void handleEcho(const std::string &input);
    void handleType(const std::string &command);
    void handleExit();
    void handlePwd();
    void handleCd(const std::string);
};

#endif // BUILTIN_COMMAND_HANDLER_H

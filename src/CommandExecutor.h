#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include <string>
#include <vector>

class CommandExecutor {
public:
    // Executes the external command given the command name, its full path, and its arguments.
    static void executeCommand(const std::string& fullPath,
                               const std::vector<std::string>& args);
};

#endif // COMMAND_EXECUTOR_H

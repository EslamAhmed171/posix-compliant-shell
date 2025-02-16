#ifndef COMMAND_RUNNER_H
#define COMMAND_RUNNER_H

#include <string>

class CommandRunner {
public:
    // Processes the input command by delegating to built-in or external handlers.
    void processCommand(const std::string &input);
};

#endif // COMMAND_RUNNER_H

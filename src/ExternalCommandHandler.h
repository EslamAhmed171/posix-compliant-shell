#ifndef EXTERNAL_COMMAND_HANDLER_H
#define EXTERNAL_COMMAND_HANDLER_H

#include <string>

class ExternalCommandHandler {
public:
    // Processes an external command input.
    void handleCommand(const std::string &input);
};

#endif // EXTERNAL_COMMAND_HANDLER_H

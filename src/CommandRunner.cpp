#include "CommandRunner.h"
#include "BuiltInCommandHandler.h"
#include "ExternalCommandHandler.h"
#include <iostream>

void CommandRunner::processCommand(const std::string &input) {
    BuiltInCommandHandler builtInHandler;
    // First, try handling as a built-in.
    if (builtInHandler.handleCommand(input)) {
        return;
    }

    // Otherwise, treat it as an external command.
    ExternalCommandHandler externalHandler;
    externalHandler.handleCommand(input);
}

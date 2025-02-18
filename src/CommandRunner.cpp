#include "CommandRunner.h"
#include "BuiltInCommandHandler.h"
#include "BuiltinCompletionHandler.h"
#include "ExternalCommandHandler.h"
#include "CommandUtils.h"

void CommandRunner::processCommand(std::string &input) {
    BuiltInCommandHandler builtInHandler;
    // First, try handling as a built-in.
    if (builtInHandler.handleCommand(input)) {
        return;
    }

    // Otherwise, treat it as an external command.
    ExternalCommandHandler externalHandler;
    externalHandler.handleCommand(input);
}

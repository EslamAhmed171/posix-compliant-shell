#include <iostream>
#include "BuiltinCompletionHandler.h"
#include "CommandUtils.h"

std::string BuiltinCompletionHandler::handleInCompleteCommand(const std::string &incompleteCommand) {
    if (incompleteCommand == "ech") {
        return "echo ";
    } else if (incompleteCommand == "exi") {
        return "exit ";
    } else if (incompleteCommand == "typ"){
        return "type ";
    }
    return incompleteCommand;
}

std::string BuiltinCompletionHandler::HandleExternalCommand(const std::string &incompleteExternalCommand) {
    std::string command = CommandUtils::handleIncompleteExternalCommand(incompleteExternalCommand);
    return command.empty() ? incompleteExternalCommand: command;
}

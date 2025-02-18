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

std::vector<std::string> BuiltinCompletionHandler::HandleExternalCommand(const std::string &incompleteExternalCommand) {
    return CommandUtils::handleIncompleteExternalCommand(incompleteExternalCommand);
}

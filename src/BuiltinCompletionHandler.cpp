#include <iostream>
#include "BuiltinCompletionHandler.h"

std::string BuiltinCompletionHandler::handleInCompleteCommand(const std::string &incompleteCommand) {
    if (incompleteCommand == "ech") {
        return "echo ";
    } else if (incompleteCommand == "exi") {
        return "exit ";
    } else if (incompleteCommand == "typ"){
        return "type ";
    };
}
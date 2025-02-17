#include "ExternalCommandHandler.h"
#include "CommandUtils.h"
#include "CommandExecutor.h"
#include <iostream>
#include <vector>

void ExternalCommandHandler::handleCommand(const std::string &input) {
    std::vector<std::string>  tokens;
    // Tokenize the input.
    if (input.front() == '\"' || input.front() == '\''){
        tokens = CommandUtils::tokenizeQuotedExec(input);
    } else {
        tokens = CommandUtils::tokenize(input);
    }
    if (tokens.empty()) return;

    // Locate the executable in the PATH.
    std::string fullPath = CommandUtils::getCommandDirectory(tokens[0], std::getenv("PATH"));
    if (fullPath.empty()) {
        std::cout << tokens[0] << ": command not found" << std::endl;
        return;
    }

    // The rest of the tokens are command-line arguments.
    CommandExecutor::executeCommand(fullPath, tokens);
}

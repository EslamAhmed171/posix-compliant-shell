#include "CommandRunner.h"
#include "RedirectionHandler.h"
#include "CommandUtils.h"
#include "BuiltInCommandHandler.h"
#include "ExternalCommandHandler.h"

void CommandRunner::processCommand(std::string& input) {
    CommandParser parser;
    auto result = parser.parse(input);

    if (result.args.empty()) {
        return;
    }

    std::string commandName = result.args[0];
    std::vector<std::string> args(result.args.begin() + 1, result.args.end());

    BuiltInCommandHandler builtInHandler;
    if (builtInHandler.isBuiltIn(commandName)) {
        RedirectionHandler rh;
        rh.apply(result.redirections);
        builtInHandler.handleCommand(commandName, args);
        rh.restore();
    } else {
        ExternalCommandHandler externalHandler;
        externalHandler.handleCommand(commandName, args, result.redirections);
    }
}
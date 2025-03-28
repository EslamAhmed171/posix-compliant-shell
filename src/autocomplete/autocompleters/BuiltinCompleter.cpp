#include "../../../include/autocomplete/autocompleters/BuiltinCompleter.h"


// BuiltinCompleter.cpp
std::vector<std::string> BuiltinCompleter::complete(const std::string& input) {
    std::vector<std::string> matches;
    const auto commands = CommandFactory::getCommandNames();

    for (const auto& cmd : commands) {
        if (cmd.length() > 1 && input.length() == cmd.length() - 1) {
            if (cmd.substr(0, cmd.length() - 1) == input) {
                matches.push_back(cmd);
            }
        }
    }

    return matches;
}

bool BuiltinCompleter::shouldTrigger(const std::string& input) const {
    return !input.empty() && input.find('/') == std::string::npos;
}
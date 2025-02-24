// CompletionSystem.cpp
#include "CompletionSystem.h"
#include "CommandUtils.h"
#include <algorithm>

// BuiltinCompleter implementation
std::vector<std::string> BuiltinCompleter::complete(const std::string& input) {
    static const std::vector<std::pair<std::string, std::string>> builtins = {
            {"ech", "echo"},
            {"exi", "exit"},
            {"typ", "type"},
    };

    std::vector<std::string> matches;
    for (const auto& [prefix, completion] : builtins) {
        if (prefix == input) {
            matches.push_back(completion);
        }
    }
    return matches;
}

// ExternalCommandCompleter implementation
std::vector<std::string> ExternalCommandCompleter::complete(const std::string& input) {
    return CommandUtils::findCommandsInPath(input);
}

// CompletionManager implementation
CompletionManager::CompletionManager() {}

std::vector<std::string> CompletionManager::getCompletions(const std::string& input) {
    auto builtinMatches = builtinCompleter.complete(input);
    if (!builtinMatches.empty()) return builtinMatches;

    return externalCompleter.complete(input);
}
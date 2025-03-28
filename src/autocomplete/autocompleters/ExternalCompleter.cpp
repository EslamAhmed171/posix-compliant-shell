#include "../../../include/autocomplete/autocompleters/ExternalCompleter.h"
#include "../../../include/utilities/PathUtils.h"

std::vector<std::string> ExternalCompleter::complete(const std::string& input) {
    return PathUtils::findCommandsInPath(input);
}

bool ExternalCompleter::shouldTrigger(const std::string& input) const {
    return !input.empty() && input.find('/') == std::string::npos;
}
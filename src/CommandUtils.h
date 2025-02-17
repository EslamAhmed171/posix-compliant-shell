#ifndef COMMAND_UTILS_H
#define COMMAND_UTILS_H

#include <string>
#include <vector>

namespace CommandUtils {

// Returns true if the command exists in the given directory.
    bool commandInDirectory(const std::string& command, const std::string& directory);

// Searches the PATH (colon-separated) for the command and returns the full path if found.
    std::string getCommandDirectory(const std::string& command, const char* path_env);

// Splits the input string into tokens based on whitespace.
    std::vector<std::string> tokenize(const std::string& input);
    std::vector<std::string> tokenizeQuotedExec(const std::string& input);

} // namespace CommandUtils

#endif // COMMAND_UTILS_H

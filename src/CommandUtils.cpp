#include "CommandUtils.h"
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

namespace CommandUtils {

    bool commandInDirectory(const std::string& command, const std::string& directory) {
        try {
            for (const auto& entry : fs::directory_iterator(directory)) {
                if (entry.path().filename() == command) {
                    return true;
                }
            }
        } catch (const fs::filesystem_error&) {
            return false;
        }
        return false;
    }

    std::string getCommandDirectory(const std::string& command, const char* path_env) {
        std::stringstream ss(path_env);
        std::string directory;
        // On Unix-like systems, PATH is colon-separated.
        while (std::getline(ss, directory, ':')) {
            if (commandInDirectory(command, directory)) {
                fs::path fullPath = fs::path(directory) / command;
                return fullPath.string();
            }
        }
        return "";
    }

    std::vector<std::string> tokenize(const std::string& input) {
        std::stringstream ss(input);
        std::vector<std::string> tokens;
        std::string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }

} // namespace CommandUtils

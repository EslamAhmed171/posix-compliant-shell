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
    std::string trimAndNormalizeSpaces(const std::string& str){
        std::stringstream ss;
        bool inSpaces = false;
        for (char c: str){
            if (std::isspace(c)){
                if (!inSpaces) {
                    ss << ' ';
                    inSpaces = true;
                }
            } else{
                ss << c;
                inSpaces = false;
            }
        }
        std::string result = ss.str();

        // Remove leading and trailing spaces
        size_t start = result.find_first_not_of(" \t\n\r\f\v");
        size_t end = result.find_last_not_of(" \t\n\r\f\v");

        return (start == std::string::npos) ? "" : result.substr(start, end - start + 1);
    }

} // namespace CommandUtils

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
    std::vector<std::string> tokenizeQuotedExec(const std::string& input){
        std::vector<std::string> tokens;
        bool insideQuotes = false;
        bool singleQuote = false;
        std::string token;
        for (char c : input) {
            if ((c == '\'' || c == '\"') && !insideQuotes) {
                insideQuotes = true;
                singleQuote = c == '\'';
                token.clear();  // Start a new file name
            }
            else if (((singleQuote && c == '\'') || (!singleQuote && c == '\"'))) {
                insideQuotes = false;
                tokens.push_back(token);  // Add the current file to the list
                token.clear();
            }
            else {
                if (!insideQuotes && c == ' ')
                    continue;
                token += c;
                }
        }
        tokens.push_back(token);
        return tokens;
    }

    bool containTab(const std::string& input){
        return int(input[3]) == 9;
    }

    std::string getIncompleteCommand(const std::string& input){
        std::string incompleteCommand;
        for (const char& c: input){
            if (int(c) == 9)
                break;
            incompleteCommand += c;
        }
        return incompleteCommand;
    }

    std::vector<std::string> handleIncompleteExternalCommand(const std::string& incompleteCommand){
        std::stringstream ss(getenv("PATH"));
        std::vector<std::string> commands;
        std::string directory;
        while (getline(ss, directory, ':')){
            if (fs::is_directory(directory)) {
                for (const auto &entry: fs::directory_iterator(directory)) {
                    if (entry.path().filename().string().compare(0, incompleteCommand.size(), incompleteCommand) == 0) {
                        commands.push_back(entry.path().filename().string());
                    }
                }
            }
        }
        return commands;
    }

    std::string getCommonPrefix(const std::vector<std::string>& commands){
        std::string common;
        for (int i = 0; i < commands[0].size(); i++){
            bool commonCh = true;
            for (const auto& command: commands){
                if (command.size() < i)
                    return common;
                commonCh &= command[i] == commands[0][i];
                if (!commonCh)
                    return common;
            }
            common += commands[0][i];
        }
        return common;
    }


} // namespace CommandUtils

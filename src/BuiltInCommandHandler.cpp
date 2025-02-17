#include "BuiltInCommandHandler.h"
#include "CommandUtils.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <limits.h>
#include <cstring>
#include <fstream>

bool BuiltInCommandHandler::handleCommand(const std::string &input) {
    const std::string echoPrefix = "echo ";
    const std::string typePrefix = "type ";
    const std::string exitCommand = "exit 0";
    const std::string pwdCommand = "pwd";
    const std::string cdPrefix = "cd ";
    const std::string catPrefix = "cat ";

    if (input.compare(0, echoPrefix.size(), echoPrefix) == 0) {
        std::string newInput = input.substr(echoPrefix.size());
        handleEcho(newInput);
        return true;
    }
    else if (input.compare(0, typePrefix.size(), typePrefix) == 0) {
        // Extract the command name after "type ".
        std::string command = input.substr(typePrefix.size());
        handleType(command);
        return true;
    }
    else if (input == exitCommand) {
        handleExit();  // Handle exit command
        return true;
    }
    else if (input == pwdCommand) {
        handlePwd();  // Handle pwd command
        return true;
    }
    else if (input.compare(0, cdPrefix.size(), cdPrefix) == 0){
        std::string path = input.substr(cdPrefix.size());
        handleCd(path);
        return true;
    }
    else if (input.compare(0, catPrefix.size(), catPrefix) == 0){
        handleCat(input.substr(catPrefix.size()));
        return true;
    }

    return false;
}

void BuiltInCommandHandler::handleEcho(std::string &input) {
    bool insideQuotes = false;
    bool singleQuote = false;
    bool isBeforeSpace = false;
    bool isBeforeBackslash = false;
    std::string str;
    for (const auto& c: input){
        if ((c == '\'' || c == '\"') && !insideQuotes && !isBeforeBackslash){
            std::cout << str;
            str.clear();
            insideQuotes = true;
            singleQuote = c == '\'';
        } else if (((singleQuote && c == '\'') || (!singleQuote && c == '\"')) && !isBeforeBackslash){
            std::cout << str;
            str.clear();
            insideQuotes = false;
        } else{
            if (c == ' ' && !insideQuotes && isBeforeSpace) {
                continue;
            }
            if ((!insideQuotes && c != '\\') ||
            (insideQuotes && singleQuote) ||
            (insideQuotes && c != '\\') ||
            (insideQuotes && isBeforeBackslash))
                str += c;
            isBeforeSpace = c == ' ';
            if (isBeforeBackslash && c == '\\') {
                isBeforeBackslash = false;
                continue;
            }
            isBeforeBackslash = c == '\\';
        }
    }
    std::cout << str << std::endl;
}

void BuiltInCommandHandler::handleType(const std::string &command) {
    if (builtins.find(command) != builtins.end()) {
        std::cout << command << " is a shell builtin" << std::endl;
    } else {
        std::string fullPath = CommandUtils::getCommandDirectory(command, std::getenv("PATH"));
        if (!fullPath.empty()) {
            std::cout << command << " is " << fullPath << std::endl;
        } else {
            std::cout << command << ": not found" << std::endl;
        }
    }
}

void BuiltInCommandHandler::handleExit() {
    exit(0);  // Exit the program
}

void BuiltInCommandHandler::handlePwd() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << cwd << std::endl;
    } else {
        perror("pwd failed");
    }
}

void BuiltInCommandHandler::handleCd(const std::string& path) {
    char* directory = const_cast<char*>(path.c_str());
    if (path == "~") {
        directory = getenv("HOME");
    }
    if (path.empty()) {
        std::cerr << "cd: Missing argument" << std::endl;
        return;
    }

    // Change the current working directory
    if (chdir(directory) == 0) {
        // Success: Do nothing or print a success message if you want.
    } else {
        // Error: Print the error message.
        std::cerr << "cd: " << path << ": " << strerror(errno) << std::endl;


    }
}
void BuiltInCommandHandler::handleCat(const std::string &input) {
    std::vector<std::string> filePaths;
    std::string currentFile;
    bool insideQuotes = false;
    bool singleQuote = false;

    // Parse the input string and extract file paths enclosed in single quotes
    for (char c : input) {
        if ((c == '\'' || c == '\"') && !insideQuotes) {
            insideQuotes = true;
            singleQuote = c == '\'';
            currentFile.clear();  // Start a new file name
        }
        else if (((singleQuote && c == '\'') || (!singleQuote && c == '\"'))) {
            insideQuotes = false;
            filePaths.push_back(currentFile);  // Add the current file to the list
        }
        else if (insideQuotes) {
            currentFile += c;  // Collect the file path inside quotes
        }
    }

    // If no files are found, return an error
    if (filePaths.empty()) {
        std::cerr << "cat: No files specified" << std::endl;
        return;
    }

    // Handle each file
    for (const auto &filePath : filePaths) {
        std::ifstream file(filePath);

        if (!file) {
            std::cerr << "cat: " << filePath << ": No such file or directory" << std::endl;
            continue;  // Skip to the next file
        }

        std::cout << file.rdbuf();  // Output the contents of the file
    }
}

#include "BuiltInCommandHandler.h"
#include "CommandUtils.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <limits.h>
#include <cstring>

bool BuiltInCommandHandler::handleCommand(const std::string &input) {
    const std::string echoPrefix = "echo ";
    const std::string typePrefix = "type ";
    const std::string exitCommand = "exit 0";
    const std::string pwdCommand = "pwd";
    const std::string cdPrefix = "cd ";

    if (input.compare(0, echoPrefix.size(), echoPrefix) == 0) {
        handleEcho(input);
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

    return false;
}

void BuiltInCommandHandler::handleEcho(const std::string &input) {
    std::cout << input.substr(5) << std::endl;
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
    if (path.empty()) {
        std::cerr << "cd: Missing argument" << std::endl;
        return;
    }

    // Change the current working directory
    if (chdir(path.c_str()) == 0) {
        // Success: Do nothing or print a success message if you want.
    } else {
        // Error: Print the error message.
        std::cerr << "cd: " << path << ": " << strerror(errno) << std::endl;
    }
}

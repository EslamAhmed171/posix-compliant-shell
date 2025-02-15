#include <iostream>
#include <filesystem>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <set>

namespace fs = std::filesystem;

bool commandInDirectory(const std::string& command, const std::string& directory) {
    try {
        for (const auto &entry: fs::directory_iterator(directory)) {
            if (entry.path().filename() == command) {
                return true;
            }
        }
    } catch (const fs::filesystem_error& error) {
        return false;
    }
    return false;
}

std::string getCommandDirectory(const std::string& command, const char* path_env) {
    std::stringstream stringStream(path_env);
    std::string directory;
    while (std::getline(stringStream, directory, ':')) {
        if (commandInDirectory(command, directory)) {
            fs::path fullPath = fs::path(directory) / command;
            return fullPath.string();
        }
    }
    return "";
}

std::vector<std::string> tokenize(const std::string& input) {
    std::stringstream string_stream(input);
    std::vector<std::string> tokens;
    std::string token;
    while (string_stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void executeCommand(const std::string& command, const std::string& fullPath, const std::vector<std::string>& args) {
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>(command.c_str()));
    for (const auto& arg : args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr); // Null-terminate the arguments

    pid_t pid = fork();
    if (pid == 0) {
        // Child process: Execute the command
        if (execv(fullPath.c_str(), argv.data()) == -1) {
            perror("execv failed");
        }
        exit(EXIT_FAILURE); // Exit if execv fails
    } else if (pid > 0) {
        // Parent process: Wait for the child process to complete
        int status;
        waitpid(pid, &status, 0);
    } else {
        // Fork failed
        perror("fork failed");
    }
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true) {
        std::cout << "$ ";

        std::string input;
        std::getline(std::cin, input);
        if (input == "exit 0")
            return 0;

        const int ECHO_LEN = 5;
        const int TYPE_LEN = 5;
        std::set<std::string> commands = {"exit", "echo", "type"};

        if (input.substr(0, ECHO_LEN) == "echo ")
            std::cout << input.substr(ECHO_LEN) << std::endl;
        else if (input.substr(0, TYPE_LEN) == "type ") {
            std::string command = input.substr(TYPE_LEN);
            if (commands.find(command) != commands.end()) {
                std::cout << command << " is a shell builtin" << std::endl;
            } else if (!getCommandDirectory(command, std::getenv("PATH")).empty()) {
                std::cout << command << " is " << getCommandDirectory(command, std::getenv("PATH")) << std::endl;
            } else {
                std::cout << command << ": not found" << std::endl;
            }
        } else {
            std::vector<std::string> tokens = tokenize(input);
            std::string fullPath = getCommandDirectory(tokens[0], std::getenv("PATH"));

            if (fullPath.empty()) {
                std::cout << tokens[0] << ": command not found" << std::endl;
                continue;
            }

            executeCommand(tokens[0], fullPath, {tokens.begin() + 1, tokens.end()});
        }
    }
}

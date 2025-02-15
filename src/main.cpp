#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <set>
namespace fs = std::filesystem;


bool commandInDirectory(const std::string& command, const std::string& directory){
    try {
        for (const auto &entry: fs::directory_iterator(directory)) {
            if (entry.path().filename() == command) {
                return true;
            }
        }
    } catch(const fs::filesystem_error& error) {
        std:: cout << error.what() << std::endl;
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

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while(true) {
        std::cout << "$ ";

        std::string input;
        std::getline(std::cin, input);
        if (input == "exit 0")
            return 0;

        // check the echo command
        const int ECHO_LEN = 5;
        const int TYPE_LEN = 5;
        std::set<std::string> commands = {"exit", "echo", "type"};

        if (input.substr(0,  ECHO_LEN) == "echo ")
            std::cout << input.substr(ECHO_LEN) << std::endl;
        else if (input.substr(0, TYPE_LEN) == "type ") {
            std::string command = input.substr(TYPE_LEN);
            if (commands.find(command) != commands.end()){
                std::cout << command << " is a shell builtin" << std::endl;
            }
            else if (!getCommandDirectory(command, std::getenv("PATH")).empty()){
                std::cout << command << " is " << getCommandDirectory(command, std::getenv("PATH")) << std::endl;
            } else{
                std::cout << command << ": not found" << std::endl;
            }
        }
        else
            std::cout << input << ": command not found" << std::endl;
    }
}

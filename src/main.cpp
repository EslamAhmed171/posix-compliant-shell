#include <iostream>
#include <set>

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
            } else{
                std::cout << command << ": not found" << std::endl;
            }
        }
        else
            std::cout << input << ": command not found" << std::endl;
    }
}

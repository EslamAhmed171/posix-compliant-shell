#include <iostream>

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
        if (input.substr(0,  5) == "echo ")
            std::cout << input.substr(ECHO_LEN) << std::endl;
        else
            std::cout << input << ": command not found" << std::endl;
    }
}

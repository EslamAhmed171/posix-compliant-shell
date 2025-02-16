#include "Shell.h"
#include "CommandRunner.h"
#include <iostream>
#include <string>

void Shell::run() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    CommandRunner runner;
    std::string input;

    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, input);
        runner.processCommand(input);
    }
}

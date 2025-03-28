#include "../../../include/shell/output/ConsoleOutputStrategy.h"
#include <iostream>

void ConsoleOutputStrategy::displayPrompt(const std::string& prompt) {
    std::cout << prompt << std::flush;
}

void ConsoleOutputStrategy::displayBuffer(const std::string& buffer) {
    std::cout << buffer << std::flush;
}

void ConsoleOutputStrategy::displayChar(char c) {
    std::cout << c << std::flush;
}

void ConsoleOutputStrategy::displayCompletions(const std::vector<std::string>& completions) {
    for (const auto& completion : completions) {
        std::cout << completion << "  ";
    }
    std::cout << std::endl;
}

void ConsoleOutputStrategy::clearLine() {
    std::cout << "\r\033[K" << std::flush;
}

void ConsoleOutputStrategy::backspace() {
    std::cout << "\b \b" << std::flush;
}

void ConsoleOutputStrategy::newLine() {
    std::cout << std::endl;
}

void ConsoleOutputStrategy::beep() {
    std::cout << '\a' << std::flush;
}

void ConsoleOutputStrategy::displayError(const std::string& error) {
    std::cerr << "\nError: " << error << std::endl;
}

void ConsoleOutputStrategy::displayMessage(const std::string& message) {
    std::cout << message << std::endl;
}
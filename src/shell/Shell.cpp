#include "../../include/shell/Shell.h"
#include "../../include/shell/output/OutputStrategy.h"
#include "../../include/shell/input/InputState.h"
#include "../../include/shell/output/ConsoleOutputStrategy.h"

#include <iostream>
#include <unistd.h>

Shell::Shell() :
        strategies_(cmd_factory_),
        dispatcher_(strategies_, redirector_),
        parser_(std::make_unique<TokenizerFactory>()),
        output_strategy_(std::make_unique<ConsoleOutputStrategy>()) {
    input_handler_ = std::make_unique<InputHandler>(*this, output_strategy_.get());
}

Shell::~Shell() = default;  // Now the compiler knows how to destroy the unique_ptr!

void Shell::run() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    enableRawMode();
    displayPrompt();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1) {
        input_handler_->processInput(c);
    }

    disableRawMode();
}

void Shell::executeCommand(const std::string& command) {
    try {
        ParseResult result = parser_.parse(command);
        dispatcher_.dispatch(result);
    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << '\n';
    }
}

void Shell::displayPrompt() const {
    std::cout << "$ ";
    std::cout.flush();
}

void Shell::enableRawMode() {
    struct termios term{};
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void Shell::disableRawMode() {
    struct termios term{};
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

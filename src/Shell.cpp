#include "Shell.h"
#include "CommandRunner.h"
#include "BuiltinCompletionHandler.h"
#include "CommandUtils.h"
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

void Shell::run() {
    enableRawMode();
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string input;
    char c;
    std::cout << "$ " << std::flush;

    while (true) {
        ssize_t n = read(STDIN_FILENO, &c, 1);
        if (n <= 0) {
            break;
        }

        // When Enter is pressed, process the command
        if (c == '\r' || c == '\n') {
            std::cout << std::endl;
            CommandRunner runner;
            runner.processCommand(input);
            input.clear();
            std::cout << "$ " << std::flush;
        }
            // Handle backspace (ASCII 127, sometimes '\b')
        else if (c == 127 || c == '\b') {
            if (!input.empty()) {
                input.pop_back();
                // Move the cursor back, erase the character, and move back again
                std::cout << "\b \b" << std::flush;
            }
        }
        else if (c == '\t') {
            std::string incompleteCommand = CommandUtils::getIncompleteCommand(input);
            BuiltinCompletionHandler completionHandler;
            std::string completedCommand = completionHandler.handleInCompleteCommand(incompleteCommand);
            if (input != completedCommand) {
                std::cout << "\r\033[K" << "$ " << completedCommand << std::flush;
            }
            else{
                completedCommand = completionHandler.HandleExternalCommand(incompleteCommand);
                if (input != completedCommand){
                    std::cout << "\r\033[K" << "$ " << completedCommand << std::flush;
                }
                else{
                    std::cout << '\a' << std::flush;
                }
            }
            input = completedCommand;
        }
        else {
            input.push_back(c);
            std::cout << c << std::flush;
        }
    }


}

void Shell::enableRawMode() {
    struct termios term{};
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

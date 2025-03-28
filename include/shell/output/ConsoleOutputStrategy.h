#ifndef CONSOLE_OUTPUT_STRATEGY_H
#define CONSOLE_OUTPUT_STRATEGY_H

#include "OutputStrategy.h"

class ConsoleOutputStrategy : public OutputStrategy {
public:
    void displayPrompt(const std::string& prompt) override;
    void displayBuffer(const std::string& buffer) override;
    void displayChar(char c) override;
    void displayCompletions(const std::vector<std::string>& completions) override;

    void clearLine() override;
    void backspace() override;
    void newLine() override;
    void beep() override;

    void displayError(const std::string& error) override;
    void displayMessage(const std::string& message) override;
};

#endif // CONSOLE_OUTPUT_STRATEGY_H
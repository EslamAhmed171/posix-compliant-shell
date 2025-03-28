#ifndef OUTPUT_STRATEGY_H
#define OUTPUT_STRATEGY_H

#include <string>
#include <vector>

class OutputStrategy {
public:
    virtual ~OutputStrategy() = default;

    // Core output operations
    virtual void displayPrompt(const std::string& prompt) = 0;
    virtual void displayBuffer(const std::string& buffer) = 0;
    virtual void displayChar(char c) = 0;
    virtual void displayCompletions(const std::vector<std::string>& completions) = 0;

    // Cursor and display manipulation
    virtual void clearLine() = 0;
    virtual void backspace() = 0;
    virtual void newLine() = 0;
    virtual void beep() = 0;

    // Error and status display
    virtual void displayError(const std::string& error) = 0;
    virtual void displayMessage(const std::string& message) = 0;
};

#endif // OUTPUT_STRATEGY_H
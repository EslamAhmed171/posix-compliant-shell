#ifndef SHELL_H
#define SHELL_H

#include "../execution/CommandDispatcher.h"
#include "../parsing/CommandParser.h"
#include "../commands/CommandFactory.h"
#include "../autocomplete/CompletionManager.h"
#include <memory>
#include <termios.h>

class OutputStrategy;  // Forward declaration
class InputHandler;    // Forward declaration

class Shell {
public:
    Shell();

    // Prevent copying and moving
    Shell(const Shell&) = delete;
    Shell& operator=(const Shell&) = delete;
    Shell(Shell&&) = delete;
    Shell& operator=(Shell&&) = delete;

    ~Shell();  // Add this destructor here!

    void run();
    void executeCommand(const std::string& command);
    void displayPrompt() const;

    void enableRawMode();
    void disableRawMode();

    const CompletionManager& completer() const { return completer_; }

private:
    CommandFactory cmd_factory_;
    StrategyHolder strategies_;
    RedirectionHandler redirector_;
    CommandDispatcher dispatcher_;
    CommandParser parser_;
    CompletionManager completer_;

    std::unique_ptr<OutputStrategy> output_strategy_;
    std::unique_ptr<InputHandler> input_handler_;
};

#endif

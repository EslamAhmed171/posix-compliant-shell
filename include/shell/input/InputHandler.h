#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <memory>
#include <string>

class Shell;
class InputState;
class InputAction;
class OutputStrategy;
enum class ActionResult;

class InputHandler {
public:
    InputHandler(Shell& shell, OutputStrategy* output_strategy);

    // Input processing
    void processInput(char c);

    // State management
    void transition(std::unique_ptr<InputState> new_state);
    const InputState* currentState() const;

    // Action execution
    ActionResult executeAction(std::unique_ptr<InputAction> action);

    // Buffer management
    std::string& buffer() noexcept;
    void clearBuffer() noexcept;

    // Access to related components
    Shell& shell() noexcept;
    OutputStrategy& output() noexcept;

private:
    std::unique_ptr<InputState> state_;
    std::string buffer_;
    Shell& shell_;
    OutputStrategy* output_strategy_; // Non-owning pointer
};

#endif // INPUT_HANDLER_H
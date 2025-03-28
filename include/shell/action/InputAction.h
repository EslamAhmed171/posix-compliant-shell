#ifndef INPUT_ACTION_H
#define INPUT_ACTION_H

class InputHandler;

enum class ActionResult {
    DEFAULT,
    BEEP_OCCURRED
};

// Abstract base class for all input actions
class InputAction {
public:
    virtual ~InputAction() = default;

    // Execute the action using the input handler
    virtual ActionResult execute(InputHandler& handler) = 0;

    // Check if the action can be executed (optional)
    virtual bool canExecute(const InputHandler& handler) const { return true; }
};

#endif // INPUT_ACTION_H
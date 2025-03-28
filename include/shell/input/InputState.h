#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include "InputHandler.h"

// Abstract interface for input states
class InputState {
public:
    virtual ~InputState() = default;

    // Handle an input character in the current state
    virtual void handle(char c, InputHandler& handler) = 0;

    // Optional methods for state entry/exit
    virtual void onEnter(InputHandler& handler) {}
    virtual void onExit(InputHandler& handler) {}
};

#endif // INPUT_STATE_H
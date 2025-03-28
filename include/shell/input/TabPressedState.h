#ifndef TAB_PRESSED_STATE_H
#define TAB_PRESSED_STATE_H

#include "InputState.h"

// State for handling second tab press for command completion
class TabPressedState : public InputState {
public:
    void handle(char c, InputHandler& handler) override;
};

#endif // TAB_PRESSED_STATE_H
#ifndef BACKSPACE_ACTION_H
#define BACKSPACE_ACTION_H

#include "InputAction.h"

class BackspaceAction : public InputAction {
public:
    ActionResult execute(InputHandler& handler) override;
};

#endif // BACKSPACE_ACTION_H
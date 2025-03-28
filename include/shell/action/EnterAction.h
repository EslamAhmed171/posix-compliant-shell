#ifndef ENTER_ACTION_H
#define ENTER_ACTION_H

#include "InputAction.h"

class EnterAction : public InputAction {
public:
    ActionResult execute(InputHandler& handler) override;
};

#endif // ENTER_ACTION_H
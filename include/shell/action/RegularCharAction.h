#ifndef REGULAR_CHAR_ACTION_H
#define REGULAR_CHAR_ACTION_H

#include "InputAction.h"

class RegularCharAction : public InputAction {
public:
    explicit RegularCharAction(char c);
    ActionResult execute(InputHandler& handler) override;

private:
    char c_;
};

#endif // REGULAR_CHAR_ACTION_H
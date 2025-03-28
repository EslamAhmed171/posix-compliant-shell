#ifndef TAB_ACTION_H
#define TAB_ACTION_H

#include "InputAction.h"

class TabAction : public InputAction {
public:
    explicit TabAction(bool isSecondTab = false);

    ActionResult  execute(InputHandler& handler) override;

private:
    bool isSecondTab_;
};

#endif // TAB_ACTION_H
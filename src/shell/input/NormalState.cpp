#include "../../../include/shell/input/NormalState.h"
#include "../../../include/shell/input/TabPressedState.h"
#include "../../../include/shell/action/ActionFactory.h"
#include "../../../include/shell/action/InputAction.h"
#include<iostream>

void NormalState::handle(char c, InputHandler& handler) {
    auto action = ActionFactory::createAction(c, handler);

    // Special handling for tab key to manage state transition
    if (c == '\t') {
        // Execute the action (which will handle first tab press)
        ActionResult result = handler.executeAction(std::move(action));

        // Only transition to TabPressedState if beep occurred
        if (result == ActionResult::BEEP_OCCURRED) {
            handler.transition(std::make_unique<TabPressedState>());
        }
    } else {
        // For all other actions, just execute them in the normal state
        handler.executeAction(std::move(action));
    }
}
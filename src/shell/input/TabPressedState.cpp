#include "../../../include/shell/input/TabPressedState.h"
#include "../../../include/shell/action/ActionFactory.h"
#include "../../../include/shell/input/NormalState.h"
#include "../../../include/shell/action/InputAction.h"

void TabPressedState::handle(char c, InputHandler& handler) {
    if (c == '\t') {
        // This is a second tab press, so create a TabAction with isSecondTab=true
        auto action = ActionFactory::createAction(c, handler);
        handler.executeAction(std::move(action));
    }

    // Always transition back to NormalState after handling
    handler.transition(std::make_unique<NormalState>());

    // If it wasn't a tab, we need to process the character in the normal state
    if (c != '\t') {
        handler.processInput(c);
    }
}
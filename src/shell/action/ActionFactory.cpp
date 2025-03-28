#include "../../../include/shell/action/ActionFactory.h"
#include "../../../include/shell/action/EnterAction.h"
#include "../../../include/shell/action/BackspaceAction.h"
#include "../../../include/shell/action/TabAction.h"
#include "../../../include/shell/action/RegularCharAction.h"
#include "../../../include/shell/input/TabPressedState.h"


std::unique_ptr<InputAction> ActionFactory::createAction(char c, const InputHandler& handler) {
    // Special control characters
    if (c == '\n' || c == '\r') {
        return std::make_unique<EnterAction>();
    } else if (c == 127 || c == '\b') {
        return std::make_unique<BackspaceAction>();
    } else if (c == '\t') {
        // Check if we're in the tab-pressed state
        bool isSecondTab = dynamic_cast<const TabPressedState*>(handler.currentState()) != nullptr;
        return std::make_unique<TabAction>(isSecondTab);
    }
    return std::make_unique<RegularCharAction>(c);
}
#include "../../../include/shell/action/BackspaceAction.h"
#include "../../../include/shell/input/InputHandler.h"
#include "../../../include/shell/output/OutputStrategy.h"

ActionResult BackspaceAction::execute(InputHandler& handler) {
    if (!handler.buffer().empty()) {
        handler.buffer().pop_back();
        handler.output().backspace();
    }
    return ActionResult::DEFAULT;
}
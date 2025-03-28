#include "../../../include/shell/action/RegularCharAction.h"
#include "../../../include/shell/input/InputHandler.h"
#include "../../../include/shell/output/OutputStrategy.h"


RegularCharAction::RegularCharAction(char c) : c_(c) {}

ActionResult RegularCharAction::execute(InputHandler& handler) {
    handler.buffer() += c_;
    handler.output().displayChar(c_);
    return ActionResult::DEFAULT;

}
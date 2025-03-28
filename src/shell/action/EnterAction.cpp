#include "../../../include/shell/action/EnterAction.h"
#include "../../../include/shell/input/InputHandler.h"
#include "../../../include/shell/Shell.h"
#include "../../../include/shell/output/OutputStrategy.h"


ActionResult EnterAction::execute(InputHandler& handler) {
    handler.output().newLine();
    handler.shell().executeCommand(handler.buffer());
    handler.clearBuffer();
    handler.shell().displayPrompt();
    return ActionResult::DEFAULT;

}

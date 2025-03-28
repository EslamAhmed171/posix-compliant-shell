#include "../../../include/shell/action/TabAction.h"
#include "../../../include/shell/input/NormalState.h"
#include "../../../include/shell/Shell.h"
#include "../../../include/shell/output/OutputStrategy.h"
#include "../../../include/utilities/StringUtils.h"

TabAction::TabAction(bool isSecondTab) : isSecondTab_(isSecondTab) {}

ActionResult TabAction::execute(InputHandler& handler) {
    const auto candidates = handler.shell().completer().getCompletions(handler.buffer());

    if (candidates.empty()) {
        handler.output().beep();
        return ActionResult::BEEP_OCCURRED;
    }

    if (candidates.size() == 1) {
        handler.buffer() = candidates.front() + " ";
        handler.output().clearLine();
        handler.output().displayPrompt("$ ");
        handler.output().displayBuffer(handler.buffer());
        return ActionResult::DEFAULT;
    } else {
        const std::string commonPrefix = StringUtils::commonPrefix(candidates);
        if (!commonPrefix.empty() && handler.buffer().size() < commonPrefix.size()) {
            handler.buffer() = commonPrefix;
            handler.output().clearLine();
            handler.output().displayPrompt("$ ");
            handler.output().displayBuffer(handler.buffer());
            return ActionResult::DEFAULT;
        } else if (isSecondTab_) {
            handler.output().newLine();
            handler.output().displayCompletions(candidates);
            handler.output().displayPrompt("$ ");
            handler.output().displayBuffer(handler.buffer());
            return ActionResult::DEFAULT;
        } else {
            handler.output().beep();
            return ActionResult::BEEP_OCCURRED;
        }
    }
}

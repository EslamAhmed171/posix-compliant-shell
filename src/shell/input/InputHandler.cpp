#include "../../../include/shell/input/InputHandler.h"
#include "../../../include/shell/Shell.h"
#include "../../../include/shell/input/InputState.h"
#include "../../../include/shell/action/InputAction.h"
#include "../../../include/shell/input/NormalState.h"

InputHandler::InputHandler(Shell& shell, OutputStrategy* output_strategy)
        : shell_(shell),
          output_strategy_(output_strategy),
          state_(std::make_unique<NormalState>()) {
}

void InputHandler::processInput(char c) {
    state_->handle(c, *this);
}

void InputHandler::transition(std::unique_ptr<InputState> new_state) {
    if (state_) {
        state_->onExit(*this);
    }
    state_ = std::move(new_state);
    if (state_) {
        state_->onEnter(*this);
    }
}

const InputState* InputHandler::currentState() const {
    return state_.get();
}

ActionResult InputHandler::executeAction(std::unique_ptr<InputAction> action) {
    if (action && action->canExecute(*this)) {
        return action->execute(*this);
    }
    return ActionResult::DEFAULT;
}

std::string& InputHandler::buffer() noexcept {
    return buffer_;
}

void InputHandler::clearBuffer() noexcept {
    buffer_.clear();
}

Shell& InputHandler::shell() noexcept {
    return shell_;
}

OutputStrategy& InputHandler::output() noexcept {
    return *output_strategy_;
}
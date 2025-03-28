#include "../../include/execution/StrategyHolder.h"

StrategyHolder::StrategyHolder(CommandFactory& cmd_factory)
        : builtin_strategy_(cmd_factory),
          external_strategy_(),
          cmd_factory_(cmd_factory) {}

ExecutionStrategy& StrategyHolder::selectStrategy(const std::string& command_name) noexcept {
    return cmd_factory_.exists(command_name) ?
           static_cast<ExecutionStrategy&>(builtin_strategy_) :
           external_strategy_;
}
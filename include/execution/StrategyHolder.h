#ifndef STRATEGY_REGISTRY_H
#define STRATEGY_REGISTRY_H
#pragma once
#include "ExecutionStrategy.h"
#include "./executions/ExternalStrategy.h"
#include "./executions/BuiltInStrategy.h"
#include "../commands/CommandFactory.h"

class StrategyHolder {
public:
    explicit StrategyHolder(CommandFactory& cmd_factory);

    ExecutionStrategy& selectStrategy(const std::string& command_name) noexcept;

private:
    BuiltInStrategy builtin_strategy_;
    ExternalStrategy external_strategy_;
    CommandFactory& cmd_factory_;
};
#endif //STRATEGY_REGISTRY_H

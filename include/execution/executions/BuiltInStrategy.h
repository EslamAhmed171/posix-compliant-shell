//
// Created by Eslam Ahmed on 2/25/2025.
//

#ifndef BUILTIN_STRATEGY_H
#define BUILTIN_STRATEGY_H
#pragma once
#include "../ExecutionStrategy.h"
#include "../../commands/CommandFactory.h"

class BuiltInStrategy : public ExecutionStrategy {
public:
    explicit BuiltInStrategy(CommandFactory& factory);
    int execute(const std::vector<std::string>& args) override;

private:
    CommandFactory& factory_;
};
#endif //BUILTIN_STRATEGY_H

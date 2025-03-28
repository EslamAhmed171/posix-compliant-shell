#ifndef EXECUTION_STRATEGY_H
#define EXECUTION_STRATEGY_H
#pragma once
#include <vector>
#include <string>

class ExecutionStrategy {
public:
    virtual ~ExecutionStrategy() = default;
    virtual int execute(const std::vector<std::string>& args) = 0;
};
#endif //EXECUTION_STRATEGY_H

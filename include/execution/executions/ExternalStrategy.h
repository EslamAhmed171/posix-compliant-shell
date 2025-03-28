//
// Created by Eslam Ahmed on 2/25/2025.
//

#ifndef EXTERNAL_STRATEGY_H
#define EXTERNAL_STRATEGY_H
#pragma once
#include "../ExecutionStrategy.h"

class ExternalStrategy : public ExecutionStrategy {
public:
    int execute(const std::vector<std::string>& args) override;

private:
    int forkAndExecute(const std::vector<std::string>& args) const;
    void setupChildProcess(const std::vector<std::string>& args) const;
    int monitorChildProcess(pid_t pid) const;
};
#endif //EXTERNAL_STRATEGY_H

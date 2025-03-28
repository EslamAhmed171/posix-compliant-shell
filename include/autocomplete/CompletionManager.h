#ifndef COMPLETION_MANAGER_H
#define COMPLETION_MANAGER_H
#pragma once
#include "Completer.h"
#include <memory>
#include <vector>

class CompletionManager {
public:
    CompletionManager();
    void registerCompleter(std::unique_ptr<Completer> completer);
    std::vector<std::string> getCompletions(const std::string& input) const;

private:
    std::vector<std::unique_ptr<Completer>> completers_;
};

#endif //COMPLETION_MANAGER_H

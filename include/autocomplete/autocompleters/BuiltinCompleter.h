#ifndef BUILTIN_COMPLETER_H
#define BUILTIN_COMPLETER_H

#pragma once
#include "../Completer.h"
#include "../../commands/CommandFactory.h"

class BuiltinCompleter : public Completer {
public:
    std::vector<std::string> complete(const std::string& input) override;
    bool shouldTrigger(const std::string& input) const override;
};

#endif //BUILTIN_COMPLETER_H

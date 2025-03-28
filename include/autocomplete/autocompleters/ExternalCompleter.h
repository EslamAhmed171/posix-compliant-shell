//
// Created by Eslam Ahmed on 2/25/2025.
//

#ifndef EXTERNAL_COMPLETER_H
#define EXTERNAL_COMPLETER_H

#pragma once
#include "../Completer.h"

class ExternalCompleter : public Completer {
public:
    std::vector<std::string> complete(const std::string& input) override;
    bool shouldTrigger(const std::string& input) const override;
};

#endif //EXTERNAL_COMPLETER_H

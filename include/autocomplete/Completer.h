//
// Created by Eslam Ahmed on 2/25/2025.
//

#ifndef COMPLETER_H
#define COMPLETER_H
#pragma once
#include <vector>
#include <string>

class Completer {
public:
    virtual ~Completer() = default;
    virtual std::vector<std::string> complete(const std::string& input) = 0;
    virtual bool shouldTrigger(const std::string& input) const = 0;
};

#endif //COMPLETER_H

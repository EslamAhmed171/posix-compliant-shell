#ifndef I_COMMAND_H
#define I_COMMAND_H

#pragma once
#include <iostream>
#include <vector>
#include <memory>

class ICommand {
public:
    virtual ~ICommand() = default;

    virtual void execute(const std::vector<std::string>& args) = 0;

    virtual std::string_view name() const noexcept = 0;

    virtual std::unique_ptr<ICommand> clone() const = 0;
};
#endif //I_COMMAND_H

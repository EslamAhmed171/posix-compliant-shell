#ifndef PWD_COMMAND_H
#define PWD_COMMAND_H

#include "../ICommand.h"
class PwdCommand final : public ICommand {
public:
    void execute(const std::vector<std::string>& args) override;
    std::string_view name() const noexcept override { return "pwd"; }
    std::unique_ptr<ICommand> clone() const override;
};

#endif // PWD_COMMAND_H

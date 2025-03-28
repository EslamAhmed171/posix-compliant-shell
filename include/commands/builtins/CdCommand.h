#ifndef CD_COMMAND_H
#define CD_COMMAND_H

#include "../ICommand.h"
class CdCommand final : public ICommand {
public:
    void execute(const std::vector<std::string>& args) override;
    std::string_view name() const noexcept override { return "cd"; }
    std::unique_ptr<ICommand> clone() const override;
};

#endif //CD_COMMAND_H

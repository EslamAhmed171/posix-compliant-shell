#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H

#include "../ICommand.h"
class ExitCommand final : public ICommand {
public:
    void execute(const std::vector<std::string>& args) override;
    std::string_view name() const noexcept override { return "exit"; }
    std::unique_ptr<ICommand> clone() const override;
};

#endif //EXIT_COMMAND_H

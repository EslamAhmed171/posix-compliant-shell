#ifndef ECHO_COMMAND_H
#define ECHO_COMMAND_H

#include "../ICommand.h"
class EchoCommand final : public ICommand {
public:
    void execute(const std::vector<std::string>& args) override;
    std::string_view name() const noexcept override { return "echo"; }
    std::unique_ptr<ICommand> clone() const override;
};

#endif //ECHO_COMMAND_H

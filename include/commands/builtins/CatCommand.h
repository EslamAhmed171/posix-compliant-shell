#ifndef CAT_COMMAND_H
#define CAT_COMMAND_H

#include "../ICommand.h"
class CatCommand final : public ICommand {
public:
    void execute(const std::vector<std::string>& args) override;
    std::string_view name() const noexcept override { return "cat"; }
    std::unique_ptr<ICommand> clone() const override;
};

#endif // CAT_COMMAND_H

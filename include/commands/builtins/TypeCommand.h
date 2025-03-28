#ifndef TYPE_COMMAND_H
#define TYPE_COMMAND_H

#include "../ICommand.h"
#include "../CommandFactory.h"
class TypeCommand final : public ICommand {
public:
    explicit TypeCommand(const CommandFactory& factory);
    void execute(const std::vector<std::string>& args) override;
    std::string_view name() const noexcept override { return "type"; }
    std::unique_ptr<ICommand> clone() const override;
private:
    const CommandFactory& factory_;
};

#endif // TYPE_COMMAND_H

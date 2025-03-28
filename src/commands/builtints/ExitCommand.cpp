#include "../../../include/commands//builtins/ExitCommand.h"

void ExitCommand::execute(const std::vector<std::string>& args) {
    exit(args.empty() ? 0 : std::atoi(args[0].c_str())); // Basic exit code handling
}

std::unique_ptr<ICommand> ExitCommand::clone() const {
    return std::make_unique<ExitCommand>(*this);
}
#include "../../../include/commands/builtins/EchoCommand.h"

void EchoCommand::execute(const std::vector<std::string>& args) {
    for (size_t i = 0; i < args.size(); ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << args[i];
    }
    std::cout << std::endl;
}

std::unique_ptr<ICommand> EchoCommand::clone() const {
    return std::make_unique<EchoCommand>(*this);
}

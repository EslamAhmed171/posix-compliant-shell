#include "../../include/commands/CommandFactory.h"
#include "../../include/commands/builtins/EchoCommand.h"
#include "../../include/commands/builtins/TypeCommand.h"
#include "../../include/commands/builtins/CdCommand.h"
#include "../../include/commands/builtins/ExitCommand.h"
#include "../../include/commands/builtins/PwdCommand.h"
#include "../../include/commands/builtins/CatCommand.h"

CommandFactory::CommandFactory() {
    registerBuiltInCommands();
}

void CommandFactory::registerBuiltInCommands() {
    // Basic commands
    registerCommand("echo", [] { return std::make_unique<EchoCommand>(); });
    registerCommand("type", [this] { return std::make_unique<TypeCommand>(*this); });
    registerCommand("cd", [] { return std::make_unique<CdCommand>(); });
    registerCommand("exit", [] { return std::make_unique<ExitCommand>(); });
    registerCommand("pwd", [] { return std::make_unique<PwdCommand>(); });
    registerCommand("cat", [] { return std::make_unique<CatCommand>(); });
}


void CommandFactory::registerCommand(std::string_view name,
                                     std::function<std::unique_ptr<ICommand>()> creator) {
    registry_.emplace(std::string(name), std::move(creator));
}

std::unique_ptr<ICommand> CommandFactory::create(std::string_view command_name) const {

    if (auto it = registry_.find(std::string(command_name)); it != registry_.end()) {
        return it->second();
    }
    return nullptr;
}

bool CommandFactory::exists(std::string_view command_name) const noexcept {
    return registry_.contains(std::string(command_name));
}

std::vector<std::string> CommandFactory::getCommandNames() {
    static const std::vector<std::string> commands = {
            "echo", "exit", "type", "cd", "pwd", "cat"
    };
    return commands;
}
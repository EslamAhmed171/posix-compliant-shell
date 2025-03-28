#include "../../../include/commands/builtins/CdCommand.h"

void CdCommand::execute(const std::vector<std::string>& args) {
    if (args.size() > 1) {
        std::cerr << "cd: too many arguments\n";
        return;
    }

    const char* path = args.empty() || args[0] == "~" ? std::getenv("HOME") : args[0].c_str();
    if (!path) {
        std::cerr << "cd: HOME not set\n";
        return;
    }

    if (chdir(path) != 0) {
        std::string err = "cd: " + args[0];
        perror(err.c_str());
    }
}

std::unique_ptr<ICommand> CdCommand::clone() const {
    return std::make_unique<CdCommand>(*this);
}
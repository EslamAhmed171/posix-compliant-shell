#include "../../../include/commands/builtins/PwdCommand.h"

void PwdCommand::execute(const std::vector<std::string>& args) {
    if (!args.empty()) {
        std::cerr << "pwd: too many arguments\n";
        return;
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))) std::cout << cwd << '\n';
    else perror("pwd");
}

std::unique_ptr<ICommand> PwdCommand::clone() const {
    return std::make_unique<PwdCommand>(*this);
}
#include "../../../include/commands/builtins/TypeCommand.h"
#include "../../../include/utilities/PathUtils.h"

TypeCommand::TypeCommand(const CommandFactory& factory)
        : factory_(factory) {}  // Store reference

void TypeCommand::execute(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "type: missing argument\n";
        return;
    }
    const std::string& cmd = args[0];
    if (cmd != "cat" && factory_.exists(cmd)) {
        std::cout << cmd << " is a shell builtin\n";
    } else {
        PathUtils pathUtils;
        std::string path = pathUtils.findExecutablePath(cmd);
        std::cout << cmd << (path.empty() ? " not found" : " is " + path) << '\n';
    }
}

std::unique_ptr<ICommand> TypeCommand::clone() const {
    return std::make_unique<TypeCommand>(*this);
}
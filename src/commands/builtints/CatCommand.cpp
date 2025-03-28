#include "../../../include/commands/builtins/CatCommand.h"
#include <fstream>

void CatCommand::execute(const std::vector<std::string>& args) {
    if (args.empty()) return; // Handle stdin if needed

    for (const auto& file : args) {
        std::ifstream fin(file);
        if (fin) std::cout << fin.rdbuf();
        else std::cerr << "cat: " << file << ": No such file or directory\n";
    }
}

std::unique_ptr<ICommand> CatCommand::clone() const {
    return std::make_unique<CatCommand>(*this);
}
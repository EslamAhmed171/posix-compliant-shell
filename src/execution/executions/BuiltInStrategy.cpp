#include "../../../include/execution/executions//BuiltInStrategy.h"

BuiltInStrategy::BuiltInStrategy(CommandFactory& factory) : factory_(factory) {}

int BuiltInStrategy::execute(const std::vector<std::string>& args) {
    if (args.empty()) return EXIT_FAILURE;

    auto command = factory_.create(args[0]);
    if (!command) return EXIT_FAILURE;

    command->execute({args.begin()+1, args.end()});
    return EXIT_SUCCESS;
}
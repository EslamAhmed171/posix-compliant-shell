#include "../../include/execution/CommandDispatcher.h"
#include <iostream>

CommandDispatcher::CommandDispatcher(StrategyHolder& strategies,
                                     RedirectionHandler& redirector)
        : strategies_(strategies), redirector_(redirector) {}

void CommandDispatcher::dispatch(const ParseResult& parse_result) {
    if (parse_result.args.empty()) {
        std::cerr << "Error: Empty command\n";
        return;
    }

    try {
        redirector_.apply(parse_result.redirections);
        ExecutionStrategy& strategy =
                strategies_.selectStrategy(parse_result.args[0]);

        const std::vector<std::string> args(
                parse_result.args.begin(),
                parse_result.args.end()
        );

        strategy.execute(args);
        redirector_.restore();
        return;
    }
    catch (const std::exception& e) {
        return;
    }
    catch (...) {
        std::cerr << "Unknown error occurred\n";
        return;
    }
}

#include "../../include/autocomplete/CompletionManager.h"
#include "../../include/autocomplete/autocompleters/BuiltinCompleter.h"
#include "../../include/autocomplete/autocompleters/ExternalCompleter.h"
#include "../../include//commands/CommandFactory.h"

CompletionManager::CompletionManager() {
    // Register default strategies
    completers_.emplace_back(std::make_unique<BuiltinCompleter>());
    completers_.emplace_back(std::make_unique<ExternalCompleter>());
}

void CompletionManager::registerCompleter(std::unique_ptr<Completer> completer) {
    completers_.push_back(std::move(completer));
}

std::vector<std::string> CompletionManager::getCompletions(const std::string& input) const {
    for (const auto& completer : completers_) {
        if (completer->shouldTrigger(input)) {
            auto matches = completer->complete(input);
            if (!matches.empty()) {
                return matches;
            }
        }
    }
    return {};
}
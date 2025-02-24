// CompletionSystem.h
#pragma once
#include <string>
#include <vector>

class Completer {
public:
    virtual ~Completer() = default;
    virtual std::vector<std::string> complete(const std::string& input) = 0;
};

class BuiltinCompleter : public Completer {
public:
    std::vector<std::string> complete(const std::string& input) override;
};

class ExternalCommandCompleter : public Completer {
public:
    std::vector<std::string> complete(const std::string& input) override;
};

class CompletionManager {
public:
    CompletionManager();
    std::vector<std::string> getCompletions(const std::string& input);

private:
    BuiltinCompleter builtinCompleter;
    ExternalCommandCompleter externalCompleter;
};
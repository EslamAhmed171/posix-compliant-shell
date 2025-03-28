#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include "ICommand.h"
#include <unordered_map>
#include <functional>
#include <string_view>
#include <memory>
#include <vector>

class CommandFactory {
public:
    CommandFactory();

    // Core functionality
    std::unique_ptr<ICommand> create(std::string_view command_name) const;
    bool exists(std::string_view command_name) const noexcept;

    // Extension point for new commands
    void registerCommand(std::string_view name, std::function<std::unique_ptr<ICommand>()> creator);

    static std::vector<std::string> getCommandNames();

private:
    using CommandRegistry = std::unordered_map<std::string, std::function<std::unique_ptr<ICommand>()>>;

    void registerBuiltInCommands();
    mutable CommandRegistry registry_;
};

#endif // COMMAND_FACTORY_H
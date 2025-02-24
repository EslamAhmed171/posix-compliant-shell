#ifndef EXTERNALCOMMANDHANDLER_H
#define EXTERNALCOMMANDHANDLER_H

#include <vector>
#include <string>
#include "CommandParser.h"

class ExternalCommandHandler {
public:
    void handleCommand(const std::string& commandName,
                       const std::vector<std::string>& args,
                       const std::vector<Redirection>& redirections);
};

#endif // EXTERNALCOMMANDHANDLER_H
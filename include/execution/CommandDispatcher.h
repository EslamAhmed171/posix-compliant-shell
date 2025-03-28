#ifndef COMMAND_DISPATCHER_H
#define COMMAND_DISPATCHER_H

#include "StrategyHolder.h"
#include "../redirection/RedirectionHandler.h"
#include "../parsing/data-structures/ParseResult.h"
#include <string>
#include <vector>

class CommandDispatcher {
public:
    CommandDispatcher(StrategyHolder& strategies, RedirectionHandler& redirector);
    void dispatch(const ParseResult& parse_result);

private:
    StrategyHolder& strategies_;
    RedirectionHandler& redirector_;
};

#endif // COMMAND_DISPATCHER_H
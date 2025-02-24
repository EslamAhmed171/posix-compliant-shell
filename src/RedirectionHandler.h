#ifndef REDIRECTIONHANDLER_H
#define REDIRECTIONHANDLER_H

#include <vector>
#include <unordered_map>
#include "CommandParser.h"

class RedirectionHandler {
public:
    void apply(const std::vector<Redirection>& redirections);
    void restore();

private:
    std::unordered_map<int, int> original_fds;
};

#endif // REDIRECTIONHANDLER_H
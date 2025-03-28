#ifndef PARSE_RESULT_H
#define PARSE_RESULT_H

#include <vector>
#include <string>
#include "../../redirection/data-structures/Redirection.h"

struct ParseResult {
    std::vector<std::string> args;
    std::vector<Redirection> redirections;
};

#endif //PARSE_RESULT_H

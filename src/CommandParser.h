#pragma once
#include <vector>
#include <string>
#include "Redirection.cpp"
class CommandParser {
public:
    struct ParseResult {
        std::vector<std::string> args;
        std::vector<Redirection> redirections;
    };

    ParseResult parse(const std::string& input);

private:
    std::vector<std::string> tokenizeEcho(const std::string& input);
    std::vector<std::string> tokenizeGeneral(const std::string& input);
    bool isRedirectOperator(const std::string& token) const;
    bool parseRedirectOperator(const std::string& token, Redirection& redir) const;
};
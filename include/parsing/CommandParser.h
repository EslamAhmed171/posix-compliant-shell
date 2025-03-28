#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "data-structures/ParseResult.h"
#include "TokenizerFactory.h"
class CommandParser {
public:
    explicit CommandParser(std::unique_ptr<TokenizerFactory> tokenizer_factory);
    ParseResult parse(const std::string& input);

private:
    std::unique_ptr<TokenizerFactory> tokenizer_factory_;
    bool isRedirectOperator(const std::string& token) const;
    bool parseRedirectOperator(const std::string& token, Redirection& redir) const;
    bool processRedirection(const std::vector<std::string>& tokens,
                                           size_t& i, ParseResult& result);
    std::string extractCommandName(const std::string& input);
    static const std::unordered_map<std::string, std::pair<int, Redirection::Mode>> redirect_ops;
};

#endif //COMMAND_PARSER_H

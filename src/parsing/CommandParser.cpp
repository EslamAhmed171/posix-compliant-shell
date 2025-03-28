#include "../../include/parsing/CommandParser.h"
#include <unordered_set>

CommandParser::CommandParser(std::unique_ptr<TokenizerFactory> tokenizer_factory)
        : tokenizer_factory_(std::move(tokenizer_factory)) {
}

const std::unordered_map<std::string, std::pair<int, Redirection::Mode>>
        CommandParser::redirect_ops = {
        {">",  {1, Redirection::TRUNCATE}},
        {">>", {1, Redirection::APPEND}},
        {"1>", {1, Redirection::TRUNCATE}},
        {"1>>",{1, Redirection::APPEND}},
        {"2>", {2, Redirection::TRUNCATE}},
        {"2>>",{2, Redirection::APPEND}}
};

ParseResult CommandParser::parse(const std::string &input) {
    ParseResult result;

    // Extract command name without full tokenization
    std::string command = extractCommandName(input);

    // Get appropriate tokenizer
    auto tokenizer = tokenizer_factory_->getTokenizer(command);
    auto tokens = tokenizer->tokenize(input);

    // Process tokens
    for (size_t i = 0; i < tokens.size();) {
        if (isRedirectOperator(tokens[i])) {
            if (processRedirection(tokens, i, result)) continue;
        }
        result.args.push_back(tokens[i]);
        i++;
    }

    return result;
}

std::string CommandParser::extractCommandName(const std::string& input) {
    bool in_quote = false;
    char quote_char = 0;
    std::string command;

    for (char c : input) {
        if (!in_quote && std::isspace(c)) break;
        if (c == '\'' || c == '"') {
            if (!in_quote) {
                quote_char = c;
                in_quote = true;
                continue;
            } else if (c == quote_char) {
                in_quote = false;
                continue;
            }
        }
        command += c;
    }

    return command;
}

bool CommandParser::isRedirectOperator(const std::string &token) const {
    return redirect_ops.find(token) != redirect_ops.end();
}

bool CommandParser::processRedirection(const std::vector<std::string>& tokens,
                                       size_t& i, ParseResult& result) {
    Redirection redir;
    if (parseRedirectOperator(tokens[i], redir) && (i + 1 < tokens.size())) {
        redir.filename = tokens[i + 1];
        result.redirections.push_back(redir);
        i += 2;
        return true;
    }
    return false;
}

bool CommandParser::parseRedirectOperator(const std::string &token, Redirection &redir) const {
    auto it = redirect_ops.find(token);
    if (it != redirect_ops.end()) {
        redir.fd = it->second.first;
        redir.mode = it->second.second;
        return true;
    }
    return false;
}


#include "../../../include/parsing/tokenizers/EchoTokenizer.h"

std::vector<std::string> EchoTokenizer::tokenize(const std::string &input) {
    std::vector<std::string> tokens;
    std::string token;
    State state = State::Normal;

    for (char c : input) {
        switch (state) {
            case State::Normal:
                if (c == '\\') {
                    state = State::EscapeNormal;
                } else if (c == '\'') {
                    state = State::SingleQuote;
                } else if (c == '"') {
                    state = State::DoubleQuote;
                } else if (isspace(c)) {
                    if (!token.empty()) {
                        tokens.push_back(token);
                        token.clear();
                    }
                } else {
                    token += c;
                }
                break;

            case State::EscapeNormal:
                token += c;  // Always add escaped char
                state = State::Normal;
                break;

            case State::SingleQuote:
                if (c == '\'') {
                    state = State::Normal;
                } else {
                    token += c;  // No escaping in single quotes
                }
                break;

            case State::DoubleQuote:
                if (c == '\\') {
                    state = State::EscapeDouble;
                } else if (c == '"') {
                    state = State::Normal;
                } else {
                    token += c;
                }
                break;

            case State::EscapeDouble:
                token += c;  // Handle escaped chars in double quotes
                state = State::DoubleQuote;
                break;
        }
    }

    if (!token.empty()) tokens.push_back(token);
    return tokens;
}

std::unique_ptr<Tokenizer> EchoTokenizer::clone() const {
    return std::make_unique<EchoTokenizer>(*this);
}
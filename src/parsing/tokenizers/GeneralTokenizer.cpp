#include "../../../include/parsing/tokenizers/GeneralTokenizer.h"

std::vector<std::string> GeneralTokenizer::tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::string token;
    State state = State::Normal;

    for (char c : input) {
        switch (state) {
            case State::Normal:
                if (c == '\'') {
                    state = State::SingleQuote;
                } else if (c == '\"') {
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

            case State::SingleQuote:
                if (c == '\'') {
                    state = State::Normal;
                } else {
                    token += c;
                }
                break;

            case State::DoubleQuote:
                if (c == '"') {
                    state = State::Normal;
                } else {
                    token += c;
                }
                break;
        }
    }

    if (!token.empty()) tokens.push_back(token);
    return tokens;
}

std::unique_ptr<Tokenizer> GeneralTokenizer::clone() const {
    return std::make_unique<GeneralTokenizer>(*this);
}
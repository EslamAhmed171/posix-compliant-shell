#ifndef GENERAL_TOKENIZER_H
#define GENERAL_TOKENIZER_H

#include "../ITokenizer.h"

class GeneralTokenizer : public Tokenizer {
public:
    std::vector<std::string> tokenize(const std::string& input) override;
    std::unique_ptr<Tokenizer> clone() const override;
private:
    enum class State {
        Normal,
        SingleQuote,
        DoubleQuote
    };
};

#endif //GENERAL_TOKENIZER_H

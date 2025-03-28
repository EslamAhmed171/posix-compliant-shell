#ifndef ECHO_TOKENIZER_H
#define ECHO_TOKENIZER_H

#include "../ITokenizer.h"

class EchoTokenizer : public Tokenizer {
public:
    std::vector<std::string> tokenize(const std::string& input) override;
    std::unique_ptr<Tokenizer> clone() const override;
private:
    enum class State {
        Normal,          // Default parsing mode
        SingleQuote,     // Inside single quotes ''
        DoubleQuote,     // Inside double quotes ""
        EscapeNormal,    // Escape detected in normal mode
        EscapeDouble     // Escape detected inside double quotes
    };
};

#endif //ECHO_TOKENIZER_H

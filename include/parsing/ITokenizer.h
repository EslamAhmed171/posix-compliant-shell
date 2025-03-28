#ifndef I_TOKENIZER_H
#define I_TOKENIZER_H

#pragma once
#include <vector>
#include <string>
#include <memory>

class Tokenizer {
public:
    virtual ~Tokenizer() = default;
    virtual std::vector<std::string> tokenize(const std::string& input) = 0;
    virtual std::unique_ptr<Tokenizer> clone() const = 0;
};

#endif //I_TOKENIZER_H

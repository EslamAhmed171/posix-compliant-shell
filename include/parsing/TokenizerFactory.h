#ifndef TOKENIZER_FACTORY_H
#define TOKENIZER_FACTORY_H

#pragma once
#include "ITokenizer.h"
#include <memory>
#include <unordered_map>

class TokenizerFactory {
public:
    TokenizerFactory();
    std::unique_ptr<Tokenizer> getTokenizer(const std::string& command) const;
    void registerTokenizer(const std::string& command, std::unique_ptr<Tokenizer> tokenizer);
    void setDefaultTokenizer(std::unique_ptr<Tokenizer> tokenizer);

private:
    std::unordered_map<std::string, std::unique_ptr<Tokenizer>> registry_;
    std::unique_ptr<Tokenizer> default_tokenizer_;
};

#endif //TOKENIZER_FACTORY_H

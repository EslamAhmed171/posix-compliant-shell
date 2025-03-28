#include "../../include/parsing/TokenizerFactory.h"
#include "../../include/parsing/tokenizers/EchoTokenizer.h"
#include "../../include/parsing/tokenizers/GeneralTokenizer.h"

TokenizerFactory::TokenizerFactory() {
    registerTokenizer("echo", std::make_unique<EchoTokenizer>());
    // Register other commands here
    setDefaultTokenizer(std::make_unique<GeneralTokenizer>());
}

void TokenizerFactory::registerTokenizer(const std::string& command,
                                         std::unique_ptr<Tokenizer> tokenizer) {
    registry_[command] = std::move(tokenizer);
}

void TokenizerFactory::setDefaultTokenizer(std::unique_ptr<Tokenizer> tokenizer) {
    default_tokenizer_ = std::move(tokenizer);
}

std::unique_ptr<Tokenizer> TokenizerFactory::getTokenizer(const std::string& command) const {
    const auto it = registry_.find(command);
    return it != registry_.end() ? it->second->clone() : default_tokenizer_->clone();
}
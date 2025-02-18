
#ifndef BUILTIN_COMPLETION_HANDLER_H
#define BUILTIN_COMPLETION_HANDLER_H

class BuiltinCompletionHandler{
public:
    std::string handleInCompleteCommand(const std::string& incompleteCommand);
};

#endif //BUILTIN_COMPLETION_HANDLER_H

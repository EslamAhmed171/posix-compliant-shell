
#ifndef BUILTIN_COMPLETION_HANDLER_H
#define BUILTIN_COMPLETION_HANDLER_H

class BuiltinCompletionHandler{
public:
    std::string handleInCompleteCommand(const std::string& incompleteCommand);
    std::string HandleExternalCommand(const std::string& incompleteExternalCommand);
};

#endif //BUILTIN_COMPLETION_HANDLER_H

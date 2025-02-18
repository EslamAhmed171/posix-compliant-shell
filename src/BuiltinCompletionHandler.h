#ifndef BUILTIN_COMPLETION_HANDLER_H
#define BUILTIN_COMPLETION_HANDLER_H

#include <vector>
class BuiltinCompletionHandler{
public:
    std::string handleInCompleteCommand(const std::string& incompleteCommand);
    std::vector<std::string> HandleExternalCommand(const std::string& incompleteExternalCommand);
};

#endif //BUILTIN_COMPLETION_HANDLER_H

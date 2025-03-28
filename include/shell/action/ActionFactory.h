#ifndef ACTION_FACTORY_H
#define ACTION_FACTORY_H

#include <memory>
class InputAction;
class InputHandler;

// Factory for creating appropriate actions based on input characters
class ActionFactory {
public:
    static std::unique_ptr<InputAction> createAction(char c, const InputHandler& handler);
};

#endif // ACTION_FACTORY_H
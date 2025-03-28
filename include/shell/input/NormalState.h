#ifndef NORMAL_STATE_H
#define NORMAL_STATE_H

#include "InputState.h"

// Normal input state - default state for most input
class NormalState : public InputState {
public:
    void handle(char c, InputHandler& handler) override;
};

#endif // NORMAL_STATE_H
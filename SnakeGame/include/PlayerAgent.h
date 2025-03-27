#pragma once
#include "BaseAgent.h"
#include <queue>

class PlayerAgent: public BaseAgent{
public:
    PlayerAgent(int KeyboardLayout=0);
    virtual void KeyDown(int Key) override;
    virtual int GetNextDirection() override;
private:
    int mKeyboardLayout;
    std::queue<Direction> mDirections;

};


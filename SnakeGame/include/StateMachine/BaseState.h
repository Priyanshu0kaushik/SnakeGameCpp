#pragma once
#include "SnakeGraphics.h"

class BaseState{

public:
    virtual bool Init();
    virtual void Update();
    virtual void Render(SnakeGraphics& snakeGraphics );
    virtual void CleanUp();
    virtual void KeyDown(int Key);
};

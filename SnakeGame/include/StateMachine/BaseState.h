#pragma once
#include "SnakeGraphics.h"

class BaseState{

public:
    virtual bool Init();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void CleanUp();
    virtual void KeyDown(int Key);
};

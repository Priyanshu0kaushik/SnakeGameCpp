#pragma once
#include "BaseState.h"

class OutroState: public BaseState{
    
public:
    bool Init() override;
    void Update() override;
    void Render(SnakeGraphics& snakeGraphics) override;
    void CleanUp() override;
    void KeyDown(int Key) override;
};



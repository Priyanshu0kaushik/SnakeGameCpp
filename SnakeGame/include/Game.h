#pragma once
#include <iostream>
#include "SnakeGraphics.h"

class Game{
  
public:
    static Game& GetInstance();
    void Run();
    SnakeGraphics* snakeGraphics{nullptr};
    
private:
    Game() = default;
    const float FPS = 60.f;
    Game* mInstance;
    bool Init();
    void Update(float deltaTime);
    void Render();
    void CleanUp();
    void KeyDownCallback(int Key);
};

#pragma once
#include <iostream>
#include "SnakeGraphics.h"

class Game{
  
public:
    static Game& GetInstance();
    void Run();
    SnakeGraphics* snakeGraphics;

    
    
private:
    Game();
    const float FPS = 60.f;
    bool Init();
    void Update(float deltaTime);
    void Render();
    void CleanUp();
    void KeyDownCallback(int Key);

    static Game* mInstance;
};

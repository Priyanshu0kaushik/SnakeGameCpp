#pragma once
#include <iostream>

class SnakeGraphics;

class Game{
  
public:
    static Game& GetInstance();
    void Run();
    SnakeGraphics* snakeGraphics{nullptr};
    
private:
    Game() = default;
    const float FPS = 60.f;
    static std::unique_ptr<Game> mInstance;
    bool Init();
    void Update();
    void Render();
    void CleanUp();
    void KeyDownCallback(int Key);
};

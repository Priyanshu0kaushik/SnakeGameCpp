#pragma once
#include "BaseState.h"

enum Buttons{
    Play,
    Quit,
    End
};

class MenuState: public BaseState{
    
public:
    bool Init() override;
    void Update() override;
    void Render(SnakeGraphics& snakeGraphics) override;
    void CleanUp() override;
    void KeyDown(int Key) override;
    
private:
    Buttons mButtonSelected;
    void CreateButton(char* string);
    
};



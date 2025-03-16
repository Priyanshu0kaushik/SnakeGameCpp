#pragma once
#include <iostream>
#include "BaseState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "OutroState.h"

class StateMachine{
public:
    static StateMachine& GetInstance();
    template <typename T>
    void SwitchState();
    
    void Update();
    void Render(SnakeGraphics& snakeGraphics);
    void KeyDown(int Key);
    
private:
    StateMachine() = default;
    static std::unique_ptr<StateMachine> mInstance;
    MenuState menuState;
    PlayState playState;
    OutroState outroState;
    BaseState* mStates[3] = {&menuState, &playState, &outroState};
    BaseState* mCurrentState{nullptr};
};

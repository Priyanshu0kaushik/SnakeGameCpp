#pragma once
#include <vector>
#include <iostream>
#include "BaseState.h"

class GameObject;
class OutroState: public BaseState{
    
public:
    bool Init() override;
    void Update(float deltaTime) override;
    void Render() override;
    void CleanUp() override;
    void KeyDown(int Key) override;

private:
    std::vector<GameObject*> mGameObjects;
    void ShowSingleplayerScore();
    void ShowMultiplayerScore();

};



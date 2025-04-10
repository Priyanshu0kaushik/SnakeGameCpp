#pragma once
#include "BaseState.h"

class World;
class PlayState: public BaseState{
    
public:
    
    bool Init() override;
    void Update(float deltaTime) override;
    void Render() override;
    void CleanUp() override;
    void KeyDown(int Key) override;
    
private:
    World* world;
};



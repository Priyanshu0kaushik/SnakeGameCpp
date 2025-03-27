#pragma once
#include "World.h"
#include "PlayGameObject.h"
#include <vector>

class BaseAgent;
class World;
class Snake : public PlayGameObject{
public:
    Snake(World* world, BaseAgent* playerAgent, const int x,const int y,World::snakeData* Data);
    void Init() override;
    void Update(float deltaTime) override;
    void Render() override;
    bool GetPos(int index, std::pair<int,int>& outPos) override;
    void OnCollision(PlayGameObject* gameObject) override;
    World::snakeData* myData;
//    void Destroy() override;
//    bool IsDestroyed() override;
    
private:
    BaseAgent* mPlayerAgent;
    std::vector<std::pair<int, int>> mBody;
    std::pair<int, int> mDirection;
    int mPreviousDirection;
    bool mHasEatenApple;
    float m_timeSinceMoved = 0.0f;
    float m_moveOnTime = 0.25f;
    float m_removeTimeStep = 0.02f;
    
    void MakeSnakeFaster();
    void HandleInput(int direction);
    void Move();
    void Grow();
};

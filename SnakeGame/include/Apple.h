#pragma once
#include "PlayGameObject.h"

class World;
class Apple: public PlayGameObject{
public:
    Apple(World* world, const int x, const int y);
    void Init() override;
    void Update(float deltaTime) override;
    void Render() override;
    bool GetPos(int index, std::pair<int,int>& outPos) override;
    void OnCollision(PlayGameObject* gameObject) override;
    void Destroy() override;
};

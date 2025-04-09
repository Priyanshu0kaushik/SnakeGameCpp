#pragma once
#include "GameObject.h"
#include <iostream>

class World;

class PlayGameObject: public GameObject{

public:
    PlayGameObject(World* world, int x, int y);
    virtual bool GetPos(int index, std::pair<int,int>& outPos);
    virtual void OnCollision(PlayGameObject* gameObject, std::pair<int,int> collisionPos);
    World* mWorld;
};

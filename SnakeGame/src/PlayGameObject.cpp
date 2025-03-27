#include "PlayGameObject.h"
#include "World.h"

PlayGameObject::PlayGameObject(World* world, int x, int y): GameObject(x, y),
mWorld(world)
{
    world->AddGameObjectToWorld(this);
}

bool PlayGameObject::GetPos(int index, std::pair<int,int>& outPos){
    return true;
}

void PlayGameObject::OnCollision(PlayGameObject* gameObject){
    
}

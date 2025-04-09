#include "GameObject.h"

GameObject::GameObject(int x, int y):
xPos{x},
yPos{y},
mIsDestroyed{false},
ObjName{""}
{
    
}

void GameObject::Destroy(){
    mIsDestroyed = true;
}

bool GameObject::IsDestroyed(){
    return mIsDestroyed;
}

void GameObject::Init(){

}

void GameObject::Render(){
    
}

void GameObject::Update(float deltaTime){
    
}


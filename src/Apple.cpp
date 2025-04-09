#include "Apple.h"
#include "Snake.h"
#include "World.h"
#include "PlayGameObject.h"
#include "Game.h"
#include <iostream>

Apple::Apple(World* world, const int x, const int y): PlayGameObject(world, x, y){
//    Init();
    ObjName = "Apple";
}

void Apple::Init(){
    std::cout<<"Apple Initiated."<<std::endl;
}

void Apple::Render(){
    
    Game::GetInstance().snakeGraphics->PlotTile(xPos, yPos, 0, Color{0,255,0}, Color{255,255,255}, ' ');
}

void Apple::Update(float deltaTime){
    
}

bool Apple::GetPos(int index, std::pair<int,int>& outPos){
    
    if(index> 0){
        return false;
    }
    outPos = {xPos, yPos};
    return true;
}

void Apple::OnCollision(PlayGameObject* gameObject, std::pair<int,int> collisionPos){

    if (Snake* snake = dynamic_cast<Snake*>(gameObject))
    {
        std::cout << "collided with : " << gameObject->ObjName << std::endl;
        mWorld->AddScore(snake->myData);
        Destroy();
    }

    
}

void Apple::Destroy(){
    mIsDestroyed = true;
}

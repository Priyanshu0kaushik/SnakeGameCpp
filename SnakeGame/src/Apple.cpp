#include "Apple.h"
#include "Snake.h"
#include "World.h"
#include "PlayGameObject.h"
#include "Game.h"
#include <iostream>

Apple::Apple(World* world, const int x, const int y): PlayGameObject(world, x, y){
//    Init();
}

void Apple::Init(){
    std::cout<<"Apple Initiated."<<std::endl;
}

void Apple::Render(){
    Game::GetInstance().snakeGraphics->PlotTile(xPos, yPos, 0, Color{0,0,0}, Color{255,255,255}, ' ');
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

void Apple::OnCollision(PlayGameObject* gameObject){
    if(typeid(gameObject) == typeid(Snake)){
        if(Snake* snake = dynamic_cast<Snake*>(gameObject)) {
            mWorld->AddScore(snake->myData);
        }
        Destroy();
    }
}

void Apple::Destroy(){
    mIsDestroyed = true;
}

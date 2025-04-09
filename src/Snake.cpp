#include "Snake.h"
#include "PlayGameObject.h"
#include <iostream>
#include <vector>
#include "Game.h"
#include "Apple.h"
#include "Core.h"
#include "SnakeGraphics.h"
#include "PlayerAgent.h"

Snake::Snake(World* world,BaseAgent* playerAgent, int x, int y, World::snakeData* Data): PlayGameObject(world, x, y),
mDirection{1,0},
mPreviousDirection{(int)PlayerAgent::Direction::RIGHT},
myData{Data},
mHasEatenApple{false},
mPlayerAgent(playerAgent)
{
    mPlayerAgent->mSnake = this;
    world->SnakeData.emplace_back(myData);
    mBody.emplace_back(x,y);
    ObjName = "Snake";
}

void Snake::Render(){
    for(std::pair<int,int> pair : mBody){
        Game::GetInstance().snakeGraphics->PlotTile(pair.first, pair.second, 0, Color{255,0,0}, Color{255,255,255}, ' ');
    }
}

void Snake::Init(){
    std::cout<<"Snake Init"<<std::endl;
}

void Snake::Update(float deltaTime){
    
    m_timeSinceMoved += deltaTime;
    
    while (m_timeSinceMoved >= m_moveOnTime)
    {
        m_timeSinceMoved -= m_moveOnTime;
        HandleInput(mPlayerAgent->GetNextDirection());
        Move();
    }
}

void Snake::HandleInput(int direction){
    
    switch (direction) {
        case (int)PlayerAgent::Direction::UP:
            if(mPreviousDirection!= (int)PlayerAgent::Direction::DOWN){
                mDirection = {0,-1};
                mPreviousDirection = direction;
            }
            break;
        case (int)PlayerAgent::Direction::RIGHT:
            if(mPreviousDirection!= (int)PlayerAgent::Direction::LEFT){
                mDirection = {1,0};
                mPreviousDirection = direction;
            }
            
            break;
        case (int)PlayerAgent::Direction::LEFT:
            if(mPreviousDirection!= (int)PlayerAgent::Direction::RIGHT){
                mDirection = {-1,0};
                mPreviousDirection = direction;
            }
            break;
        case (int)PlayerAgent::Direction::DOWN:
            if(mPreviousDirection!= (int)PlayerAgent::Direction::UP){
                mDirection = {0,1};
                mPreviousDirection = direction;
            }
            break;
        default:
            break;
    }
    
}

void Snake::Move(){
    int x = mDirection.first + mBody.front().first;
    int y = mDirection.second + mBody.front().second;
    
    mBody.insert(mBody.begin(), {x,y});
    
    if(!mHasEatenApple){
        mBody.pop_back();
    }
    else{
        mHasEatenApple = false;
    }
}

void Snake::Grow(){
    mHasEatenApple = true;
    MakeSnakeFaster();
}

void Snake::MakeSnakeFaster(){
    m_moveOnTime -= m_removeTimeStep;
}

bool Snake::GetPos(int index, std::pair<int,int>& outPos){
    
    if(index> mBody.size()-1){
        return false;
    }
    outPos = mBody[index];
    return true;
}

void Snake::OnCollision(PlayGameObject* gameObject, std::pair<int,int> collisionPos){

    if (Apple* apple = dynamic_cast<Apple*>(gameObject)) 
    {
        std::cout << "Collided with : " << gameObject->ObjName << std::endl;
        Grow();
    }
    else if (Snake* snake = dynamic_cast<Snake*>(gameObject))
    {
        std::cout << "collided with : " << gameObject->ObjName << std::endl;
        mWorld->OverGame();
    }
    else{
        
    }
}

std::pair<int, int> Snake::GetHead(){
    return mBody.front();
}

void Snake::Resize(int xPos,int yPos){
    mBody.clear();
    mBody.emplace_back(xPos, yPos);
    mDirection = {1,0};
    mPreviousDirection = {1,0};
    m_moveOnTime = m_defaultMoveOnTime;
    
}

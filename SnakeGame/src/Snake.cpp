#include "Snake.h"
#include "PlayGameObject.h"
#include <iostream>
#include <vector>
#include "Game.h"
#include "Apple.h"
#include "SnakeGraphics.h"
#include "PlayerAgent.h"

Snake::Snake(World* world,BaseAgent* playerAgent, int x, int y, World::snakeData* Data): PlayGameObject(world, x, y),
mDirection{0,1},
myData{Data},
mPlayerAgent(playerAgent)
{
    mPlayerAgent->mSnake = this;
    world->SnakeData.emplace_back(myData);
    mBody.emplace_back(x,y);
}

void Snake::Render(){
    for(std::pair<int,int> pair : mBody){
        Game::GetInstance().snakeGraphics->PlotTile(pair.first, pair.second, 0, Color{0,0,0}, Color{255,255,255}, ' ');
    }
}

void Snake::Init(){
    std::cout<<"Snake Init"<<std::endl;
}

void Snake::Update(float deltaTime){
    std::cout<<"SnakeUpdate"<<std::endl;
    m_timeSinceMoved += deltaTime;
    std::cout<< (int) m_timeSinceMoved <<std::endl;
    while (m_timeSinceMoved >= m_moveOnTime)
    {
        std::cout<<"Snake Moved"<<std::endl;
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
            }
            break;
        case (int)PlayerAgent::Direction::RIGHT:
            if(mPreviousDirection!= (int)PlayerAgent::Direction::LEFT){
                mDirection = {1,0};
            }
            
            break;
        case (int)PlayerAgent::Direction::LEFT:
            if(mPreviousDirection!= (int)PlayerAgent::Direction::RIGHT){
                mDirection = {-1,0};
            }
            break;
        case (int)PlayerAgent::Direction::DOWN:
            if(mPreviousDirection!= (int)PlayerAgent::Direction::UP){
                mDirection = {0,1};
            }
            break;
        default:
            break;
    }
    mPreviousDirection = direction;
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

void Snake::OnCollision(PlayGameObject* gameObject){
    if(typeid(gameObject) == typeid(Apple)){
        Grow();
    }
    else if (typeid(gameObject) == typeid(Snake)){
        mWorld->OverGame();
    }
    else{
        
    }
}

std::pair<int, int> Snake::GetHead(){
    return mBody.front();
}

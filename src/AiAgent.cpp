#include "AiAgent.h"
#include "Snake.h"

int AiAgent::GetNextDirection(){
    
    if(mPath.empty()){
        mPath = mAStarAgent->FindPath(mSnake->GetHead(), mSnake->mWorld->GetApplePos() , mSnake->mWorld->GetLevel(), mSnake->mBody);
        if (mPath.empty()){
            return (int)Direction::NONE;
        }
    }
    
    if (mPreviousTilePos == std::pair<int, int>{0, 0}) {
            mPreviousTilePos = mSnake->GetHead();
    }
    
    int x = mPath[0].first - mPreviousTilePos.first;
    int y = mPath[0].second - mPreviousTilePos.second;
    std::pair<int, int> diff = std::make_pair(x, y);
    
    Direction nextDirection;
    
    if (diff == std::make_pair(0, 1)) {
        nextDirection = Direction::RIGHT;
    }
    else if(diff == std::make_pair(0, -1)){
        nextDirection = Direction::LEFT;
    }
    else if(diff == std::make_pair(-1, 0)){
        nextDirection = Direction::UP;
    }
    else if(diff == std::make_pair(1,0)){
        nextDirection = Direction::DOWN;
    }
    else{
        nextDirection = Direction::NONE;
    }
    
    mPreviousTilePos = *mPath.begin();
    if (!mPath.empty()){
        mPath.erase(mPath.begin());
    }
    

    return (int)nextDirection;
    
}

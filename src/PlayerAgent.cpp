#include "PlayerAgent.h"
#include "Core.h"

PlayerAgent::PlayerAgent(int KeyboardLayout):
mKeyboardLayout{KeyboardLayout}
{
    
}

void PlayerAgent::KeyDown(int Key){
    
    switch (mKeyboardLayout) {
        case 0:
            if(Key == 'W'){
                mDirections.emplace(Direction::UP);
            }
            else if (Key == 'A'){
                mDirections.emplace(Direction::LEFT);
            }
            else if(Key == 'S'){
                mDirections.emplace(Direction::DOWN);
            }
            else if (Key == 'D'){
                mDirections.emplace(Direction::RIGHT);
            }
            break;
        case 1:
            if(Key == KEY_UP){
                mDirections.emplace(Direction::UP);
            }
            else if (Key == KEY_LEFT){
                mDirections.emplace(Direction::LEFT);
            }
            else if (Key == KEY_RIGHT){
                mDirections.emplace(Direction::RIGHT);
            }
            else if(Key == KEY_DOWN){
                mDirections.emplace(Direction::DOWN);
            }
        default:
            break;
    }
    
}

int PlayerAgent::GetNextDirection(){
    if(mDirections.empty()) return (int)Direction::NONE;
    
    Direction nextDirection = mDirections.front();
    mDirections.pop();

    return (int)nextDirection;
}


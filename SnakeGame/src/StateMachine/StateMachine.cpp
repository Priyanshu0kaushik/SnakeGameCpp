#include "StateMachine.h"
#include <iostream>

std::unique_ptr<StateMachine> StateMachine::mInstance = nullptr;

StateMachine& StateMachine::GetInstance(){
    return  *mInstance;
}


template <typename T>
void StateMachine::SwitchState(){
    for(int i=0; i<3; i++){
        if(typeid(T) == typeid(*mStates[i])){
            if(mCurrentState){
                mCurrentState->CleanUp();
            }
            
            mCurrentState = mStates[i];
            mCurrentState->Init();
            break;
        }
    }
}

void StateMachine::Update(){
    if(mCurrentState) mCurrentState->Update();
}

void StateMachine::Render(SnakeGraphics& snakeGraphics){
    if(mCurrentState) mCurrentState->Render(snakeGraphics);
}

void StateMachine::KeyDown(int Key){
    if(mCurrentState) mCurrentState->KeyDown(Key);
}

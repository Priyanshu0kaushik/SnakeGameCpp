#include "StateMachine.h"
#include <iostream>

StateMachine StateMachine::mInstance = StateMachine();
StateMachine::GameData StateMachine::gameData = StateMachine::GameData();

StateMachine& StateMachine::GetInstance(){

    return mInstance;
}

StateMachine::StateMachine(){
    mStates[0] = new MenuState();
    mStates[1] = new PlayState();
    mStates[2] = new OutroState();
}

void StateMachine::Update(float deltaTime){
    if(mCurrentState) mCurrentState->Update(deltaTime);
}

void StateMachine::Render(){
    if(mCurrentState) mCurrentState->Render();
}

void StateMachine::KeyDown(int Key){
    if(mCurrentState) mCurrentState->KeyDown(Key);
}

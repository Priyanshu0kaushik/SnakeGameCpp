#include "StateMachine/PlayState.h"
#include "World.h"
#include <iostream>


bool PlayState::Init(){
    world = new World();
    if(!world->Init()){
        std::cerr<<"World not initiated correctly."<<std::endl;
        return false;
    }
    return true;
}
void PlayState::Update(float deltaTime){
    world->Update(deltaTime);
}

void PlayState::Render(){
    world->Render();
}

void PlayState::CleanUp(){
    
}
void PlayState::KeyDown(int Key){
    world->KeyDown(Key);
}

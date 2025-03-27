#include "Game.h"
#include "Core.h"
#include <chrono>
#include "SnakeGraphics.h"
#include "SnakeInput.h"
#include "StateMachine.h"


Game& Game::GetInstance() {
    static Game mInstance;
    return mInstance;
}
bool Game::Init(){
    snakeGraphics = new SnakeGraphics(1024, 720, WORLD_WIDTH, WORLD_HEIGHT);
    if(!snakeGraphics->Init()){
        std::cerr<<"SnakeGraphics not initialized."<<std::endl;
        return false;
    }
    
    SnakeInput::Init(snakeGraphics);
    SnakeInput::AddKeyDownCallback(std::bind(&Game::KeyDownCallback, this, std::placeholders::_1));
    
    StateMachine::GetInstance().SwitchState<MenuState>();
    return true;
}

void Game::KeyDownCallback(int Key)
{
    std::cout << "Keydown: " << Key << std::endl;
    StateMachine::GetInstance().KeyDown(Key);
}

void Game::Run(){
    snakeGraphics->ClearScreen();
    if (!Init())
    {
        std::cerr << "Init failed!" << std::endl;

        return;
    }

    std::chrono::system_clock::time_point timer = std::chrono::system_clock::now();
    float elapsedTime = 0.f;
    float targetFrameTime = 1/FPS;
    
    while (true){
        std::chrono::duration<float> frameDeltaTime = std::chrono::system_clock::now() - timer;
        timer = std::chrono::system_clock::now();
        
        elapsedTime += frameDeltaTime.count();
        while(elapsedTime > targetFrameTime){
            Update(elapsedTime);
            std::cout<<elapsedTime<<std::endl;
            elapsedTime -= targetFrameTime;
            Render();
        }
    }
}

void Game::Update(float deltaTime){
    StateMachine::GetInstance().Update(deltaTime);
}

void Game::Render(){
    
    StateMachine::GetInstance().Render();
    snakeGraphics->Render();
}

void Game::CleanUp(){
    SnakeInput::CleanUp();
    delete snakeGraphics;
    delete mInstance;
}

#include "Game.h"
#include "Core.h"
#include <chrono>
#include "SnakeGraphics.h"
#include "SnakeInput.h"
#include "StateMachine.h"

std::unique_ptr<Game> Game::mInstance = nullptr;

Game& Game::GetInstance(){
    return  *mInstance;
}

bool Game::Init(){
    snakeGraphics = new SnakeGraphics(1024, 720, WORLD_WIDTH, WORLD_HEIGHT);
    if(snakeGraphics->Init()){
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
    if (!Init())
    {
        std::cerr << "Init failed!" << std::endl;

        return;
    }

    std::chrono::system_clock::time_point timer = std::chrono::system_clock::now();
    float elapsedTime =0.f;
    float targetFrameTime = 1/FPS;
    
    while (snakeGraphics->UpdateWindowMessages()){
        std::chrono::duration<float> frameDeltaTime = std::chrono::system_clock::now() - timer;
        timer = std::chrono::system_clock::now();
        
        elapsedTime += frameDeltaTime.count();
        while(elapsedTime > targetFrameTime){
            elapsedTime -= targetFrameTime;
            Update();
            Render();
        }
    }
}

void Game::Update(){
    StateMachine::GetInstance().Update();
}

void Game::Render(){
    
    StateMachine::GetInstance().Render(*snakeGraphics);
    snakeGraphics->Render();
}

void Game::CleanUp(){
    SnakeInput::CleanUp();
    delete snakeGraphics;
}

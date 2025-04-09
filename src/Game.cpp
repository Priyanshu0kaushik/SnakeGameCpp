#include "Game.h"
#include "Core.h"
#include <chrono>
#include "SnakeGraphics.h"
#include "SnakeInput.h"
#include "StateMachine/StateMachine.h"

Game* Game::mInstance = nullptr;

Game& Game::GetInstance() {
    
    
    if (mInstance == nullptr) {
        std::cout << "Creating new instance of Game" << std::endl;
        mInstance = new Game();
    }
    return *mInstance; 

}

Game::Game() 
{
    
}

bool Game::Init(){

    std::cout << "Init game" << std::endl;

    snakeGraphics = new SnakeGraphics(1000, 500, 60, 30);

    if(!Game::GetInstance().snakeGraphics->Init()){
        std::cerr<<"SnakeGraphics not initialized."<<std::endl;
        return false;
    }
    
    if (!SnakeInput::Init(Game::GetInstance().snakeGraphics)) {
        std::cerr << "SnakeInput init failed!\n";
        return false;
    }
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
    
  //  snakeGraphics->ClearScreen();
    if (!Init())
    {
        std::cerr << "Init failed!" << std::endl;

        return;
    }
	std::cout << "AFTER INIT" << std::endl; 
    std::chrono::system_clock::time_point timer = std::chrono::system_clock::now();
    float elapsedTime = 0.f;
    float targetFrameTime = 1/FPS;
    
    while (snakeGraphics->UpdateWindowMessages()){
        std::chrono::duration<float> frameDeltaTime = std::chrono::system_clock::now() - timer;
        timer = std::chrono::system_clock::now();
        
        elapsedTime += frameDeltaTime.count();
        while(elapsedTime > targetFrameTime){

            Update(elapsedTime);
            Render();
            elapsedTime -= targetFrameTime;
        }
    }
}

void Game::Update(float deltaTime){
    StateMachine::GetInstance().Update(deltaTime);
}

void Game::Render(){
    
    snakeGraphics->ClearScreen();
    StateMachine::GetInstance().Render();
    snakeGraphics->Render();
}

//void Game::CleanUp(){
//    SnakeInput::CleanUp();
//    delete snakeGraphics;
//    delete mInstance;
//}

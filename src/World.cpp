#include "World.h"
#include "Snake.h"
#include "Game.h"
#include "SnakeGraphics.h"
#include "StateMachine/StateMachine.h"
#include "Apple.h"
#include "PlayerAgent.h"
#include "AiAgent.h"
#include "Core.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>



bool World::Init(){
    
    if (!LoadLevel(level, levelId, WORLD_WIDTH, WORLD_HEIGHT))
    {
        std::cerr << "Level not loaded!" << std::endl;
        return false;
    }
    switch(StateMachine::gameData.gameMode){
        case StateMachine::GameData::GameMode::SinglePlayer:
            StartSingleplayerMode();
            break;
        case StateMachine::GameData::GameMode::Multiplayer:
            if(StateMachine::gameData.MultiplayerGameData.MultiGameMode == StateMachine::GameData::MultiplayerGameMode::COOP){
                StartCoOpMode();
            }
            else if (StateMachine::gameData.MultiplayerGameData.MultiGameMode == StateMachine::GameData::MultiplayerGameMode::Battle){
                StartBattleMode();
            }
            break;
    }
    
    return true;
    }
    
void World::Update(float deltaTime){
    
    if(mCurrentAppleCount==0) SpawnApple(1);
    
    switch(StateMachine::gameData.gameMode){
        case StateMachine::GameData::GameMode::SinglePlayer:
            SingleplayerModeUpdate();
            break;
        case StateMachine::GameData::GameMode::Multiplayer:
            if(StateMachine::gameData.MultiplayerGameData.MultiGameMode == StateMachine::GameData::MultiplayerGameMode::COOP){
                CoOpModeUpdate();
            }
            else if (StateMachine::gameData.MultiplayerGameData.MultiGameMode == StateMachine::GameData::MultiplayerGameMode::Battle){
                BattleModeUpdate();
            }
            break;
    }
    
    // Adding GameObjects
    for (PlayGameObject* gameObject : mGameObjectsToAdd) {
        gameObject->Init();
        mGameObjects.emplace_back(gameObject);
    }
    mGameObjectsToAdd.clear();
    
    // Updating GameObjects
    for(PlayGameObject* gO : mGameObjects){
        if(!gO->IsDestroyed()){
            gO->Update(deltaTime);
        }
    }
  
    // Collision check
    mCollisions.clear();

    for(PlayGameObject* gameObject : mGameObjects){
        std::pair<int, int> pos;
        for(int index = 0; gameObject->GetPos(index, pos); index++){
            int posIndex = pos.second * WORLD_WIDTH + pos.first;
            
            if(dynamic_cast<Snake*>(gameObject) && level[posIndex]){
                OverGame();
            }
            std::map<int, std::vector<Collision>>::iterator it = mCollisions.find(posIndex);

            if (it != mCollisions.end())
                {
                    for (std::vector<Collision>::iterator gameObject2It = it->second.begin(); gameObject2It != it->second.end();)
                    {
                        gameObject2It->gameObject->OnCollision(gameObject);
                        gameObject->OnCollision(gameObject2It->gameObject);
                        gameObject2It++;
                    }
                }

            mCollisions[posIndex].push_back({0, gameObject});
        }
    }
    
    
    // Destroy
    for(std::vector<PlayGameObject*>::iterator it = mGameObjects.begin(); it!=mGameObjects.end();){
        if((*it)->IsDestroyed())
        {
           it = mGameObjects.erase(it);
        }
        else{
            ++it;
        }
    }
    
}

void World::Render(){
    
    // Render Level
    for (int y = 0; y < WORLD_HEIGHT; y++)
    {
        for (int x = 0; x < WORLD_WIDTH; x++)
        {
            if (level[y * WORLD_WIDTH + x])
            {
                Game::GetInstance().snakeGraphics->PlotTile(x, y, 0, Color(255,255,255), Color(0,0,0), ' ');
            }
            else
            {
                // std::cout << ".";
            }
        }
    }
    
    for(PlayGameObject* gameObject : mGameObjects){
        if(!gameObject->IsDestroyed()){
            gameObject->Render();
        }
    }
    
}

void World::AddGameObjectToWorld(PlayGameObject* gameObject){
    mGameObjectsToAdd.emplace_back(gameObject);
}

void World::KeyDown(int Key){
    for(PlayerAgent* agent : mAgents){
        agent->KeyDown(Key);
    }
}

bool World:: LoadLevel(bool *outLevel, int levelId, int width, int height){

    std::cout << "LoadLevel" << std::endl;

    for(snakeData* data: SnakeData){
        data->AppleEaten = 0;
        data->AppleStreakCount = 0;
    }
    std::string filename = "level" + std::to_string(levelId) + ".txt";
    std::string path = "D:/FutureGames/Mentorship/Priyanshu/LevelsFiles/";
    std::ifstream file(path+filename);
    if (!file)
    {
        std::cerr << filename << " File not found" << std::endl;
        return false;
    }
    std::string line;
    int y = 0;
    while (std::getline(file, line))
    {
        if (line.size() != width)
        {
            std::cerr << filename <<" file have the wrong width" << std::endl;

            return false;
        }
        for (size_t x = 0; x < width; x++)
        {
            switch (line[x])
            {
            case '.':
                outLevel[y * width + x] = false;
                break;

            case '#':
                outLevel[y * width + x] = true;
                break;

            default:
                std::cerr << "Level txt file has illegal character!" << std::endl;
                return false;
            }
        }
        y++;
    }
    if (y != height)
    {
        std::cerr << "Level txt file have the wrong height" << std::endl;
        return false;
    }
    return true;
}

void World::AddScore(snakeData* Data){
    mCurrentAppleCount--;
    Data->AppleEaten++;
    Data->AppleStreakCount++;
    Data->Score += 30;
    // destroy other players streak
    for(snakeData* data : SnakeData){
        if(Data != data){
            data->AppleStreakCount = 0;
        }
    }
}

void World::OverGame(){
 // Move to OutroState
    StateMachine::gameData.datas = SnakeData;
    StateMachine::GetInstance().SwitchState<OutroState>();
}

void World::StartSingleplayerMode(){
    PlayerAgent* playerAgent = new PlayerAgent();
    mAgents.emplace_back(playerAgent);
    snakeData* data1 = new snakeData();
    new Snake(this, playerAgent, 10, 20, data1);
}



void World::SpawnApple(int count){

    mCurrentAppleCount = count;

    for(int i = 0; i<count; i++){
        int xPos = std::rand() % WORLD_WIDTH;
        int yPos = std::rand() % WORLD_HEIGHT;
        int index = yPos * WORLD_WIDTH + xPos;
        
        while(level[index]){
            xPos = std::rand() % WORLD_WIDTH;
            yPos = std::rand() % WORLD_HEIGHT;
            index = yPos * WORLD_WIDTH + xPos;
        }
        new Apple(this, xPos, yPos);
    }
    
}

void World::StartCoOpMode(){
    PlayerAgent* playerAgent1 = new PlayerAgent(0);
    mAgents.emplace_back(playerAgent1);
    snakeData* data1 = new snakeData();
    new Snake(this, playerAgent1, 10, 20, data1);
    
    if(StateMachine::gameData.MultiplayerGameData.noOfPlayers == 1){
        AiAgent* aiAgent = new AiAgent();
        snakeData* data2 = new snakeData();
        new Snake(this, aiAgent, 5, 10, data2);
    }
    else if (StateMachine::gameData.MultiplayerGameData.noOfPlayers == 2){
        PlayerAgent* playerAgent2 = new PlayerAgent(1);
        mAgents.emplace_back(playerAgent2);
        snakeData* data2 = new snakeData();
        new Snake(this, playerAgent2, 5, 10, data2);
    }
}

void World::StartBattleMode(){
    PlayerAgent* playerAgent1 = new PlayerAgent(0);
    mAgents.emplace_back(playerAgent1);
    snakeData* data1 = new snakeData();
    new Snake(this, playerAgent1, 10, 20, data1);
    
    if(StateMachine::gameData.MultiplayerGameData.noOfPlayers == 1){
        AiAgent* aiAgent = new AiAgent();
        snakeData* data2 = new snakeData();
        new Snake(this, aiAgent, 5, 10, data2);
    }
    else if (StateMachine::gameData.MultiplayerGameData.noOfPlayers == 2){
        PlayerAgent* playerAgent2 = new PlayerAgent(1);
        mAgents.emplace_back(playerAgent2);
        snakeData* data2 = new snakeData();
        new Snake(this, playerAgent2, 5, 10, data2);
    }
}

void World::SingleplayerModeUpdate(){
    if(SnakeData[0]->AppleEaten == 10){
        levelId ++;
        LoadLevel(level, levelId, WORLD_WIDTH, WORLD_HEIGHT);
        ResizeSnakes();
    }
}

void World::CoOpModeUpdate(){
    if(SnakeData[0]->AppleEaten + SnakeData[1]->AppleEaten == 10){
        levelId++;
        LoadLevel(level, levelId, WORLD_WIDTH, WORLD_HEIGHT);
        ResizeSnakes();
    }
}

void World::BattleModeUpdate(){
    for(snakeData* data : SnakeData){
        if(data->AppleStreakCount == 5){
            OverGame();
        }
    }
}

std::pair<int, int> World::GetApplePos(){
    std::pair<int, int> outPos;
    for(PlayGameObject* gameObject : mGameObjects){
        if(typeid(gameObject) == typeid(Apple)){
            gameObject->GetPos(0, outPos);
        }
    }
    return outPos;
}

bool* World::GetLevel(){
    return &level[0];
}

void World::ResizeSnakes(){
    for(PlayGameObject* gameObject : mGameObjects){
        if(Snake* snake = dynamic_cast<Snake*>(gameObject)){
            std::pair<int,int> snakePos = snake->GetHead();
            int xPos, yPos;
            int posIndex = snakePos.second * WORLD_WIDTH + snakePos.first;
            if(!level[posIndex]){
                xPos = posIndex.first();
                yPos = posIndex.second();
            }
            else{
                std::rand() % WORLD_WIDTH;
                std::rand() % WORLD_HEIGHT;
                int index = yPos * WORLD_WIDTH + xPos;
                
                while(level[index]){
                    xPos = std::rand() % WORLD_WIDTH;
                    yPos = std::rand() % WORLD_HEIGHT;
                    index = yPos * WORLD_WIDTH + xPos;
                }
            }
            
            snake->Resize(xPos,yPos);
        }
    }
}

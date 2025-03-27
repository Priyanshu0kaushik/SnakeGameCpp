#pragma once
#include "PlayGameObject.h"
#include "PlayerAgent.h"
#include "Core.h"
#include <vector>
#include <map>
#include <iostream>


struct Collision{
    int Id;
    PlayGameObject* gameObject;
};



class World{

public:
    struct snakeData{
        int AppleEaten = 0;
        int Score = 0;
        int AppleStreakCount = 0;
    };
    bool Init();
    void KeyDown(int Key);
    void Update(float deltaTime);
    void Render();
    void Destory();
    void AddGameObjectToWorld(PlayGameObject* gameObject);
    bool LoadLevel(bool *outLevel, int levelId, int width, int height);
    void OverGame();
    void AddScore(snakeData* Data);
    std::vector<snakeData*> SnakeData;
private:

    int mCurrentAppleCount = 0;
    int levelId = 1;
    bool level[WORLD_WIDTH * WORLD_HEIGHT];
    
    std::map<int,std::vector<Collision>> mCollisions;
    std::vector<PlayerAgent*> mAgents;
    std::vector<PlayGameObject*> mGameObjects;
    std::vector<PlayGameObject*> mGameObjectsToAdd;
    void StartCoOpMode();
    void StartBattleMode();
    void StartSingleplayerMode();
    void SingleplayerModeUpdate();
    void CoOpModeUpdate();
    void BattleModeUpdate();
    void SpawnApple(int count);
    
};

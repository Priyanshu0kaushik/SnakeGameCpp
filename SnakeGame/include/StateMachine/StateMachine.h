#pragma once
#include <iostream>
#include "BaseState.h"
#include "MenuState.h"
#include "World.h"
#include "PlayState.h"
#include "OutroState.h"
#include <memory>
#include <vector>



class StateMachine{
    
public:
    struct GameData{
        enum class GameMode{
            SinglePlayer,
            Multiplayer,
        };
        
        enum class MultiplayerGameMode{
            None,
            COOP,
            Battle,
        };
        struct MultiplayerData{
            MultiplayerGameMode MultiGameMode = MultiplayerGameMode::None;
            int noOfPlayers = 0;
        };
        
        
        GameMode gameMode;
        MultiplayerData MultiplayerGameData;
        std::vector<World::snakeData*> datas;
        
    };
    static StateMachine& GetInstance();
    static GameData gameData;
    template <typename T>
    void SwitchState(){
        for(int i=0; i<3; i++){
            if(typeid(T) == typeid(*mStates[i])){
                if(mCurrentState){
                    mCurrentState->CleanUp();
                }
                mCurrentState = mStates[i];
                std::cout<<"State Switched to" << typeid(*mCurrentState).name()<< std::endl;
                mCurrentState->Init();
                break;
            }
        }
    }

    
    void Update(float deltaTime);
    void Render();
    void KeyDown(int Key);
    
    
private:
    StateMachine();
    static StateMachine mInstance;
    BaseState* mStates[3];
    BaseState* mCurrentState{nullptr};
};

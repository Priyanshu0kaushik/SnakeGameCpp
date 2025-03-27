#include "MenuState.h"
#include "StateMachine.h"
//#include <Windows.h>
#include "ButtonGO.h"
#include "Core.h"
#include "TextGO.h"

bool MenuState::Init(){
    Title = new TextGO(WORLD_WIDTH/2, WORLD_HEIGHT-5, L"Snake Game");
    mGameObjects.emplace_back(Title);
    mGameObjects.emplace_back(Button1);
    mGameObjects.emplace_back(Button2);
    CreateMainMenu();
    return true;
}

void MenuState::Render(){
    switch((int)mButtonSelected){
        case Buttons::Button1:
            Button1->IsButtonSelected = true;
            Button2->IsButtonSelected = false;
        break;
        case Buttons::Button2:
            Button1->IsButtonSelected = true;
            Button2->IsButtonSelected = false;
        break;
    }
    for(GameObject* gameObject : mGameObjects){
        gameObject->Render();
    }

}

void MenuState::Update(float deltaTime){

//    std::cout<< "Button At Start: "<< Button1->Name << Button2->Name << std::endl;
//    std::cout<< "Button Selected: "<< (Buttons)mButtonSelected << std::endl;
//    KeyDown(KEY_ENTER);
//    std::cout<< "Button After Key Enter: "<< Button1->Name<< Button2->Name << std::endl;
//
//    
//    KeyDown(KEY_DOWN);
//    std::cout<< "Button After Key Down: "<< Button1->Name<< Button2->Name << std::endl;
//    KeyDown(KEY_ENTER);
}


void MenuState::KeyDown(int Key){
    if(Key == KEY_ENTER){
         switch (mCurrentMenu) {
             case MenuLevel::Main:
                 if (mButtonSelected == Buttons::Button1) {
                     mCurrentMenu = MenuLevel::PlayMode;
                     CreatePlayModeMenu();
                 } else if (mButtonSelected == Buttons::Button2) {
                     OnEnterQuitButton();
                 }
                 break;
                 
             case MenuLevel::PlayMode:
                 if (mButtonSelected == Buttons::Button1) {
                     StateMachine::GetInstance().gameData.gameMode = StateMachine::GameData::GameMode::SinglePlayer;
                     StateMachine::GetInstance().SwitchState<PlayState>();
                 } else if (mButtonSelected == Buttons::Button2) {
                     mCurrentMenu = MenuLevel::Multiplayer;
                     StateMachine::GetInstance().gameData.gameMode = StateMachine::GameData::GameMode::Multiplayer;
                     CreateMultiplayerMenu();
                 }
                 break;
                 
             case MenuLevel::Multiplayer:
                 if (mButtonSelected == Buttons::Button1) {
                     StateMachine::GetInstance().gameData.MultiplayerGameData.MultiGameMode = StateMachine::GameData::MultiplayerGameMode::COOP;
                 } else if (mButtonSelected == Buttons::Button2) {
                     StateMachine::GetInstance().gameData.MultiplayerGameData.MultiGameMode = StateMachine::GameData::MultiplayerGameMode::Battle;
                 }
                 mCurrentMenu = MenuLevel::NoOfPlayer;
                 CreateNoOfplayerMenu();
                 break;
                 
                 
             case MenuLevel::NoOfPlayer:
                 if (mButtonSelected == Buttons::Button1) {
                     StateMachine::GetInstance().gameData.MultiplayerGameData.noOfPlayers = 1;
                     StateMachine::GetInstance().SwitchState<PlayState>();
                 }
                 else if (mButtonSelected == Buttons::Button2) {
                     StateMachine::GetInstance().gameData.MultiplayerGameData.noOfPlayers = 2;
                     StateMachine::GetInstance().SwitchState<PlayState>();
                 }
                 
                 break;
         }
     }

    else if(Key == KEY_UP){
        if(mButtonSelected>0){
            mButtonSelected = (Buttons)((int)mButtonSelected-1);
        }
        else{
            mButtonSelected = (Buttons)((int)Buttons::End-1);
        }
    }
    else if (Key == KEY_DOWN){
        if(mButtonSelected < Buttons::End-1){
            mButtonSelected = (Buttons)((int)mButtonSelected+1);
        }
        else{
            mButtonSelected = (Buttons)0;
        }
    }
}

void MenuState::OnEnterQuitButton(){
//    PostQuitMessage(0);
}



void MenuState::CleanUp(){
    for(GameObject* gameObject : mGameObjects){
        delete gameObject;
    }

}


void MenuState::CreateMainMenu(){
    Button1 = new ButtonGO(WORLD_WIDTH/2, WORLD_HEIGHT/2 + 2, L"Play", "PlayButton");
    Button2 = new ButtonGO(WORLD_WIDTH/2, WORLD_HEIGHT/2 - 2, L"Quit", "QuitButton");
    mButtonSelected = (Buttons)0;
}

void MenuState::CreatePlayModeMenu(){
    Button1 = new ButtonGO(WORLD_WIDTH/2, WORLD_HEIGHT/2 + 2, L"Singleplayer", "SinglePlayerButton");
    Button2 = new ButtonGO(WORLD_WIDTH/2, WORLD_HEIGHT/2 - 2, L"Multiplayer", "MultiplayerButton");
    mButtonSelected = (Buttons)0;
}

void MenuState::CreateMultiplayerMenu(){
    Button1 = new ButtonGO(WORLD_WIDTH/2, WORLD_HEIGHT/2 + 2, L"Co-op", "CoOpButton");
    Button2 = new ButtonGO(WORLD_WIDTH/2, WORLD_HEIGHT/2 - 2, L"Battle", "BattleButton");
    mButtonSelected = (Buttons)0;
}

void MenuState::CreateNoOfplayerMenu(){
    Button1 = new ButtonGO(WORLD_WIDTH/2, WORLD_HEIGHT/2 + 2, L"One Player", "OnePlayerButton");
    Button2 = new ButtonGO(WORLD_WIDTH/2, WORLD_HEIGHT/2 - 2, L"Two Players", "TwoPlayerButton");
    mButtonSelected = (Buttons)0;
}

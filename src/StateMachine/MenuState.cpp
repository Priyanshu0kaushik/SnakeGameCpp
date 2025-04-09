#include "StateMachine/MenuState.h"
#include "StateMachine/StateMachine.h"
#include <Windows.h>
#include "ButtonGO.h"
#include "Core.h"
#include "TextGO.h"

bool MenuState::Init(){
    Title = new TextGO(WORLD_WIDTH/2, WORLD_HEIGHT/4, L"SNAKE GAME");
    Button1 = new ButtonGO(WORLD_WIDTH/2, WORLD_HEIGHT/2 - 2, L"PLAY", true,);
    Button2 = new ButtonGO(WORLD_WIDTH/2, WORLD_HEIGHT/2 + 2, L"QUIT", false);
    CreateMainMenu();
    mGameObjects.emplace_back(Title);
    mGameObjects.emplace_back(Button1);
    mGameObjects.emplace_back(Button2);

    return true;
}

void MenuState::Render(){
   
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
        std::cout << "Enter" << std::endl;
         switch (mCurrentMenu) {
             case MenuLevel::Main:
                 if (mButtonSelected == Buttons::Button1) {
                     mCurrentMenu = MenuLevel::PlayMode;
                     //CreatePlayModeMenu();
                     StateMachine::GetInstance().gameData.gameMode = StateMachine::GameData::GameMode::SinglePlayer;
                     StateMachine::GetInstance().SwitchState<PlayState>();
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
        mButtonSelected = (Buttons)0;
        Button1->SetSelected(true);
        Button2->SetSelected(false);
    }
    else if (Key == KEY_DOWN){
        mButtonSelected = (Buttons)1;
        Button1->SetSelected(false);
        Button2->SetSelected(true);
    }
}

void MenuState::OnEnterQuitButton(){
    PostQuitMessage(0);
}



void MenuState::CleanUp(){
    for(GameObject* gameObject : mGameObjects){
        delete gameObject;
    }

}

void MenuState::CreateMainMenu(){
    Button1->SetText(L"PLAY");
    Button2->SetText(L"QUIT");
    mButtonSelected = (Buttons)0;
}

void MenuState::CreatePlayModeMenu(){
    Button1->SetText(L"SINGLEPLAYER");
    Button2->SetText(L"MULTIPLAYER");
    mButtonSelected = (Buttons)0;
}

void MenuState::CreateMultiplayerMenu(){
    Button1->SetText(L"CO-OP");
    Button2->SetText(L"BATTLE");
    mButtonSelected = (Buttons)0;
}

void MenuState::CreateNoOfplayerMenu(){
    Button1->SetText(L"ONE PLAYER");
    Button2->SetText(L"TWO PLAYERS");
    mButtonSelected = (Buttons)0;
}

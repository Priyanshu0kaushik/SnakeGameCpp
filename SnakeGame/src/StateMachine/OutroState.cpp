#include "OutroState.h"
#include "StateMachine.h"
#include "SnakeGraphics.h"
#include "TextGO.h"
#include "SnakeInput.h"
#include <string>
#include "Core.h"

bool OutroState::Init(){
    TextGO* Title = new TextGO(WORLD_WIDTH/2, WORLD_HEIGHT-5, L"Snake Game");
    mGameObjects.emplace_back(Title);
    
    TextGO* Instruction = new TextGO(WORLD_WIDTH/2, WORLD_HEIGHT-5, L"Press Enter To Go To Main Menu.");
    mGameObjects.emplace_back(Instruction);
    
    return true;
}
void OutroState::Update(float deltaTime){
    
}

void OutroState::Render(){
    for(GameObject* gameobject : mGameObjects){
        gameobject->Render();
    }
}


void OutroState::CleanUp(){
    for(GameObject* gameobject : mGameObjects){
        delete gameobject;
    }
    mGameObjects.clear();
}

void OutroState::KeyDown(int Key){
    if(Key == KEY_ENTER){
        StateMachine::GetInstance().SwitchState<MenuState>();
    }
}

void OutroState::ShowSingleplayerScore(){
    std::wstring temp = std::to_wstring(StateMachine::gameData.datas[0]->Score);
    const wchar_t* InText = temp.c_str();
//    TextGO* Score = new TextGO(WORLD_WIDTH/2, WORLD_HEIGHT/2, InText);
//    mGameObjects.emplace_back(Score);

}

void OutroState::ShowMultiplayerScore(){

    TextGO* ScoreTitle1 = new TextGO(WORLD_WIDTH/2 - 10, WORLD_HEIGHT/2-2 , L"Player1 Score: ");
    mGameObjects.emplace_back(ScoreTitle1);

    wchar_t* InText1 = (wchar_t*)StateMachine::gameData.datas[0]->Score;
    TextGO* Score1 = new TextGO(WORLD_WIDTH/2 + 10, WORLD_HEIGHT/2 - 2, InText1);
    mGameObjects.emplace_back(Score1);

    
    
    
    TextGO* ScoreTitle2 = new TextGO(WORLD_WIDTH/2 - 10, WORLD_HEIGHT/2 + 2 , L"Player2 Score: " );
    mGameObjects.emplace_back(ScoreTitle2);

    wchar_t* InText2 = (wchar_t*)StateMachine::gameData.datas[1]->Score;
    TextGO* Score2 = new TextGO(WORLD_WIDTH/2 + 10, WORLD_HEIGHT/2 + 2, InText2);
    mGameObjects.emplace_back(Score2);

}

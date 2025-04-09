#pragma once
#include "GameObject.h"
#include "BaseState.h"
#include <vector>

class ButtonGO;
class TextGO;
enum class MenuLevel {
    Main,
    PlayMode,
    Multiplayer,
    NoOfPlayer,
};

enum Buttons{
    Button1,
    Button2,
    End
};

class MenuState: public BaseState{
    
public:
    bool Init() override;
    void Update(float deltaTime) override;
    void Render() override;
    void CleanUp() override;
    void KeyDown(int Key) override;
    
private:
    std::vector<GameObject*> mGameObjects;
    MenuLevel mCurrentMenu = MenuLevel::Main;
    Buttons mButtonSelected;
    ButtonGO* Button1{nullptr};
    ButtonGO* Button2{nullptr};
    TextGO* Title{nullptr};
    void CreateButton(char* string);
    void OnEnterQuitButton();
    void CreateMainMenu();
    void CreatePlayModeMenu();
    void CreateNoOfplayerMenu();
    void CreateMultiplayerMenu();
    
};



#include "ButtonGO.h"
#include "Game.h"
#include "SnakeGraphics.h"
#include "GameObject.h"

ButtonGO::ButtonGO(const int x, const int y, wchar_t* Text, char* ButtonName): GameObject(x, y),
Name{ButtonName},
mButtonText{Text},
mSpaceBetweenDotAndText(2)
{
}

void ButtonGO::Render(){
    CreateButton();
}

void ButtonGO::CreateButton(){
    Game::GetInstance().snakeGraphics->PlotText(xPos, yPos, 0, Color{0,0,0}, mButtonText, Color(255,255,255), SnakeGraphics::Alignment::Center);
    if(mIsButtonSelected){
        Game::GetInstance().snakeGraphics->PlotTile(xPos-mSpaceBetweenDotAndText, yPos, 0, Color(0,0,0), Color(0,0,0), ' ');
        
    }
}

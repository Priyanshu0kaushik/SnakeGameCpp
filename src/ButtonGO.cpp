#include "ButtonGO.h"
#include "Game.h"
#include "SnakeGraphics.h"
#include "GameObject.h"

ButtonGO::ButtonGO(const int x, const int y, wchar_t* Text,bool isSelected): GameObject(x, y),
mButtonText{Text},
mIsButtonSelected{isSelected}
{

}

void ButtonGO::SetSelected(bool selected)
{
    mIsButtonSelected = selected;
}

void ButtonGO::Render(){
    CreateButton();
}

void ButtonGO::CreateButton(){
    
    if(mIsButtonSelected)
    {
        Game::GetInstance().snakeGraphics->PlotText(xPos, yPos, 0, Color{ 122,122,122 }, mButtonText, Color(255, 255, 255), SnakeGraphics::Alignment::Center);
    }
    else 
    {
        Game::GetInstance().snakeGraphics->PlotText(xPos, yPos, 0, Color{ 122,122,122 }, mButtonText, Color(0, 0, 0), SnakeGraphics::Alignment::Center);
    }

    
}

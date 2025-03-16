#include "ButtonGO.h"
#include "Game.h"
#include "SnakeGraphics.h"

ButtonGO::ButtonGO(const int x, const int y, wchar_t* Text, bool ButtonSelected):
xPos{x},
yPos{y},
mButtonText{Text},
mIsButtonSelected{ButtonSelected},
mSpaceBetweenDotAndText(2)
{
    
}

void ButtonGO::Render(){
    
}

void ButtonGO::CreateButton(){
    Game::GetInstance().snakeGraphics->PlotText(xPos, yPos, 0, Color{0,0,0}, mButtonText, Color(255,255,255), SnakeGraphics::Alignment::Center);
    if(mIsButtonSelected){
        Game::GetInstance().snakeGraphics->PlotTile(xPos-mSpaceBetweenDotAndText, yPos, 0, Color(0,0,0), Color(0,0,0), ' ');
        
    }
}

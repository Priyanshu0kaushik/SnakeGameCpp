#include "TextGO.h"
#include "Game.h"
#include "SnakeGraphics.h"
#include "GameObject.h"


TextGO::TextGO(const int x, const int y, wchar_t* Text): GameObject(x, y),
mText{Text}
{
    
}

void TextGO::Render(){
    Game::GetInstance().snakeGraphics->PlotText(xPos, yPos, 0, Color{0,0,0}, mText, Color(255,255,255), SnakeGraphics::Alignment::Center);

}



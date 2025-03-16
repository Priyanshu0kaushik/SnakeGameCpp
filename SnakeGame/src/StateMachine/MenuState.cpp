#include "MenuState.h"

bool MenuState::Init(){
    
}

void MenuState::Render(SnakeGraphics& snakeGraphics){
//    snakeGraphics
}


void MenuState::KeyDown(int Key){
    if(Key == 72){    //up arrow
        if(mButtonSelected>0){
            mButtonSelected = (Buttons)((int)mButtonSelected-1);
        }
        else{
            mButtonSelected = (Buttons)((int)Buttons::End-1);
        }
    }
    else if (Key == 80){
        if(mButtonSelected < Buttons::End-1){
            mButtonSelected = (Buttons)((int)mButtonSelected+1);
        }
        else{
            mButtonSelected = (Buttons)0;
        }
    }
}

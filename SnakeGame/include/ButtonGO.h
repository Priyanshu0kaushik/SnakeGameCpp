#pragma once
#include "Core.h"
#include "GameObject.h"
#include <iostream>

class ButtonGO: public GameObject{
public:
    ButtonGO(const int x, const int y, wchar_t* Text, bool ButtonSelected);
    void Update() override;
    void Render() override;
    void Destroy() override;
    bool IsDestroyed() override;
    
private:
    wchar_t* mButtonText;
    const int xPos, yPos;
    bool mIsButtonSelected;
    const int mSpaceBetweenDotAndText;
    void CreateButton();
};

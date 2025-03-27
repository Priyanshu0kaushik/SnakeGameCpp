#pragma once
#include "Core.h"
#include "GameObject.h"
#include <iostream>

class ButtonGO: public GameObject{
public:
    ButtonGO(const int x, const int y,wchar_t* Text, char* ButtonName);
    bool IsButtonSelected{false};
//    void Init() override;
//    void Update() override;
    void Render() override;
//    void Destroy() override;
//    bool IsDestroyed() override;
    char* Name;
    
private:
    wchar_t* mButtonText;
    bool mIsButtonSelected{false};
    const int mSpaceBetweenDotAndText;
    void CreateButton();
};

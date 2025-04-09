#pragma once
#include "Core.h"
#include "GameObject.h"
#include <iostream>

class ButtonGO: public GameObject{
public:
    ButtonGO(const int x, const int y,wchar_t* Text, bool isSelected);
    void SetSelected(bool selected);
//    void Init() override;
//    void Update() override;
    void Render() override;
//    void Destroy() override;
//    bool IsDestroyed() override;
    void SetText(wchar_t* NewText){mButtonText = NewText;}
    
private:
    wchar_t* mButtonText;
    bool mIsButtonSelected{false};
    void CreateButton();
};

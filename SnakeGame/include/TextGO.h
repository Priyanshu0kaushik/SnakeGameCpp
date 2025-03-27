#pragma once
#include "Core.h"

#include "GameObject.h"
#include <iostream>

class TextGO: public GameObject{
public:
    TextGO(const int x, const int y, wchar_t* Text);
//    void Init() override;
//    void Update() override;
    void Render() override;
//    void Destroy() override;
//    bool IsDestroyed() override;
    
private:
    wchar_t* mText;
};

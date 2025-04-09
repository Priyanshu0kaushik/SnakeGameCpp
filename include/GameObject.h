#pragma once
#include <string>

class World;
class GameObject{
  
public:
    GameObject(int x, int y);
    virtual void Init();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void Destroy();
    virtual bool IsDestroyed();
    std::string ObjName;

    virtual ~GameObject() = default;

protected:
    int xPos, yPos;
    bool mIsDestroyed;
};

#pragma once

class World;
class GameObject{
  
public:
    GameObject(int x, int y);
    virtual void Init();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void Destroy();
    virtual bool IsDestroyed();
protected:
    int xPos, yPos;
    bool mIsDestroyed;
};

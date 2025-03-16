#pragma once

class GameObject{
  
public:
    virtual void Update();
    virtual void Render();
    virtual void Destroy();
    virtual bool IsDestroyed();
};

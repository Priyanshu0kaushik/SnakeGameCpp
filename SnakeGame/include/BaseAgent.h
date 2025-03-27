#pragma once

class BaseAgent{
  
public:
    enum class Direction
    {
        NONE = -1,
        UP = 0,
        DOWN = 1,
        RIGHT = 2,
        LEFT = 3
        
    };
    virtual void KeyDown(int Key);
    virtual int GetNextDirection() = 0;
};

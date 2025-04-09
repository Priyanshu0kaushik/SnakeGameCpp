#pragma once
#include <queue>
#include "AStar.h"
#include "BaseAgent.h"


class AiAgent : public BaseAgent{
public:
    int GetNextDirection() override;
private:
    std::pair<int, int> mPreviousTilePos;
    AStar* mAStarAgent = new AStar();
    std::vector<std::pair<int, int>> mPath;
};


#pragma once
#include <vector>
#include <limits>

struct Node {
    int x, y;
    int g = 9999;
    int h = 0;
    int f = 0;
    Node* parent = nullptr;

    bool operator>(const Node& other) const { return f > other.f; }
};

struct CompareNode {
    bool operator()(const Node* a, const Node* b) const {
        return a->f > b->f;
    }
};

class AStar {
public:
    std::vector<std::pair<int, int>> FindPath(std::pair<int, int> startPos, std::pair<int, int> goalPos, bool tiles[], std::vector<std::pair<int, int>> snakeBody);
private:
    int Heuristic(std::pair<int, int> a, std::pair<int, int> b);
    std::vector<std::pair<int, int>> GetNeighbors(Node& node, bool tiles[]);
    Node* GetNodeAt(int x, int y, std::vector<Node>& nodes);
};

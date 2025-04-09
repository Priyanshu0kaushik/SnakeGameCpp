#include "AStar.h"
#include "Core.h"
#include "math.h"
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

int AStar::Heuristic(std::pair<int, int> a, std::pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

std::vector<std::pair<int, int>> AStar::FindPath(std::pair<int, int> startPos, std::pair<int, int> goalPos, bool tiles[], std::vector<std::pair<int, int>> snakeBody) {
    std::vector<Node> nodes;
    std::priority_queue < Node*, std::vector<Node*>, CompareNode > openList;
    std::vector<Node*> closedList;

    for (int i = 0; i < WORLD_HEIGHT; i++) {
        for (int j = 0; j < WORLD_WIDTH; j++) {
            if (tiles[i * WORLD_WIDTH + j]) continue;
            
            bool isSnakeBody = std::find(snakeBody.begin(), snakeBody.end(), std::make_pair(i, j)) != snakeBody.end();
            if (isSnakeBody) continue;
            Node node;
            node.x = i;
            node.y = j;
            node.h = Heuristic({i, j}, goalPos);
            nodes.push_back(node);
        }
    }

    Node* startNode = GetNodeAt(startPos.first, startPos.second, nodes);
    Node* endNode = GetNodeAt(goalPos.first, goalPos.second, nodes);
    
    if (!startNode || !endNode) return {};

    startNode->g = 0;
    startNode->f = startNode->h;
    
    openList.push(startNode);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();
        
        if (current == endNode) break;

        closedList.push_back(current);
        
        for (auto& neighborPos : GetNeighbors(*current, tiles)) {
            Node* neighbor = GetNodeAt(neighborPos.first, neighborPos.second, nodes);
            if (!neighbor || std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end()) continue;
            
            int tentativeG = current->g + 1;
            if (tentativeG < neighbor->g) {
                neighbor->parent = current;
                neighbor->g = tentativeG;
                neighbor->f = neighbor->g + neighbor->h;
                openList.push(neighbor);
            }
        }
    }

    std::vector<std::pair<int, int>> path;
    Node* pathNode = endNode;
    while (pathNode) {
        path.push_back({pathNode->x, pathNode->y});
        pathNode = pathNode->parent;
    }
    std::reverse(path.begin(), path.end());
    
    return path;
}

std::vector<std::pair<int, int>> AStar::GetNeighbors(Node& node, bool tiles[]) {
    std::vector<std::pair<int, int>> neighbors;
    std::vector<std::pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};

    for (auto& dir : directions) {
        int nx = node.x + dir.first;
        int ny = node.y + dir.second;
        if (nx >= 0 && nx < WORLD_HEIGHT && ny >= 0 && ny < WORLD_WIDTH && !tiles[nx * WORLD_WIDTH + ny]) {
            neighbors.emplace_back(nx, ny);
        }
    }
    
    return neighbors;
}

Node* AStar::GetNodeAt(int x, int y, std::vector<Node>& nodes) {
    for (auto& node : nodes) {
        if (node.x == x && node.y == y) return &node;
    }
    return nullptr;
}

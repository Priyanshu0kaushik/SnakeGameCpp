#pragma once
#include <vector>

struct Node {
	int x, y;
	int g = 1;
	int h = 0;
	int f = g + h;
};

class AStar {
public:

	std::vector<std::pair<int, int>> FindPath(std::pair<int,int> startPos, std::pair<int, int> goalPos, bool tiles[], std::vector<std::pair<int, int>> snakeBody);
	Node MakeNode(std::pair<int, int> pos, int h = 0);
};
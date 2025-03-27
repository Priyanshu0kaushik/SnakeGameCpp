#include "AStar.h"


std::vector<std::pair<int, int>> AStar::FindPath(std::pair<int, int> startPos, std::pair<int, int> goalPos, bool tiles[], std::vector<std::pair<int, int>> snakeBody)
{
	Node startNode, endNode;
	std::vector<Node> nodes;
	//for(std::pair<int,int> tile in )
	
}

Node AStar::MakeNode(std::pair<int, int> pos, int h) {
	Node node = Node();
	node.x = pos.first;
	node.x = pos.second;
	return node;

}
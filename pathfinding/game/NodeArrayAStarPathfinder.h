#pragma once

#include "AStarPathfinder.h"
#include "NodeRecord.h"
#include <vector>


class Path;
class Graph;
class Grid;


class NodeArrayAStarPathfinder :public AStarPathfinder
{
public:
	NodeArrayAStarPathfinder(Graph* pGraph);
	~NodeArrayAStarPathfinder();

	//virtual Path findPath(Node* pFrom, Node* pTo);

private:
};


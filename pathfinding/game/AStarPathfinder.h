#pragma once

#include "GridPathfinder.h"
#include "NodeRecord.h"
#include <vector>
#include <mutex>

class Path;
class Graph;
class Grid;

using namespace std;

class AStarPathfinder :public GridPathfinder
{
public:
	AStarPathfinder(Graph* pGraph);
	~AStarPathfinder();

	virtual Path findPath(Node* pFrom, Node* pTo);

protected:
	float getHeuristicCost(Node* pFrom, Node* pTo);
	mutex mMutex;
};

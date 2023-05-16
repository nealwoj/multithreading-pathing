#pragma once

#include "GridPathfinder.h"
#include "NodeRecord.h"
#include <vector>


class Path;
class Graph;
class Grid;

class DijkstraPathfinder :public GridPathfinder
{
public:
	DijkstraPathfinder(Graph* pGraph);
	~DijkstraPathfinder();

	virtual Path findPath(Node* pFrom, Node* pTo);

private:

};

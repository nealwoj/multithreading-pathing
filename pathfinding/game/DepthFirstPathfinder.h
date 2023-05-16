#pragma once

#include "GridPathfinder.h"
#include <vector>
#include <list>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class DepthFirstPathfinder:public GridPathfinder
{
public:
	DepthFirstPathfinder( Graph* pGraph );
	~DepthFirstPathfinder();

	Path findPath(Node* pFrom, Node* pTo) { return Path(); };//make sure to delete the path when you are done!

	bool update(unsigned int numIterations = 1);

private:
	Node* mpCurrentNode = nullptr;
	Node* mpFromNode = nullptr;
	Node* mpToNode = nullptr;
	std::list<Node*> mNodesToVisit;
	Path* mpPath = nullptr;
	bool mToNodeAdded = false;
};


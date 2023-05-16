#include "DepthFirstPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

DepthFirstPathfinder::DepthFirstPathfinder( Graph* pGraph )
:GridPathfinder(dynamic_cast<GridGraph*>(pGraph) )
{
}

DepthFirstPathfinder::~DepthFirstPathfinder()
{
}
/*
void DepthFirstPathfinder::findPath(Node* pFrom, Node* pTo)
{
	mTimeElapsed = 0;

	mpFromNode = pFrom;
	mpToNode = pTo;

	mNodesToVisit.push_front(pFrom);

	mpPath = new Path;

#ifdef VISUALIZE_PATH
	mPath.clear();
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	mpCurrentNode = nullptr;
	mToNodeAdded = false;
}

bool DepthFirstPathfinder::update(unsigned int numIterations)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	while (mpCurrentNode != mpToNode && mNodesToVisit.size() > 0)
	{
		//get current node from front of list
		mpCurrentNode = mNodesToVisit.front();
		//remove node from list
		mNodesToVisit.pop_front();
		//add Node to Path
		mPath.addNode(mpCurrentNode);

		mToNodeAdded = false;

		//get the Connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(mpCurrentNode->getId());

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for (unsigned int i = 0; i < connections.size(); i++)
		{
			Connection* pConnection = connections[i];
			Node* pTempToNode = connections[i]->getToNode();
			if (!mToNodeAdded &&
				!mpPath->containsNode(pTempToNode) &&
				find(mNodesToVisit.begin(), mNodesToVisit.end(), pTempToNode) == mNodesToVisit.end())
			{
				mNodesToVisit.push_front(pTempToNode);//uncomment me for depth-first search
				//nodesToVisit.push_back( pTempToNode );//uncomment me for breadth-first search
				if (pTempToNode == mpToNode)
				{
					mToNodeAdded = true;
				}
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pTempToNode);
#endif

			}
		}
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed += gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mPath = *mpPath;
#endif
	return false;

}*/


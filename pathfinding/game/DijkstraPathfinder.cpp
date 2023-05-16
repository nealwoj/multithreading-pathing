#include "DijkstraPathfinder.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Node.h"

#include <Game.h>
#include <PerformanceTracker.h>

#include <algorithm>

using namespace std;

DijkstraPathfinder::DijkstraPathfinder(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
}

DijkstraPathfinder::~DijkstraPathfinder()
{
}

Path DijkstraPathfinder::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	vector<NodeRecord> openList;
	vector<NodeRecord> closedList;

	openList.push_back(NodeRecord(pFrom, nullptr, 0.0f));

#ifdef VISUALIZE_PATH
	mPath.clear();
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	while (openList.size() > 0)
	{
		//sort the openList
		sort(openList.begin(), openList.end(),isGreater);
		//the shortest cost so far will be on the end
		NodeRecord current = openList.back();
		//remove the node from the end
		openList.pop_back();

		//get the Connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(current.pNode->getId());

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for (unsigned int i = 0; i < connections.size(); i++)
		{
			Connection* pConnection = connections[i];
			Node* pToNode = pConnection->getToNode();

			//create NodeRecord from ToNode
			NodeRecord connectionRecord(pToNode, current.pNode, current.totalCost + pConnection->getCost());

			//see if connectionRecord is in closedList
			auto it = NodeRecord::getExistingRecord(closedList, connectionRecord);
			if (it != closedList.end())
			{
				//compare costs
				if (connectionRecord.totalCost < it->totalCost)
				{
					//found a cheaper route - remove NodeRecord from closed list - will get placed in open list with lower cost
					closedList.erase(it);
				}
				else
				{
					//on the closed list but we are not shorter - just skip to end of for loop
					continue;
				}
			}

			//check to see if connectionRecord is in openList
			it = NodeRecord::getExistingRecord(openList, connectionRecord);
			if (it != openList.end())
			{
				//compare costs
				if (connectionRecord.totalCost < it->totalCost)
				{
					//found a cheaper route - overwrite fields in existing record
					it->pFrom = connectionRecord.pFrom;
					it->totalCost = connectionRecord.totalCost;
				}
			}
			else
			{
				//connectionRecord is new to the openList
				openList.push_back(connectionRecord);
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pToNode);
#endif
			}
		}//end for(connections)
		//add current to closed list
		closedList.push_back(current);
		if (current.pNode == pTo)
			break;

	}//end while(openList not empty)

	//make a path
	Path path = NodeRecord::createPath(pFrom, pTo, closedList);;

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mPath = path;
#endif
	return path;

}


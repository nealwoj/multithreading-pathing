#include "NodeRecord.h"
#include "Node.h"
#include <vector>

using namespace std;

NodeRecord::NodeRecord(Node* pTheNode, Node* pTheFrom, float cost, float heuristic, Status theStatus)
	:pNode(pTheNode)
	, pFrom(pTheFrom)
	, totalCost(cost)
	, heuristicCost(heuristic)
	, listStatus(theStatus)
{
}


bool NodeRecord::operator<(const NodeRecord& rhs) const
{
	return (totalCost + heuristicCost < rhs.totalCost + rhs.heuristicCost);
}

bool NodeRecord::operator>(const NodeRecord& rhs) const
{
	return (totalCost + heuristicCost > rhs.totalCost + rhs.heuristicCost);
}

bool NodeRecord::operator==(const NodeRecord& rhs) const
{
	return (pNode->getId() == rhs.pNode->getId());
}

bool isGreater(const NodeRecord& lhs, const NodeRecord& rhs)
{
	return lhs.totalCost + lhs.heuristicCost > rhs.totalCost + rhs.heuristicCost;
};

std::vector<NodeRecord>::iterator NodeRecord::getExistingRecord(std::vector<NodeRecord>& theList, const NodeRecord& theRecord)
{
	return find(theList.begin(), theList.end(), theRecord);
}

Path NodeRecord::createPath(Node* pFrom, Node* pTo, std::vector<NodeRecord>& theList)
{
	Path path;
	vector<Node*> temp;

	//find the To node
	auto endIt = getExistingRecord(theList, NodeRecord(pTo, nullptr, 0.0f));
	if (endIt != theList.end())
	{
		auto currentIt = endIt;
		Node* pCurrent = endIt->pNode;
		//found it - means we found a path
		while (currentIt != theList.end())
		{
			temp.push_back(pCurrent);

			if (currentIt->pFrom == nullptr)
				break;

			currentIt = getExistingRecord(theList, NodeRecord(currentIt->pFrom, nullptr, 0.0f));

			if (currentIt != theList.end())
			{
				pCurrent = currentIt->pNode;
			}
		}
	}

	//build the actual path in reverse order
	for (auto it = temp.rbegin(); it != temp.rend(); ++it)
	{
		path.addNode(*it);
	}
	return path;
}


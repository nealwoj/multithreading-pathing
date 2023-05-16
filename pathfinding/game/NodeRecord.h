#pragma once

#include "Path.h"
#include <Trackable.h>

class Node;


struct NodeRecord:public Trackable
{
	enum Status{ UNVISITED, CLOSED, OPEN };
	Node* pNode = nullptr;
	Node* pFrom = nullptr;
	float totalCost = 0.0f;
	float heuristicCost = 0.0f;
	NodeRecord::Status listStatus = UNVISITED;

	bool operator<(const NodeRecord& rhs) const;
	bool operator>(const NodeRecord& rhs) const;
	bool operator==(const NodeRecord& rhs) const;

	NodeRecord(Node* pTheNode, Node* pTheFrom, float cost, float heuristic = 0.0f, Status theStatus = UNVISITED);
	NodeRecord() {};

	static std::vector<NodeRecord>::iterator getExistingRecord(std::vector<NodeRecord>& theList, const NodeRecord& theRecord);
	static Path createPath(Node* pFrom, Node* pTo, std::vector<NodeRecord>& theList);

};

bool isGreater(const NodeRecord& lhs, const NodeRecord& rhs);



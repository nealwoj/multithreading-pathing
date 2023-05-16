#include "NodeArray.h"
#include "Node.h"

NodeArray::NodeArray(unsigned int numEntries)
	:mNumRecords(numEntries)
{
	mpRecords = new NodeRecord[numEntries];
}

NodeArray::~NodeArray()
{
	delete[] mpRecords;
}

void NodeArray::reset()
{
	for (unsigned int i = 0; i < mNumRecords; i++)
	{
		mpRecords[i].listStatus = NodeRecord::UNVISITED;
	}
	mNumOpenRecords = 0;
}

bool NodeArray::isOnClosedList(unsigned int nodeID) const
{
	return mpRecords[nodeID].listStatus == NodeRecord::CLOSED;
}

bool NodeArray::isOnOpenList(unsigned int nodeID) const
{
	return mpRecords[nodeID].listStatus == NodeRecord::OPEN;
}

void NodeArray::addToOpenList(const NodeRecord& record)
{
	unsigned int id = record.pNode->getId();
	mpRecords[id] = record;
	if (mpRecords[id].listStatus != NodeRecord::OPEN)
	{
		mpRecords[id].listStatus = NodeRecord::OPEN;
		mNumOpenRecords++;
	}
}

void NodeArray::addToClosedList(const NodeRecord& record)
{
	unsigned int id = record.pNode->getId();
	mpRecords[id] = record;
	mpRecords[id].listStatus = NodeRecord::CLOSED;
}

const NodeRecord& NodeArray::getNodeRecord(unsigned int nodeID) const
{
	return mpRecords[nodeID];
}

NodeRecord& NodeArray::removeFromOpenList(unsigned int nodeID)
{
	mpRecords[nodeID].listStatus = NodeRecord::UNVISITED;
	mNumOpenRecords--;
	return mpRecords[nodeID];
}

void NodeArray::modifyNodeRecord(const NodeRecord& record)
{
	//unsigned int id = record.pNode->getId();
	//if( mpRecords[id].listStatus == NodeRecord::OPEN && record.listStatus)
}

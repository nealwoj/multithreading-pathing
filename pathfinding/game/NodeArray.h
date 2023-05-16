#pragma once

#include <Trackable.h>
#include "NodeRecord.h"


class NodeArray :public Trackable
{
public:
	explicit NodeArray(unsigned int numEntries);
	~NodeArray();

	void reset();//set the status of all Records to Unvisited
	bool isOnClosedList(unsigned int nodeID) const;
	bool isOnOpenList(unsigned int nodeID) const;
	void addToOpenList(const NodeRecord& record);
	void addToClosedList(const NodeRecord& record);
	const NodeRecord& getNodeRecord(unsigned int nodeID) const;
	NodeRecord& removeFromOpenList(unsigned int nodeID);
	void modifyNodeRecord(const NodeRecord& record);

	unsigned int getNumOpenNodes() const { return mNumOpenRecords; };
private:
	NodeRecord* mpRecords=nullptr;
	unsigned int mNumRecords = 0;
	unsigned int mNumOpenRecords = 0;

};

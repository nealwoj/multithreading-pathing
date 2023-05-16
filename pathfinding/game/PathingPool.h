#pragma once

#include <Trackable.h>
#include <vector>
#include <thread>
#include <mutex>

#include "CircularQueue.h"
#include "Path.h"

using namespace std;

struct PathRequest
{
	Node* pFromNode;
	Node* pToNode;
	int mID;

	PathRequest()
	{
		pFromNode = NULL;
		pToNode = NULL;
	}

	PathRequest(Node* pFrom, Node* pTo, int id)
	{
		pFromNode = pFrom;
		pToNode = pTo;
		mID = id;
	}
};

class PathingPool : public Trackable
{
public:
	PathingPool();
	~PathingPool() { cleanup(); };

	void init();
	void cleanup();
	void update();

	void addThread();
	void subtractThread();
	void addPath(Path path) { mPathPools.push_back(path); };
	void addRequest(PathRequest request);

	int getThreadCount() { return mThreadCount; };
	int getRequestCount() { return mRequestCount; };
	int getProcessedCount() { return mProcessedCount; };
	Path getPoolIndex(int index) { return mPathPools[index]; };
	Path getRandomPool() { return mPathPools[rand() % mPathPools.size()]; };

private:
	CircularQueue<PathRequest>* mpQueue;
	vector<Path> mPathPools;
	vector<thread> mThreads;
	int mThreadCount, mRequestCount, mProcessedCount;
};
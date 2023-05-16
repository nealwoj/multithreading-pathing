#include "PathingPool.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "GridGraph.h"
#include "Node.h"

#define GAME_APP (dynamic_cast<GameApp*>(gpGame))

auto lambda_function = [](Node* pFrom, Node* pTo)
{
	GAME_APP->getPathfinder()->findPath(pFrom, pTo);
};

PathingPool::PathingPool()
{
	init();
}

void PathingPool::init()
{
	mThreadCount = 1;
	mRequestCount = 0;
	mProcessedCount = 0;
	mPathPools.clear();
	mThreads.clear();
	mpQueue = new CircularQueue<PathRequest>(MAX_POOL_SIZE);
}

void PathingPool::cleanup()
{
	for (int i = 0; i < (int)mThreads.size(); i++)
	{
		mThreads[i].join();
	}

	mThreadCount = 0;
	mRequestCount = 0;
	mProcessedCount = 0;

	mPathPools.clear();
	mThreads.clear();

	mpQueue->reset();
	delete mpQueue;
	mpQueue = NULL;
}

void PathingPool::update()
{
	//mRequestCount = 0;

	for (int i = 0; i < (int)mThreads.size(); i++)
	{
		mThreads[i].join();
	}

	mThreads.clear();

	for (int i = 0; i < mThreadCount; i++)
	{
		PathRequest request;
		if (mpQueue->popFront(request))
		{
			mThreads.push_back(thread(lambda_function, request.pFromNode, request.pToNode));
			mRequestCount++;
		}
	}
}

void PathingPool::addThread()
{
	mThreadCount++;
}

void PathingPool::subtractThread()
{
	mThreadCount--;
}

void PathingPool::addRequest(PathRequest request)
{
	mpQueue->pushBack(request);
	mRequestCount++;
}
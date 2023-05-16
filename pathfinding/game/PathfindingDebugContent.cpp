#include "PathfindingDebugContent.h"
#include "GridPathfinder.h"
#include "Path.h"
#include "GameApp.h"
#include "PathingPool.h"
#include <sstream>

using namespace std;

PathfindingDebugContent::PathfindingDebugContent()
{
}

string PathfindingDebugContent::getDebugString()
{
	stringstream theStream;

	GameApp* pGameApp = dynamic_cast<GameApp*>(gpGame);
	GridPathfinder* pathfinder = pGameApp->getPathfinder();
	PathingPool* pool = pGameApp->getPool();

	theStream << "  Elapsed Time:" << pathfinder->mTimeElapsed;
	//theStream << "  Current Time:" << gpGame->getCurrentTime();
	theStream << "  Threads:" << pool->getThreadCount();
	//theStream << "  Requests:" << pGameApp->getPool()->getRequestCount();
	theStream << "  Requests Processed / Second:" << pathfinder->mTimeElapsed / pGameApp->getPool()->getRequestCount();

	return theStream.str();
}


#pragma once

/*Game - class to hold all game related info.

Dean Lawson
Champlain College
2011
*/

#include "Game.h"

//forward declarations
class PathingPool;
class GraphicsBuffer;
class Sprite;
class KinematicUnit;
class GameMessageManager;
class Grid;
class GridVisualizer;
class GridGraph;
class GridPathfinder;
class DebugDisplay;

const float LOOP_TARGET_TIME = 41.67f;//how long should each frame of execution take? 30fps = 33.3ms/frame

const IDType BACKGROUND_BUFFER_ID = 0;

const int MAX_POOL_SIZE = 1000;

class GameApp: public Game
{
public:
	GameApp();
	~GameApp();

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	//accessors
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };
	inline GridPathfinder* getPathfinder() { return mpPathfinder; };
	inline Grid* getGrid() { return mpGrid; };
	inline GridGraph* getGridGraph() { return mpGridGraph; };
	
	inline PathingPool* getPool() { return mpPathingPool; };

private:
	GameMessageManager* mpMessageManager;
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	GridGraph* mpGridGraph;
	DebugDisplay* mpDebugDisplay;
	GridPathfinder* mpPathfinder;

	PathingPool* mpPathingPool;
	int mCount;
};

#define GRID dynamic_cast<GameApp*>(gpGame)->getGrid();
#define GAMEAPP (dynamic_cast<GameApp*>(gpGame));
#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Vector2D.h"
#include "Grid.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Path.h"
#include "DepthFirstPathfinder.h"
#include "DijkstraPathfinder.h"
#include "AStarPathfinder.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"

#include <InputSystem.h>
#include <fstream>
#include <vector>

#include "PathingPool.h"

const GraphicsBufferID BACKGROUND_ID = "Background";
const int GRID_SIZE_X = 32;
const int GRID_SIZE_Y = 32;
const std::string gFileName = "..\\pathgrid.txt";

GameApp::GameApp()
:mpMessageManager(NULL)
,mpGrid(NULL)
,mpGridGraph(NULL)
,mpPathfinder(NULL)
,mpDebugDisplay(NULL)
{
}

GameApp::~GameApp()
{
	cleanup();
}

bool GameApp::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	mpMessageManager = new GameMessageManager();

	GraphicsSystem* pGraphicsSystem = getGraphicsSystem();

	//create and load the Grid, GridBuffer, and GridVisualizer
	mpGrid = new Grid(pGraphicsSystem->getDisplayWidth(), pGraphicsSystem->getDisplayHeight(), GRID_SIZE_X, GRID_SIZE_Y);
	mpGridVisualizer = new GridVisualizer( mpGrid );
	std::ifstream theStream( gFileName );
	mpGrid->load( theStream );

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mpGrid);
	//init the nodes and connections
	mpGridGraph->init();

	mpPathfinder = new AStarPathfinder(mpGridGraph);

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0.0f, 0.0f, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight() );
	}

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent();
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );

	mpPathingPool = new PathingPool();

	mCount = 0;

	mpMasterTimer->start();
	return true;
}

void GameApp::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

	delete mpGrid;
	mpGrid = NULL;

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	delete mpPathingPool;
	mpPathingPool = NULL;
}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	GraphicsSystem* pGraphicsSystem = getGraphicsSystem();
	//get back buffer
	GraphicsBuffer* pBackBuffer = pGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw( *pBackBuffer );
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	mpPathfinder->drawVisualization(mpGrid, pBackBuffer);
#endif

	mpDebugDisplay->draw( pBackBuffer );

	mpMessageManager->processMessagesForThisframe();

	InputSystem* pInputSystem = getInputSystem();
	pInputSystem->update(mLoopTargetTime);

	if( pInputSystem->isMouseButtonPressed(InputSystem::LEFT) )
	{
		static Vector2D lastPos( 0.0f, 0.0f );
		Vector2D pos = pInputSystem->getCurrentMousePos();
		if( lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY() )
		{
			GameMessage* pMessage = new PathToMessage( lastPos, pos );
			mpMessageManager->addMessage( pMessage, 0 );
			lastPos = pos;
		}
	}

	if (pInputSystem->isKeyPressed(InputSystem::D_KEY))
	{
		delete mpPathfinder;
		mpPathfinder = new DijkstraPathfinder(mpGridGraph);
	}
	else if (pInputSystem->isKeyPressed(InputSystem::A_KEY))
	{
		delete mpPathfinder;
		mpPathfinder = new AStarPathfinder(mpGridGraph);
	}

	//multithreading
	if (pInputSystem->isKeyPressed(InputSystem::PERIOD_KEY))
	{
		mpPathingPool->addThread();
	}

	if (pInputSystem->isKeyPressed(InputSystem::COMMA_KEY))
	{
		if (mpPathingPool->getThreadCount() > 1)
			mpPathingPool->subtractThread();
	}

	if (mCount % 5 == 0)
	{
		//generate random nodes that aren't in blocked terrain
		bool stop = false;
		while (stop == false && mpPathingPool->getRequestCount() < MAX_POOL_SIZE)
		{
			Node* pFrom = mpGridGraph->getNode(rand() % mpGridGraph->getLastID());
			Node* pTo = mpGridGraph->getNode(rand() % mpGridGraph->getLastID());

			if (mpGrid->getValueAtIndex(pFrom->getId()) == 0 && mpGrid->getValueAtIndex(pTo->getId()) == 0)
			{
				//add request to the queue
				PathRequest request(pFrom, pTo, mCount);
				mpPathingPool->addRequest(request);
				stop = true;
			}
		}
	}
	mCount++;

	mpPathingPool->update();

	//should be last thing in processLoop
	Game::processLoop();
}

bool GameApp::endLoop()
{
	return Game::endLoop();
}
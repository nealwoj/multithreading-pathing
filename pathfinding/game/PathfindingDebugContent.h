#pragma once

#include "DebugContent.h"

class GridPathfinder;

class PathfindingDebugContent:public DebugContent
{
public:
	PathfindingDebugContent();
	~PathfindingDebugContent(){};

	std::string getDebugString();

private:
};
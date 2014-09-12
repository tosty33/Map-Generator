#ifndef __ISLAND_GENERATOR_H__
#define __ISLAND_GENERATOR_H__

#include "Map.h"

class IslandGenerator
{
public:
	static bool generate(Map& map);

	IslandGenerator();
	~IslandGenerator();
};

#endif
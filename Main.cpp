#include <iostream>
#include <sstream>
#include "Map.h"

#include "IslandGenerator.h"
#include "MapOutput.h"

using namespace std;

int main()
{
	Map* map = new Map(256);

	for (int i = 0; i < 10; i++)
	{
		IslandGenerator::generate(*map);
		ostringstream ss;
		ss << "map_" << i << ".png";

		MapOutput::saveAsPNG(*map, ss.str());
	}

	MapOutput::saveAsJSON(*map, "map.json");

	cin.get();

	return 0;
}
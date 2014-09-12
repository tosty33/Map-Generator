#include "IslandGenerator.h"

#include "Gradient.h"
#include "Noise.h"

#include "Vec2.h"
#include "Tools.h"

#include <iostream>
using namespace std;

IslandGenerator::IslandGenerator()
{
}


IslandGenerator::~IslandGenerator()
{
}

bool IslandGenerator::generate(Map& map)
{
	map.clearMap();

	int result = rand(0, 100);
	if (result < 20)
	{
		float odst = rand(2.0f, 2.4f);
		Gradient::radialGradient(map, Vec2<int>(map.getSize() / odst, map.getSize() / odst), map.getSize() / rand(1.5f, 1.9f));
		Gradient::radialGradient(map, Vec2<int>(map.getSize() - map.getSize() / odst, map.getSize() - map.getSize() / odst), map.getSize() / rand(1.5f, 1.9f));

		odst = rand(1.6f, 2.0f);
		int result = rand(0, 100);
		if (result < 10)
		{
			Gradient::radialGradient(map, Vec2<int>(map.getSize() - map.getSize() / odst, map.getSize() / odst), map.getSize() / rand(1.7f, 1.9f));
		}
		else if (result < 20)
		{
			Gradient::radialGradient(map, Vec2<int>(map.getSize() / odst, map.getSize() - map.getSize() / odst), map.getSize() / rand(1.7f, 1.9f));
		}
	}
	else if (result < 40)
	{
		float odst = rand(2.2f, 2.4f);
		Gradient::radialGradient(map, Vec2<int>(map.getSize() / odst, map.getSize() - map.getSize() / odst), map.getSize() / rand(1.5f, 1.9f));
		Gradient::radialGradient(map, Vec2<int>(map.getSize() - map.getSize() / odst, map.getSize() / odst), map.getSize() / rand(1.5f, 1.9f));

		odst = rand(1.6f, 2.0f);
		int result = rand(0, 100);
		if (result < 10)
		{
			Gradient::radialGradient(map, Vec2<int>(map.getSize() - map.getSize() / odst, map.getSize() - map.getSize() / odst), map.getSize() / rand(1.7f, 1.9f));
		}
		else if (result < 20)
		{
			Gradient::radialGradient(map, Vec2<int>(map.getSize() / odst, map.getSize() / odst), map.getSize() / rand(1.7f, 1.9f));
		}
	}
	else
	{
		Gradient::radialGradient(map, Vec2<int>(map.getSize() / 2, map.getSize() / 2), map.getSize() / rand(1.4f, 1.6f));
	}

	Noise::perlin(map, 8, 10, 0.4);
	
	for (int i = 0; i < 10; i++)
		map.smooth();

	for (int x = 0; x < map.getSize(); x++)
	{
		for (int y = 0; y < map.getSize(); y++)
		{
			if (map.map[x][y] > 1) map.map[x][y] = 1;
		}
	}

	return true;
}
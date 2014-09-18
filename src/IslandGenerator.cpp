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
	map.clear();

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

	Map tmpMap = map.getSize();

	Noise::perlin(tmpMap, 8, 10, 0.4);
	tmpMap.addValue(0.1f);
	tmpMap.cutValues();
	map.joinWith(tmpMap);

	map.addValue(0.4f);
	map.cutValues();

	map.joinWith(tmpMap);
	map.joinWith(tmpMap);
	map.normalize();
	map.removeSmallIslands();

	for (int i = 0; i < 15; i++)
		map.smooth();


	return true;
}
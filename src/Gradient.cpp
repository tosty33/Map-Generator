#include "Gradient.h"

Gradient::Gradient()
{
}


Gradient::~Gradient()
{
}

bool Gradient::radialGradient(Map& map, Vec2<int> center, int radius)
{
	for (int x = 0; x < map.getSize(); x++)
	{
		for (int y = 0; y < map.getSize(); y++)
		{
			float disX = (center.x - x) * (center.x - x) * 4.0f;
			float disY = (center.y - y) * (center.y - y) * 4.0f;
			float dist = sqrt(disX + disY);

			float tmp = 1.0f - (dist / ((float)radius));
			if (tmp < 0) tmp = 0;
			if (tmp > 1) tmp = 1;

			map.map[x][y] += tmp;

			if (map.map[x][y] < 0) map.map[x][y] = 0.0;
			if (map.map[x][y] > 1) map.map[x][y] = 1.0;
		}
	}

	return true;
}
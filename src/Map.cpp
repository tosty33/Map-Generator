#include "Map.h"
#include <list>

Map::Map(int size = 256)
{
	resizeMap(size);
}


Map::~Map()
{
}

void Map::uncheckTiles()
{
	for (int x = 0; x < size; x++)
	for (int y = 0; y < size; y++)
		map[x][y].selected = false;
}

void Map::recurrentSelect(Vec2<int> startPos, float minValue, float maxValue)
{
	int x = startPos.x, y = startPos.y;

	list<Vec2<int>> l;
	l.push_back(startPos);

	while (!l.empty())
	{
		Vec2<int> tmp = l.front();
		x = tmp.x, y = tmp.y;
		l.pop_front();

		if (map[x][y].selected)
			continue;

		if (map[x][y] >= minValue && map[x][y] <= maxValue)
			map[x][y].selected = true;
		else
			continue;

		if (x > 0 && !map[x - 1][y].selected  && map[x - 1][y] >= minValue)
			l.push_back(Vec2<int>(x - 1, y));

		// Right
		if (x < size && !map[x + 1][y].selected && map[x + 1][y] >= minValue)
			l.push_back(Vec2<int>(x + 1, y));

		// Top
		if (y > 0 && !map[x][y - 1].selected && map[x][y - 1] >= minValue)
			l.push_back(Vec2<int>(x, y - 1));

		// Bottom
		if (y < size && !map[x][y + 1].selected && map[x][y + 1] >= minValue)
			l.push_back(Vec2<int>(x, y + 1));
	}
}

void Map::reverseSelection()
{
	for (int x = 0; x < size; x++)
	for (int y = 0; y < size; y++)
		map[x][y].selected = !map[x][y].selected;
}

void Map::setSelection(float value)
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (map[x][y].selected)
				map[x][y] = value;
		}
	}
}

void Map::removeSmallIslands()
{
	uncheckTiles();

	Vec2<int> startTile(floor(size / 2), floor(size / 2));
	recurrentSelect(startTile, 0.0f, 1.0f);
	reverseSelection();
	setSelection(-1.0f);

	uncheckTiles();
}

bool Map::joinWith(const Map& joinMap)
{
	auto joinTiles = joinMap.getTiles();

	if (size != joinMap.getSize())
	{
		cout << "Error: joined map need to be the same size to be joined." << endl;
		return false;
	}

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			map[x][y] = (map[x][y].value + joinTiles[x][y].value);
		}
	}

	normalize();
	return true;
}

void Map::multiply(float value)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			map[x][y] += 1.0f;
		}
	}

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			map[x][y] = map[x][y] * value;
		}
	}

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			map[x][y] -= 1.0f;
		}
	}
}

void Map::reverse()
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			map[x][y] *= -1;
		}
	}
}

void Map::clear()
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			map[x][y] = 0.0;
		}
	}
}

bool Map::normalize()
{
	float min = 0.0f, max = 0.0f;

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (map[x][y] < min)
				min = map[x][y].value;

			if (map[x][y] > max)
				max = map[x][y].value;
		}
	}

	if (max == 0.0f || min == max)
		return false;

	if (min < 0.0f)
	{
		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				map[x][y].value += -min;
			}
		}
		min += -min;

		// We need to measure the min and max values again
		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				if (map[x][y] < min)
					min = map[x][y].value;

				if (map[x][y] > max)
					max = map[x][y].value;
			}
		}
	}

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			map[x][y].value = ((map[x][y].value * 2.0f) / max) - 1.0f;
		}
	}

	return true;
}

void Map::resizeMap(int newSize)
{
	map.clear();
	size = newSize;

	for (int i = 0; i < newSize; i++)
	{
		vector<Tile> tileVec;

		for (int j = 0; j < newSize; j++)
			tileVec.push_back(Tile());

		map.push_back(tileVec);
	}
}

void Map::addValue(float value)
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			map[x][y] += value;
		}
	}
}

void Map::cutValues()
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (map[x][y] > 1.0f)
				map[x][y] = 1.0f;
			else if (map[x][y] < -1.0f)
				map[x][y] = -1.0f;
		}
	}
}

void Map::smooth()
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (x > 0 && y > 0 && x < size - 1 && y < size - 1)
			{
				int horiz = 0;
				int vert = 0;
				int count = 0;
				if (x > 0)
				{
					if (map[x - 1][y] >= 0.0)
					{
						count++;
						horiz++;
					}
				}

				if (x < size - 1)
				{
					if (map[x + 1][y] >= 0.0)
					{
						count++;
						horiz++;
					}
				}

				if (y > 0)
				{
					if (map[x][y - 1] >= 0.0)
					{
						count++;
						vert++;
					}
				}

				if (y < size - 1)
				{
					if (map[x][y + 1] >= 0.0)
					{
						count++;
						vert++;
					}
				}

				if (map[x][y] >= 0.0)
				{
					if (count < 2 || vert == 0 || horiz == 0)
						map[x][y] = -1.0;
				}
				else if ((horiz == 2 && vert == 1) || (horiz == 2 && vert == 0) || (horiz == 2 && vert == 2))
				{
					map[x][y] = map[x + 1][y];
				}
				else if ((horiz == 1 && vert == 2) || (horiz == 0 && vert == 2))
				{
					map[x][y] = map[x][y + 1];
				}
			}
			else
				map[x][y] = -1.0;
		}
	}
}
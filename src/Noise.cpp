#include "Noise.h"

Noise::Noise()
{
}


Noise::~Noise()
{
}

bool Noise::perlin(Map& map, int octaves = 8, float frequency = 10.0f, float amplitude = 0.5f)
{
	Perlin* noise = new Perlin(octaves, frequency, amplitude, rand());
	for (int x = 0; x < map.getSize(); x++)
	{
		for (int y = 0; y < map.getSize(); y++)
		{
			map.map[x][y] = noise->Get((float)x / (float)map.getSize(), (float)y / (float)map.getSize());
		}
	}

	return true;
}
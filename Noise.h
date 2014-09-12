#ifndef __NOISE_H__
#define __NOISE_H__

#include "Map.h"

// Noise classes
#include "Perlin.h"

class Noise
{
public:
	static bool perlin(Map& map, int octaves, float frequency, float amplitude);

	Noise();
	~Noise();

private:
};

#endif
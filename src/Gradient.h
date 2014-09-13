#ifndef __GRADIENT_H__
#define __GRADIENT_H__

#include "Map.h"
#include "Vec2.h"

class Gradient
{
public:
	static bool radialGradient(Map& _map, Vec2<int> center, int radius);

	Gradient();
	~Gradient();

private:
};

#endif
#include "Tile.h"

ostream& operator<<(ostream& out, const Tile& tile)
{
	out << tile.value;
	return out;
}

Tile::Tile()
{
}


Tile::~Tile()
{
}

/* Temporary solution! */
int Tile::getItemId()
{
	if (value < 0.0)
		return 4665;
	else if (value < 0.16)
		return 231;
	else if (value < 0.7)
		return 4530;
	else
		return 919;
}

/* Temporary solution! */
Color Tile::getColor()
{
	unsigned char r, g, b;
	r = g = b = value * 255;

	if (value < 0.0)
	{
		r = g = 0, b = 255;
	}
	else if (value < 0.16)
	{
		r = 255, g = 255, b = 102;
	}
	else if (value < 0.7)
	{
		r = 0, g = 255, b = 0;
	}
	else
	{
		r = 90, g = 90, b = 90;
	}

	return Color(r, g, b);
}
#include "MapOutput.h"

#include "lodepng.h"

#include <fstream>

bool MapOutput::saveAsLUA(const Map& map, string filename)
{
	return true;
}

bool MapOutput::saveAsJSON(const Map& map, string filename)
{
	int size = map.getSize();

	fstream file;
	file.open(filename.c_str(), ios::trunc | ios::out);

	if (!file.is_open())
		return false;

	file << "[\n";

	for (unsigned y = 0; y < size; y++)
	{
		file << "	[";
		for (unsigned x = 0; x < size; x++)
		{
			file << "[";
			file << round(map.map[x][y].value * 100) / 100;;
			file << "]";

			if (x != size - 1)
				file << ", ";
		}
		file << "]";
		if (y != size - 1)
			file << ",";

		file << "\n";
	}

	file << "]";
	file.close();

	return true;
}

bool MapOutput::saveAsPNG(const Map& map, string filename)
{
	int size = map.getSize();
	auto tiles = map.map;

	std::vector<unsigned char> out;
	out.resize(size * size * 4);

	for (unsigned y = 0; y < size; y++)
	for (unsigned x = 0; x < size; x++)
	{
		out[4 * size * y + 4 * x + 0] = tiles[x][y].getColor().r;
		out[4 * size * y + 4 * x + 1] = tiles[x][y].getColor().g;
		out[4 * size * y + 4 * x + 2] = tiles[x][y].getColor().b;
		out[4 * size * y + 4 * x + 3] = 255;
	}

	if (lodepng::encode(filename, out, size, size) != 0)
		return false;

	return true;
}
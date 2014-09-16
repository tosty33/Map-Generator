#ifndef __MAP_OUTPUT_H__
#define __MAP_OUTPUT_H__

#include "Map.h"

#include <string>
using namespace std;

class MapOutput
{
public:
	static bool saveAsJSON(const Map& map, string filename);
	static bool saveAsPNG(const Map& map, string filename, bool grayscale = false);
	static bool saveAsLUA(const Map& map, string filename);
	static bool saveAsOTBM(const Map& map, string filename);

	MapOutput() {};
	~MapOutput() {};
};

#endif
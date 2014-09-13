#ifndef __MAP_H__
#define __MAP_H__

#include "Tile.h"

#include <vector>
#include <string>

using namespace std;

class Map
{
public:
	Map(int size);
	~Map();

	void clearMap();
	void resizeMap(int newSize);

	void smooth();

	// Saving map
	bool saveAsPNG(string filename);
	bool saveAsJSON(string filename);
	
	// Get/set
	inline int getSize() const { return size; }

	// Friends
	friend class Gradient;
	friend class IslandGenerator;
	friend class Noise;
	friend class MapOutput;

private:
	vector<vector<Tile>> map;
	int size;
};

#endif
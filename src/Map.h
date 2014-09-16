#ifndef __MAP_H__
#define __MAP_H__

#include "Tile.h"

#include <vector>
#include <string>

using namespace std;

class Map
{
public:
	// Friend declarations
	friend Map* multiplyMaps(const Map& map1, const Map& map2);
	friend class Gradient;
	friend class IslandGenerator;
	friend class Noise;
	friend class MapOutput;

	// Constructors / destructors
	Map(int size);
	~Map();

	bool joinWith(const Map& joinMap);
	void multiply(float value);

	void clearMap();
	bool normalize();
	void resizeMap(int newSize);

	void smooth();

	// Saving map
	bool saveAsPNG(string filename);
	bool saveAsJSON(string filename);
	
	// Get/set
	inline vector<vector<Tile>> getTiles() const { return map; }
	inline int getSize() const { return size; }
private:
	vector<vector<Tile>> map;
	int size;
};

#endif
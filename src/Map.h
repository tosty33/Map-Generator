#ifndef __MAP_H__
#define __MAP_H__

#include "Tile.h"

#include "Vec2.h"
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

	void Map::uncheckTiles();
	void recurrentSelect(Vec2<int> startPos, float minValue = 0.0f, float maxValue = 1.0f);
	void reverseSelection();
	void setSelection(float value);
	void removeSmallIslands();

	bool joinWith(const Map& joinMap);
	void multiply(float value);

	void reverse();
	void clear();
	bool normalize();
	void resizeMap(int newSize);

	void addValue(float value);
	void cutValues();

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
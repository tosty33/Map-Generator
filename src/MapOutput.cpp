#include "MapOutput.h"

#include "lodepng.h"

#include <fstream>

bool MapOutput::saveAsLUA(const Map& map, string filename)
{
	int size = map.getSize();

	fstream file;
	file.open(filename.c_str(), ios::trunc | ios::out);

	if (!file.is_open())
		return false;

	file << "{\n";

	for (unsigned y = 0; y < size; y++)
	{
		file << "	{";
		for (unsigned x = 0; x < size; x++)
		{
			file << round(map.map[x][y].value * 100) / 100;
			if (x != size - 1)
				file << ", ";
		}
		file << "}";
		if (y != size - 1)
			file << ",";

		file << "\n";
	}

	file << "}";
	file.close();

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
			file << round(map.map[x][y].value * 100) / 100;
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

/*
	Created by using RME source code and hex editor
*/
bool MapOutput::saveAsOTBM(const Map& map, string filename)
{
	int size = map.getSize();
	auto tiles = map.map;

	int local_x = -1, local_y = -1, local_z = -1;

	FILE* f;

	if (fopen_s(&f, filename.c_str(), "wb"))
		return false;

	vector<unsigned char> header1{
		0x00, 0x00, 0x00, 0x00,
		0xFE, 0x00, 0x02, 0x00,
		0x00, 0x00 };
	
	vector<unsigned char> header2{
		0x03, 0x00,

		0x00, 0x00, 0x14, 0x00,
		0x00, 0x00, 
		
		0xFE, 0x02, // OTBM_MAP_DATA node
		0x01, 0x00, 0x00, // Map description
		0x01, 0x00,	0x00, // Map description
		0x0B, 0x00, 0x00, // Spawn file
		0x0D, 0x00, 0x00  // House file
	};

	vector <unsigned char> footer {
		0xFE, 0x0C, 0xFF, 
		0xFE, 0x0F,	0xFF, 
		0xFF, 0xFF
	};

	// Writing file
	for (auto hex : header1)
		fputc(hex, f);

	unsigned short otbmMapSize = size;
	if (otbmMapSize < 256)
		otbmMapSize = 256;

	if (size > 250)
	{
		size = 250;
		cout << "Warning: Map size was set to 250x250 SQM, type --help to get more info." << std::endl;
	}


	fwrite(&otbmMapSize, sizeof(unsigned short), 1, f); // size X
	fwrite(&otbmMapSize, sizeof(unsigned short), 1, f); // size Y

	for (auto hex : header2)
		fputc(hex, f);

	int z = 7;
	bool first = true;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			// Check if we should create new node
			if (x < local_x || x >= local_x + 256 ||
				x < local_y || y >= local_y + 256 ||
				z != local_z)
			{
				if (!first)
				{
					// End node
					fputc(0xFF, f);
				}
				first = false;

				// New node
				fputc(0xFE, f); // Node start
				fputc(0x04, f); // Node type

				unsigned short tmp = (local_x = x & 0xFF00);
				fwrite(&tmp, sizeof(unsigned short), 1, f); // start X
				tmp = (local_y = y & 0xFF00);
				fwrite(&tmp, sizeof(unsigned short), 1, f); // start Y
				fputc(local_z = 0x07, f);                   // start Z
			}

			fputc(0xFE, f); // Node start
			fputc(0x05, f); // Node type (OTBM_TILE)

			fputc(static_cast<unsigned char>(x)& 0xFF, f); // Pos X
			fputc(static_cast<unsigned char>(y)& 0xFF, f); // Pos Y

			fputc(0x09, f); // OTBM_ATTR_ITEM

			unsigned short tmp = tiles[x][y].getItemId();
			fwrite(&tmp, sizeof(unsigned short), 1, f); // Item ID

			fputc(0xFF, f); // Node end
		}
	}

	// Closing last node
	if (!first) {
		fputc(0xFF, f);
	}

	for (auto hex : footer)
		fputc(hex, f);

	fclose(f);

	return true;
}
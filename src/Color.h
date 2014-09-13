#ifndef __COLOR_H__
#define __COLOR_H__
class Color
{
public:
	unsigned char r = 0, g = 0, b = 0, a = 0;

	Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 255) : r(_r), g(_g), b(_b), a(_a) {};
	~Color() {};
};

#endif
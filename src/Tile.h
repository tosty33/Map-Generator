#ifndef __TILE_H__
#define __TILE_H__

#include <iostream>

#include "Color.h"

using namespace std;

class Tile
{
public:
	bool selected = false;
	float value = 0.0;

	Color getColor();
	int getItemId();

	Tile();
	~Tile();

	// Operator overloading
	template <class T>
	inline bool operator< (T value)
	{
		return (this->value < value ? true : false);
	}

	template <class T>
	inline bool operator> (T value)
	{
		return (this->value > value ? true : false);
	}

	template <class T>
	inline T operator+ (T right)
	{
		return (this->value + right);
	}

	template <class T>
	inline T operator- (T right)
	{
		return (this->value - right);
	}

	template <class T>
	inline T operator* (T right)
	{
		return (this->value * right);
	}

	template <class T>
	inline T operator== (T right)
	{
		return (this->value == right);
	}

	template <class T>
	inline bool operator>= (T value)
	{
		return (this->value >= value ? true : false);
	}

	template <class T>
	inline bool operator<= (T value)
	{
		return (this->value <= value ? true : false);
	}

	template <class T>
	inline Tile& operator= (T right)
	{
		value = right;
		return *this;
	}

	template <class T>
	inline Tile& operator+= (T right)
	{
		value += right;
		return *this;
	}

	template <class T>
	inline Tile& operator-= (T right)
	{
		value -= right;
		return *this;
	}

	template <class T>
	inline Tile& operator*= (T right)
	{
		value *= right;
		return *this;
	}

	// Friends
	friend ostream& operator<<(ostream& out, const Tile& tile);
};

#endif
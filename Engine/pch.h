#pragma once

#include <d2d1.h>
#include <dwrite.h>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <d2d1helper.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <comdef.h>
#include <d2d1helper.h>
#include "Resource.h"
#include <dxgi1_4.h>
#include <cmath>
#include <list>
#include <vector>
#include <map>
#include "CommonEnums.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "MathHelper.h"
#include <wincodec.h>

using namespace std;
using namespace MathHelper;

class Vector2D
{

public:
	Vector2D()
		: x(0.0f)
		, y(0.0f)
	{

	}

	Vector2D(float x, float y) : x(x), y(y) {}

	float x, y;

	static const Vector2D Zero;
	static const Vector2D One;

	Vector2D& operator+=(const Vector2D& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	float length() const
	{
		return sqrt(x * x + y * y);
	}

	void clear()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D operator * (float f)
	{
		return Vector2D{ x * f, y * f };
	}

	Vector2D operator * (Vector2D other)
	{
		return Vector2D{ x * other.x, y * other.y };
	}
	Vector2D operator - (Vector2D other)
	{
		return Vector2D{ x - other.x, y - other.y };
	}
	Vector2D operator + (Vector2D other)
	{
		return Vector2D{ x + other.x, y + other.y };
	}

	Vector2D operator / (float f) const
	{
		if (f == 0.0f)
		{
			return *this;
		}
		return Vector2D{ x / f, y / f };
	}

	Vector2D operator - ()
	{
		return Vector2D(-x, -y);
	}

	Vector2D operator / (const Vector2D& other) const
	{
		if (other.x == 0.0f || other.y == 0.0f)
		{
			return *this;
		}
		return Vector2D{ x / other.x, y / other.y };
	}

	bool operator ==(Vector2D other)
	{
		return (x == other.x && y == other.y);
	}
	static float Distance2(Vector2D a, Vector2D b)
	{
		return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
	}
	Vector2D Normalize()
	{
		float length = sqrt(pow(x, 2) + pow(y, 2));
		if (length == 0.f)
			return Vector2D{ x, y };
		return Vector2D({ x / length, y / length });
	}


};

inline const Vector2D Vector2D::Zero = { 0.0f, 0.0f };
inline const Vector2D Vector2D::One = { 1.0f, 1.0f };


enum class Color
{
	RED = D2D1::ColorF::Red,
	BLACK = D2D1::ColorF::Black,
	WHITE = D2D1::ColorF::White,
	GREEN = D2D1::ColorF::Green,
};

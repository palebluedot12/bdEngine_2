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
#include "CommonEnums.h"

using namespace std;

class Vector2D
{
public:
	Vector2D(float x, float y) : x(x), y(y) {}
	float x, y;

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
	bool operator == (Vector2D other)
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

enum class Color
{
	RED = D2D1::ColorF::Red,
	BLACK = D2D1::ColorF::Black,
	WHITE = D2D1::ColorF::White
};

enum EDirType { UP, RIGHT, DOWN, LEFT };
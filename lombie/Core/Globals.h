#pragma once
#include <NuakeRenderer/Math.h>
#include <map>

enum class ColorNames
{
	Black,
	White,
	LightGrey,
	Grey,
	DarkGrey,
	Blue,
	DarkBlue,
	Green,
	DarkGreen,
	Red,
	DarkRed
};

class Globals
{
public:
	static Vector2 WindowSize;
	static float TileSize;
	static std::map<ColorNames, Color> Colors;
};

#pragma once
#include <NuakeRenderer/Math.h>

class Char
{
private:
	char _data;
	Color _fgColor;
	Color _bgColor;

public:
	Char(char data, const Color& fg = Color(1.0f, 1.0f, 1.0f, 1.0f), const Color& bgColor = Color(0.0f, 0.0f, 0.0f, 1.0f));
	~Char();

	char GetData() const;
	Color GetBgColor() const;
	Color GetFgColor() const;
};
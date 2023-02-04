#include "Char.h"

Char::Char(char data, const Color& fg, const Color& bg) :
	_data(data),
	_fgColor(fg),
	_bgColor(bg)
{
}

Char::~Char()
{

}

char Char::GetData() const
{
	return _data;
}

Color Char::GetFgColor() const
{
	return _fgColor;
}

Color Char::GetBgColor() const
{
	return _bgColor;
}
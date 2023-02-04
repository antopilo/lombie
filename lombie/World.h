#pragma once
#include "ASCII/Plate.h"

#include <memory>
#include <string>

class World
{
private:
	std::string _name;
	unsigned int _width;
	unsigned int _height;
	
public:
	World(const std::string& name, unsigned int width, unsigned int height);
	~World();

};
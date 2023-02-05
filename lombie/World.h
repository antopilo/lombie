#pragma once
#include "ASCII/Plate.h"
#include "ASCII/UIPlate.h"
#include "Camera.h"
#include "Player.h"

#include <memory>
#include <string>

class World
{
public:
	const float WORLD_SIZE = 0.25f;

private:
	std::string _name;
	uint32_t _width;
	uint32_t _height;
	
	std::shared_ptr<Plate> _plate;
	Camera _camera;
	
	std::shared_ptr<Player> _player;

	std::vector<std::shared_ptr<UIPlate>> _ui;
public:
	World(const std::string& name, uint32_t width, uint32_t height);
	~World();

	void Update(float ts);
	void Render();

public:
	Camera& GetCamera();
};
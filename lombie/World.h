#pragma once
#include "ASCII/Plate.h"
#include "ASCII/UIPlate.h"
#include "ASCII/ContextMenuPlate.h"

#include "Camera.h"
#include "Player.h"
#include "Inventory/Entity.h"

#include <NuakeRenderer/Window.h>


#include <memory>
#include <string>

class World
{
private:
	std::string _name;
	uint32_t _width;
	uint32_t _height;
	float _worldTime = 0.0f;

	std::shared_ptr<Player> _player;

	Camera _camera;
	
	Vector2 _worldMouseCoords;
	Vector2 _mouseTilePosition;

	std::shared_ptr<Plate> _plate;

	std::vector<Entity*> _entities;
	std::vector<std::shared_ptr<UIPlate>> _ui;
	Entity* _hoveredEntity;
	bool _isHoveringEntity = false;

	bool _contextMenuOpened = false;
	ContextMenuPlate* _contextMenu;
public:
	World(const std::string& name, uint32_t width, uint32_t height);
	~World();

	void Update(float ts, NuakeRenderer::Window& window);
	void Render();

	bool HasEntity(const Vector2& pos);

	Entity* GetEntity(const Vector2& pos);
	void DestroyEntity(const Vector2& pos);
public:
	Camera& GetCamera();
};
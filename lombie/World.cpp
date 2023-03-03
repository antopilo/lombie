#include "Player.h"

#include "World.h"

#include "ASCII/InventoryPlate.h"
#include "ASCII/PlateRenderer.h"
#include "ASCII/UIPlate.h"
#include "Core/InputManager.h"
#include "Core/Globals.h"
#include "Inventory/Entity.h"

#include <Dependencies/imgui/imgui.h>
#include <GLFW/glfw3.h>

#include <iostream>

World::World(const std::string& name, uint32_t width, uint32_t height) :
	_name(name),
	_width(width),
	_height(height)
{
	_plate = std::make_shared<Plate>(width, height);
	_player = std::make_shared<Player>("Dev", this);

	_contextMenu = new ContextMenuPlate(_player.get());

	_player->SetPosition(width / 2, height / 2);
	_worldMouseCoords = Vector2(-1, -1);
	
	// Generate some random world
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			_plate->SetChar(x, y, Char(249, Color(0.1, 0.1, 0.1, 1.0)));
		}
	}

	IItem junk = IItem("Stick", 0.1f, ItemType::Weapon);
	ItemEntity* junkE = new ItemEntity(junk, Vector2(width / 2 + 3, height / 2));
	_entities.push_back(junkE);

	IItem money = IItem("Money x10", 0.1f, ItemType::Valuable);
	ItemEntity* moneyE = new ItemEntity(money, Vector2(width / 2 -1 , height / 2 + 2));
	_entities.push_back(moneyE);

	IItem carBattery = IItem("Car Battery", 0.1f, ItemType::Junk);
	ItemEntity* carBatteryE = new ItemEntity(carBattery, Vector2(width / 2 - 3, height / 2 - 2));
	_entities.push_back(carBatteryE);

	IItem ham = IItem("Ham", 0.5f, ItemType::Food);
	ItemEntity* hamE = new ItemEntity(ham, Vector2(width / 2 - 5, height / 2 - 5));
	_entities.push_back(hamE);

	IItem ham2 = IItem("Ham2", 0.5f, ItemType::Food);
	ItemEntity* hamE2 = new ItemEntity(ham2, Vector2(width / 2 - 3, height / 2 - 3));
	_entities.push_back(hamE2);

	IItem ham3 = IItem("Ham3", 0.5f, ItemType::Food);
	ItemEntity* hamE3 = new ItemEntity(ham3, Vector2(width / 2 - 4, height / 2 - 4));
	_entities.push_back(hamE3);

	auto plate = std::make_shared<UIPlate>(Vector2(0,0), 16, 10);
	_ui.push_back(plate);
	auto plateInv = std::make_shared<InventoryPlate>(_player.get());
	_ui.push_back(plateInv);
}

World::~World()
{

}

void World::Update(float ts, NuakeRenderer::Window& window)
{
	_worldTime += ts;
	// Check if mouse is over UI
	int numTileWidth = 16 * (1.0 / Globals::TileSize);
	int numTileHeight = 9.0 * (1.0 / Globals::TileSize);
	int screenWidth = window.GetWindowSize().x / numTileWidth;
	int screenHeight = window.GetWindowSize().y / numTileHeight;
	float mouseX = Input::GetMouseX() / screenWidth;
	float mouseY = (window.GetWindowSize().y - Input::GetMouseY()) / screenHeight;

	_mouseTilePosition = Vector2((int)mouseX, (int)(mouseY - 0.5));

	bool mouseGrabbed = false;
	for (auto& u : _ui)
	{
		if (u->AcceptInput(mouseX, mouseY))
		{
			u->Hover((mouseX - u->GetPosition().x) * 2.0, mouseY - u->GetPosition().y);
			mouseGrabbed = true;
		}
	}

	if (!mouseGrabbed)
	{
		_worldMouseCoords = Vector2((int)mouseX, (int)(mouseY - 0.5));
		_worldMouseCoords -= _camera.GetWorldCenterCoord();
		_worldMouseCoords -= Vector2(ceil(numTileWidth / 2.0), ceil(numTileHeight / 2.0));
	}
	else
	{
		_worldMouseCoords = Vector2(-999, -999);
	}

	_player->Update(ts);
	_camera.Update(ts);
	auto camPos = _camera.GetPosition();
	
	auto targetCam = Vector3(-_player->GetPosition().x / (1.0 / Globals::TileSize), -_player->GetPosition().y / (1.0 / Globals::TileSize), 0);
	_camera.SetPosition(targetCam);

	// Update info ui
	auto plate = _ui[0]->GetPlate();

	std::vector<std::string> infoData = std::vector<std::string>();
	infoData.push_back("" + _player->_name);
	infoData.push_back("HP: " + std::to_string((int)_player->_health) + "/100");
	infoData.push_back("Age: " + std::to_string(_player->_age));
	infoData.push_back("Stam: " + std::to_string((int)_player->_stamina));

	int y = _ui[0]->GetPlate()->GetHeight() - 2;
	int startX = 2;
	for (const auto line : infoData)
	{
		y -= 1;

		int x = startX;
		for (const auto letter : line)
		{
			_ui[0]->GetPlate()->SetChar(x, y, Char(letter));
			x++;
		}
	}

	if (!mouseGrabbed)
	{
		// Check entity hover
		bool hasFoundEntity = false;
		for (auto& e : _entities)
		{
			const Vector2& entityPos = e->Position;
			if (entityPos == _worldMouseCoords)
			{
				hasFoundEntity = true;
				_isHoveringEntity = true;
				_hoveredEntity = e;

				if (Input::IsMouseButtonReleased(GLFW_MOUSE_BUTTON_2))
				{
					_contextMenuOpened = true;
					_contextMenu->SetSelectedEntity(_hoveredEntity);
					_contextMenu->RecreatePlate(_mouseTilePosition);
				}
			}
		}

		if (!hasFoundEntity)
		{
			_isHoveringEntity = false;
		}
	}
}

void World::Render()
{
	// Render UI
	Matrix4 transform = Matrix4(1.0f);
	transform = glm::scale(transform, Vector3(Globals::TileSize));

	for (auto& p : _ui)
	{
		p->Draw();
	}

	auto camPos = Vector2(_camera.GetPosition().x, _camera.GetPosition().y);
	float halfWidth = 16.0f / 2.0f;
	float halfHeight = 9.0f / 2.0f;
	float multiplier = 1.0f / Globals::TileSize;
	Vector2 offset = Vector2(halfWidth, halfHeight );
	Vector2 from = (-camPos - offset) * multiplier;
	Vector2 to = (- camPos + offset) * multiplier;

	PlateRenderer::Get().RenderPlate(*_plate.get(), transform, _camera.GetView(), _camera.GetProjection(), from, to);

	ImGui::Begin("World");
	std::string text = "From: (" + std::to_string(from.x) + ", " + std::to_string(from.y) + ")";
	ImGui::Text(text.c_str());

	text = "To: (" + std::to_string(to.x) + ", " + std::to_string(to.y) + ")";
	ImGui::Text(text.c_str());

	ImGui::SliderFloat("Speed", &(_camera._speed), 0.0f, 100.0f);

	ImGui::Text("Info");

	std::string tileHovered = "TileHovered: " + std::to_string(_worldMouseCoords.x) + ", " + std::to_string(_worldMouseCoords.y);
	ImGui::Text(tileHovered.c_str());
	ImGui::End();

	// Draw entities'

	for (const auto& e : _entities)
	{
		Matrix4 eTransform = Matrix4(1.0);
		eTransform = glm::scale(eTransform, Vector3(Globals::TileSize));

		Vector3 pos = Vector3(e->Position.x, e->Position.y, 0.1f);
		eTransform = glm::translate(eTransform, pos);

		const float glowingRate = 4.0f;
		float alpha = (sin(_worldTime * glowingRate) + 1.0) / 3.0;

		PlateRenderer::Get().RenderChar(e->Visual , eTransform);
	}

	// Draw the player
	_player->Draw();

	// Draw hover
	Matrix4 cursorTransform = Matrix4(1.0);
	cursorTransform = glm::scale(cursorTransform, Vector3(Globals::TileSize));

	Vector3 pos = Vector3(_worldMouseCoords.x, _worldMouseCoords.y, 0.2f);
	cursorTransform = glm::translate(cursorTransform, pos);

	const float glowingRate = 4.0f;
	float alpha = (sin(_worldTime * glowingRate) + 1.0) / 3.0;

	PlateRenderer::Get().RenderChar(Char(219, Color(1.0, 1.0, 1.0, alpha), Color(1.0, 1.0, 1.0, alpha)), cursorTransform);

	// Display label
	if (_isHoveringEntity)
	{
		if (_hoveredEntity->Type == EntityType::Item)
		{
			ItemEntity* itemEntity = dynamic_cast<ItemEntity*>(_hoveredEntity);

			Color darkColor;
			Color lightColor;
			if (itemEntity->Item._type == ItemType::Valuable)
			{
				darkColor = Globals::Colors[ColorNames::DarkGreen];
				lightColor = Globals::Colors[ColorNames::Green];
			}
			else if (itemEntity->Item._type == ItemType::Junk)
			{
				darkColor = Globals::Colors[ColorNames::Grey];
				lightColor = Globals::Colors[ColorNames::LightGrey];
			}
			else if (itemEntity->Item._type == ItemType::Weapon)
			{
				darkColor = Globals::Colors[ColorNames::DarkBlue];
				lightColor = Globals::Colors[ColorNames::Blue];
			}
			else if(itemEntity->Item._type == ItemType::Food)
			{
				darkColor = Globals::Colors[ColorNames::DarkRed];
				lightColor = Globals::Colors[ColorNames::Red];
			}
			Matrix4 labelTransform = Matrix4(1.0);
			labelTransform = glm::scale(labelTransform, Vector3(Globals::TileSize));

			Vector3 pos = Vector3(_worldMouseCoords.x + 1, _worldMouseCoords.y, 0.2f);
			labelTransform = glm::translate(labelTransform, pos);

			
			PlateRenderer::Get().RenderCharHalf(Char('-', darkColor), labelTransform);
			labelTransform = glm::translate(labelTransform, Vector3(0.5, 0, 0));
			PlateRenderer::Get().RenderCharHalf(Char('-', darkColor), labelTransform);
			labelTransform = glm::translate(labelTransform, Vector3(0.5, 0, 0));
			PlateRenderer::Get().RenderCharHalf(Char(' ', darkColor, darkColor), labelTransform);
			labelTransform = glm::translate(labelTransform, Vector3(0.5, 0, 0));
			PlateRenderer::Get().RenderCharHalf(Char(' ', lightColor, lightColor), labelTransform);
			const std::string label = itemEntity->Item._name;
			for (const auto& c : label)
			{
				// move half a character.
				labelTransform = glm::translate(labelTransform, Vector3(0.5, 0, 0));
				PlateRenderer::Get().RenderCharHalf(Char(c, Globals::Colors[ColorNames::Black], lightColor), labelTransform);
			}
			labelTransform = glm::translate(labelTransform, Vector3(0.5, 0, 0));
			PlateRenderer::Get().RenderCharHalf(Char(' ', Globals::Colors[ColorNames::Black], lightColor), labelTransform);
		}
	}

	if (_contextMenuOpened)
	{
		_contextMenu->Draw();
	}
}

bool World::HasEntity(const Vector2& pos)
{
	auto it = std::find_if(_entities.begin(), _entities.end(), [pos](Entity* e)
		{
			return e->Position == pos;
		});

	return  it != _entities.end();
}

Entity* World::GetEntity(const Vector2& pos)
{
	auto it = std::find_if(_entities.begin(), _entities.end(), [pos](Entity* e)
		{
			return e->Position == pos;
		});
	// Maybe there's a better way to handle not found entities.
	if (it == _entities.end())
	{
		return nullptr;
	}

	return *it;
}

void World::DestroyEntity(const Vector2& pos)
{
	_entities.erase(std::remove_if(_entities.begin(), _entities.end(), [pos](Entity* e) 
		{
		return e->Position == pos;
		}));
}

Camera& World::GetCamera()
{
	return _camera;
}
#include "ContextMenuPlate.h"
#include "PlateRenderer.h"

ContextMenuPlate::ContextMenuPlate(Player* player) : _player(player)
{
	_size = Vector2(0, 0);
}

void ContextMenuPlate::SetSelectedEntity(Entity* entity)
{
	_selectedEntity = entity;

	if (_selectedEntity->Type == EntityType::Item)
	{
		AddAction(ContextMenuAction{ ActionTypes::Inspect });
	}
}

void ContextMenuPlate::AddAction(const ContextMenuAction& action)
{
	_actions.push_back(std::move(action));

	hasChanged = true;
}

void ContextMenuPlate::RecreatePlate(Vector2 position)
{
	// Calculate height
	//
	// --(   item  )
	//   | action  |
	//   | action2 |
	//	 *---------*
	// 
	
	_position = position;
	_position.x += 1;
	_position.y -= 0.5;
	int rows = 1 + _actions.size() + 1;
	constexpr int columns = 16 + 2;
	_position.y -= rows - 2;
	_plate = std::make_shared<Plate>(columns, rows);

	// HEADER CREATION
	Color headerColor = Globals::Colors[ColorNames::Grey];
	Color headerColorLight = Globals::Colors[ColorNames::LightGrey];
	int cursorX = 0;
	int cursorY = rows - 1;
	if (_selectedEntity != nullptr)
	{
		_plate->SetChar(cursorX, cursorY, Char('-', headerColor));
		cursorX++;
		_plate->SetChar(cursorX, cursorY, Char('-', headerColor));
		cursorX++;
		_plate->SetChar(cursorX, cursorY, Char(' ', headerColor, headerColor));
		cursorX++;
		_plate->SetChar(cursorX, cursorY, Char(' ', headerColorLight, headerColorLight));
		cursorX++;
		if (_selectedEntity->Type == EntityType::Item)
		{
			ItemEntity* itemEntity = dynamic_cast<ItemEntity*>(_selectedEntity);
			_plate->WriteString(itemEntity->Item._name, cursorX, cursorY, Globals::Colors[ColorNames::Black], headerColorLight);

			cursorX += itemEntity->Item._name.size();
		}

		while (cursorX < columns)
		{
			_plate->SetChar(cursorX, cursorY, Char(' ', headerColorLight, headerColorLight));
			cursorX++;
		}
	}
	else
	{

	}

	cursorY--;
	// OPTIONS
	int i = 0;
	for (const auto& o : _actions)
	{
		i++;
		_zones[std::to_string(i)] = Zone(2, cursorY, columns - 1, cursorY);

		cursorX = 2;
		_plate->SetChar(cursorX, cursorY, Char(179, Globals::Colors[ColorNames::White]));
		cursorX++;

		_plate->WriteString("Action", cursorX, cursorY, Globals::Colors[ColorNames::White]);

		_plate->SetChar(columns - 1, cursorY, Char(179, Globals::Colors[ColorNames::White]));
		cursorY--;
		cursorX = 2;

	}

	// Bottom
	_plate->SetChar(cursorX, cursorY, Char(192, Globals::Colors[ColorNames::White]));
	cursorX++;
	while (cursorX < columns)
	{
		_plate->SetChar(cursorX, cursorY, Char(196, Globals::Colors[ColorNames::White]));
		cursorX++;
	}
	_plate->SetChar(columns - 1, cursorY, Char(217, Globals::Colors[ColorNames::White]));
}

void ContextMenuPlate::Draw()
{
	Matrix4 transform = Matrix4(1);
	transform = glm::scale(transform, Vector3(Globals::TileSize));
	transform = glm::translate(transform, Vector3(_position.x, _position.y, 0.3f));

	PlateRenderer::Get().RenderPlateHalf(*_plate.get(), transform, Matrix4(1), glm::ortho(0.0, 16.0, 0.0, 9.0, -1.0, 1.0));
}

void ContextMenuPlate::Update(float ts)
{

}
#pragma once
#include "UIPlate.h"
#include "../Player.h"
#include "../Inventory/Entity.h"

#include <functional>
#include <string>
#include <vector>

enum class ActionTypes
{
	Pickup,
	Inspect
};

struct ContextMenuAction
{
	ActionTypes Type;
	bool _locked = false;
	std::function<void()> _callback = []{};
};

class ContextMenuPlate : public UIPlate
{
private:
	Player* _player;
	Vector2 _size;

	std::vector<ContextMenuAction> _actions;

	Entity* _selectedEntity = nullptr;

	bool hasChanged = false;
public:
	ContextMenuPlate(Player* player);
	~ContextMenuPlate() = default;

	void SetSelectedEntity(Entity* entity);
	void AddAction(const ContextMenuAction& action);
	void RecreatePlate(Vector2 position);

	void Draw();
	void Update(float ts);
};

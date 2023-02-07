#pragma once
#include "IAction.h"

#include "../Inventory/Entity.h"

class Player;

class LootAction : public IAction
{
private:
	Player* _player = nullptr;
	ItemEntity& _itemEntity;
	float _cost = 1.0f;

public:
	LootAction(Player* player, ItemEntity& itemEntity);

	void Execute() override;
};
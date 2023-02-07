#include "LootAction.h"

#include "../Player.h"
#include "../World.h"

LootAction::LootAction(Player* player, ItemEntity& itemEntity) : _itemEntity(itemEntity)
{
	_player = player;
}

void LootAction::Execute()
{
	if (_player->_inventory.CanAddItem(_itemEntity.Item))
	{
		_player->_inventory.AddItem(std::move(_itemEntity.Item));
		_player->_world->DestroyEntity(_itemEntity.Position);
	}
}
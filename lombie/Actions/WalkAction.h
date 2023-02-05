#pragma once
#include "IAction.h"
#include "../Player.h"
enum class WalkDirection
{
	Up, Down, Left, Right
};

class Player;

class WalkAction : public IAction
{
private:
	WalkDirection _direction;
	Player* _player = nullptr;
	float _cost = 1.0f;
public:
	WalkAction(WalkDirection direction, Player* player);

	void Execute() override;
};
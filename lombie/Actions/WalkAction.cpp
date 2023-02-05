#include "WalkAction.h"

WalkAction::WalkAction(WalkDirection direction, Player* player)
{
	_player = player;
	_direction = direction;
}

void WalkAction::Execute()
{
	if (_player->CanPerformAction(_cost))
	{
		_player->DrainStamina(_cost);
	}

	Vector2 position = _player->GetPosition();
	switch (_direction)
	{
	case WalkDirection::Up:
		position.y += 1;
		break;
	case WalkDirection::Down:
		position.y -= 1;
		break;
	case WalkDirection::Left:
		position.x -= 1;
		break;
	case WalkDirection::Right:
		position.x += 1;
		break;
	}

	_player->SetPosition(position.x, position.y);
}
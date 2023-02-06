#include "Player.h"
#include "Core/InputManager.h"
#include "ASCII/PlateRenderer.h"
#include "Core/Globals.h"

#include <GLFW/glfw3.h>

#include "Actions/WalkAction.h"
#include <Dependencies/imgui/imgui.h>

Player::Player(const std::string& name) :
	_name(name)
{
	_age = 25;
	_stamina = 100.0f;
	_position = Vector2(0, 0);
	_targetPosition = Vector2(0, 0);
	_startPosition = Vector2(0, 0);
	_timeAlive = 0.0f;
	_actionStarted = 0.0f;
	_actionEnd = 0.0f;

	_inventory.AddItem(IItem("Rock", 0.1f, ItemType::Weapon));
	_inventory.AddItem(IItem("Rock", 0.1f, ItemType::Weapon));
	_inventory.AddItem(IItem("Rock", 0.1f, ItemType::Weapon));
	_inventory.AddItem(IItem("Rock", 0.1f, ItemType::Weapon));
	_inventory.AddItem(IItem("Rock", 0.1f, ItemType::Weapon));
}

void Player::Update(float ts)
{
	_timeAlive += ts;
	float t = (_timeAlive - _actionStarted) / (_actionEnd - _actionStarted);
	t = std::min(t, 1.0f);
	_position = glm::mix(_startPosition, _targetPosition, t);

	if (_state == PLAYER_STATE::Action)
	{
		if (_timeAlive > _actionEnd)
		{
			_state = PLAYER_STATE::Idle;
		}
		else
		{
			return; // Performing an action..
		}
	}
	else
	{
		
	}

	bool isShift = Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT);
	if (Input::IsKeyPressed(GLFW_KEY_D))
	{
		QueueAction(new WalkAction(WalkDirection::Right, this));
	}
	else if(Input::IsKeyPressed(GLFW_KEY_A))
	{
		QueueAction(new WalkAction(WalkDirection::Left, this));
	}
	else if (Input::IsKeyPressed(GLFW_KEY_W))
	{
		QueueAction(new WalkAction(WalkDirection::Up, this));
	}
	else if (Input::IsKeyPressed(GLFW_KEY_S))
	{
		QueueAction(new WalkAction(WalkDirection::Down, this));
	}

	if (_actionQueue.size() > 0)
	{
		_startPosition = _position;
		_actionQueue.front()->Execute();
		_actionEnd = _timeAlive + 0.3f;
		_actionStarted = _timeAlive;
		_state = PLAYER_STATE::Action;
		_actionQueue.pop();
	}
}

void Player::Draw()
{
	Matrix4 transform = Matrix4(1.0);
	transform = glm::scale(transform, Vector3(Globals::TileSize));
	transform = glm::translate(transform, Vector3(_position.x, _position.y, 0.1f));
	PlateRenderer::Get().RenderChar(Char(icon, Color(1.0, 0.0, 0.0, 1.0)), transform);

	if (ImGui::Begin("Player"))
	{
		ImGui::Text(("Name:" + _name).c_str());
		ImGui::Text(("State" + std::to_string((int)_state)).c_str());
		ImGui::Text(("Actions:" + std::to_string(_actionQueue.size())).c_str());
		if (ImGui::Button("+"))
		{
			icon++;
		}
		if (ImGui::Button("-"))
		{
			icon--;
		}

		ImGui::Text(("Char id:" + std::to_string((unsigned char)icon)).c_str());
	}
	ImGui::End();
}

Inventory& Player::GetInventory()
{
	return _inventory;
}

void Player::QueueAction(IAction* action)
{
	if (_actionQueue.size() < 3)
	{
		_actionQueue.push(action);
	}
}

Vector2 Player::GetPosition() const
{
	return _targetPosition;
}

void Player::SetPosition(uint32_t x, uint32_t y)
{
	_targetPosition = Vector2(x, y);
}

bool Player::CanPerformAction(float cost)
{
	return _stamina - cost > 0.0f;
}

void Player::DrainStamina(float cost)
{
	_stamina -= cost;

	if (_stamina < 0.0f)
	{
		_stamina = 0.0f;
	}
}

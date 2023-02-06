#include "Camera.h"
#include "Core/InputManager.h"
#include "Core/Globals.h"

#include <GLFW/glfw3.h>

Camera::Camera()
{
	_position = Vector3(0, 0, 0);
	_projection = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
	_view = Matrix4(1.0);
	_hasChanged = true;
	_speed = 0.5f;
}

void Camera::Update(float ts)
{
	Vector3 pos = _position;
	if (Input::IsKeyPressed(GLFW_KEY_UP))
	{
		pos.y -= _speed * ts;
	}

	if (Input::IsKeyPressed(GLFW_KEY_DOWN))
	{
		pos.y += _speed * ts;
	}

	if (Input::IsKeyPressed(GLFW_KEY_RIGHT))
	{
		pos.x -= _speed * ts;
	}

	if (Input::IsKeyPressed(GLFW_KEY_LEFT))
	{
		pos.x += _speed * ts;
	}

	SetPosition(pos);
}

void Camera::SetPosition(const Vector3& position)
{
	_position = position;
	_hasChanged = true;
}

Vector3 Camera::GetPosition() const
{
	return _position;
}

Matrix4 Camera::GetView()
{
	if (_hasChanged)
	{
		_view = Matrix4(1.0);
		_view = glm::translate(_view, _position);
	}

	return _view;
}

Matrix4 Camera::GetProjection() const
{
	return _projection;
}

Vector2 Camera::GetWorldCenterCoord() const
{
	// Camera world pos
	Vector2 result = Vector2(_position.x, _position.y) * Vector2(1.0 / Globals::TileSize);
	return result;
}
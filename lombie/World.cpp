#include "World.h"
#include "ASCII/PlateRenderer.h"
#include "Core/InputManager.h"
#include "ASCII/UIPlate.h"
#include <iostream>

#include <Dependencies/imgui/imgui.h>

World::World(const std::string& name, uint32_t width, uint32_t height) :
	_name(name),
	_width(width),
	_height(height)
{
	_plate = std::make_shared<Plate>(width, height);
	_player = std::make_shared<Player>("Dev");

	// World Plate

	auto plate = std::make_shared<UIPlate>(Vector2(0,0), 25, 30);
	_ui.push_back(plate);
}

World::~World()
{

}

void World::Update(float ts)
{
	_player->Update(ts);
	_camera.Update(ts);
	auto camPos = _camera.GetPosition();
	
	auto targetCam = Vector3(-_player->GetPosition().x / 4.0, -_player->GetPosition().y / 4.0, 0);
	_camera.SetPosition(targetCam);
}

void World::Render()
{
	// Render UI
	Matrix4 transform = Matrix4(1.0f);
	transform = glm::scale(transform, Vector3(WORLD_SIZE));

	for (auto& p : _ui)
	{
		p->Draw();
	}

	auto camPos = Vector2(_camera.GetPosition().x, _camera.GetPosition().y);
	float halfWidth = 16.0f / 2.0f;
	float halfHeight = 9.0f / 2.0f;
	float multiplier = 1.0f / WORLD_SIZE;
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
	ImGui::End();

	// Draw the player
	
	_player->Draw();

}

Camera& World::GetCamera()
{
	return _camera;
}
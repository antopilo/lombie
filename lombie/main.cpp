#include "ASCII/Plate.h"
#include "ASCII/PlateRenderer.h"
#include "Core/InputManager.h"
#include "World.h"
#include "ASCII/DebugPlate.h"

#include <NuakeRenderer/NuakeRenderer.h>
#include <NuakeRenderer/Window.h>
#include <Dependencies/glfw/include/GLFW/glfw3.h>

#include <iostream>
#include <cstdint>

/* LOMBIE v0.0.1

TODO:
	- Render ASCII
		- Background color
		- Foreground color
		- Symbol
		- Outline?
		- Animation?
	- Render World
	- Render UI windows on top in same ASCII
*/

int main()
{
	std::cout << "Hello Lombie!" << std::endl;

	using namespace NuakeRenderer;

	Window gameWindow = Window("LOMBIE", Vector2(1280, 720));
	Input::SetWindow(gameWindow.GetHandle());

	NuakeRenderer::Init();
	NuakeRenderer::ApplyNuakeImGuiTheme();

	DebugPlate debugPlate = DebugPlate();

	World world = World("dev", 100, 100);

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	while (!gameWindow.ShouldClose())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Update
		world.Update(deltaTime);

		// Render
		Clear();

		glViewport(0, 0, gameWindow.GetWindowSize().x, gameWindow.GetWindowSize().y);

		NuakeRenderer::BeginImGuiFrame();
		{
			//world.Render();
			debugPlate.Draw();
		}
		NuakeRenderer::EndImGuiFrame();

		gameWindow.SwapBuffers();
		NuakeRenderer::PollEvents();
	}

	return 1;
}
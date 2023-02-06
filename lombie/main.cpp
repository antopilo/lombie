#include "ASCII/Plate.h"
#include "ASCII/PlateRenderer.h"
#include "Core/InputManager.h"
#include "World.h"
#include "ASCII/DebugPlate.h"
#include "Core/Globals.h"

#include <NuakeRenderer/NuakeRenderer.h>
#include <NuakeRenderer/Window.h>
#include <Dependencies/glfw/include/GLFW/glfw3.h>

#include <iostream>
#include <cstdint>

/* LOMBIE v0.0.1

TODO:
	- Render ASCII				X	
		- Background color		X
		- Foreground color		X
		- Symbol
		- Outline?
		- Animation?
	- Render World				X
	- Render UI windows on top in same ASCII	X

*/

int main()
{
	std::cout << "Initializing Lombie" << std::endl;

	using namespace NuakeRenderer;

	Window gameWindow = Window("LOMBIE", Globals::WindowSize);
	Input::SetWindow(gameWindow.GetHandle());

	NuakeRenderer::Init();
	NuakeRenderer::ApplyNuakeImGuiTheme();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::cout << "Renderer Initialized" << std::endl;

	Globals::Colors[ColorNames::Black] = Color(0, 0, 0, 1);
	Globals::Colors[ColorNames::White] = Color(1, 1, 1, 1);
	Globals::Colors[ColorNames::DarkGrey] = Color(0.05, 0.05, 0.05, 1);
	Globals::Colors[ColorNames::Grey] = Color(0.5, 0.5, 0.5, 1);
	Globals::Colors[ColorNames::LightGrey] = Color(0.7, 0.7, 0.7, 1);
	Globals::Colors[ColorNames::Blue] = Color(0, 0.38, 1, 1);
	Globals::Colors[ColorNames::DarkBlue] = Color(0, 0.2, 0.5, 1);
	Globals::Colors[ColorNames::Green] = Color(0, 1, 0.2, 1);
	Globals::Colors[ColorNames::DarkGreen] = Color(0, 0.4, 0.05, 1);

	std::cout << "Colors initialized" << std::endl;

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
		world.Update(deltaTime, gameWindow);

		// Render
		Clear();
		glfwSetWindowAspectRatio(gameWindow.GetHandle(), 16, 9);
		glViewport(0, 0, gameWindow.GetWindowSize().x, gameWindow.GetWindowSize().y);
		
		NuakeRenderer::BeginImGuiFrame();
		{
			world.Render();
			//debugPlate.Draw();
		}
		NuakeRenderer::EndImGuiFrame();

		gameWindow.SwapBuffers();
		NuakeRenderer::PollEvents();
	}

	return 1;
}
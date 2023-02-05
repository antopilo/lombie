#include "ASCII/Plate.h"
#include "ASCII/PlateRenderer.h"
#include "Core/InputManager.h"
#include "World.h"

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
	
	// Create a new ASCII plate.
	Plate plate = Plate(100, 100);
	std::string text = "Hello Fakse!";
	for(int i = 0; i < text.size(); i++)
		plate.SetChar(7 + i, 7, Char(text[i]));

	World world = World("dev", 1000, 1000);

	Window gameWindow = Window("LOMBIE", Vector2(1280, 720));
	Input::SetWindow(gameWindow.GetHandle());

	NuakeRenderer::Init();
	NuakeRenderer::ApplyNuakeImGuiTheme();


	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	while (!gameWindow.ShouldClose())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		world.Update(deltaTime);

		Clear();
		glViewport(0, 0, gameWindow.GetWindowSize().x, gameWindow.GetWindowSize().y);
		Matrix4 view = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

		// World plate is going to be 
		const float size = 0.25f;
		Matrix4 transform = Matrix4(1.0f);
		transform = glm::scale(transform, Vector3(size));
		NuakeRenderer::BeginImGuiFrame();

		//PlateRenderer::Get().RenderPlate(plate, transform, view);
		{
			ImGui::ShowMetricsWindow();
			// Basic info
			

			world.Render();

			// imgui code here...
			ImGui::Begin("camera");
			ImGui::Text("Position:");
			
			ImGui::End();
		}
		NuakeRenderer::EndImGuiFrame();

		

		gameWindow.SwapBuffers();
		PollEvents();
	}

	return 1;
}
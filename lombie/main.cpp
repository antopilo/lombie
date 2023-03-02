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

/* Notes

Rain effect: 

	Easy 3D effect can be done by simply traversing to the target tile
	Starting outside of the screen in the direction of the angle between center and target

	Example:
						Monitor
			  * start is  X - Center with magnitude until it gets out of screen.
		*------\-------------------------------*
		*       \
		*        \
		*		  \
		*		   \
		*			X <- Target destination	
		* 
		*		
		* 
		* 
		* 
		* --------------------------------------*
	========================================

	// Vegetation
	- Notes on vegetation juice:
	- make them wiggle with wind
*/

/* LOMBIE v0.0.1
TODO:
[X] Render ASCII
	[X]	Background color
	[X]	Foreground color
	[X]	Symbol				
	[ ]	Outline?
	[ ]	Animations
[X] Render UI windows on top in same ASCI

[ ] World basics
	[ ] P0 - Basic World map	
	[ ] P0 - Collision
	[ ] P0 - Loading of map
	[ ] P1 - Saving of map
	[ ] Time of Day
	[ ] P1 - Tile light levels
	[ ] Weathers
		[ ] Wind direction and Speed

	[ ] Fog of War maybe? Would be cool. Not necessary

[ ] Entities
	[ ] P1 - Create static entities
		- Must be in the world and have a fixed size
		- E.g: Car, Workbench, Barrel
	[ ] P1 - Create dynamic entities
		- Can move and have mutable states depending on time
		- E.g: Chicken (most basic)

[ ] Systems
	[ ] Line tracing (https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
	[ ] P0 - Path Finding ( either custom or lib) the simpler the better
	[ ] Player aiming (either grid or dynamic)

[ ] Player
	[ ] Running
	[ ] Vision
	[ ] Juice?

[ ] Rendering
	[ ] Particles
	[ ] Framebuffer pipeline
	[ ] Bloom
	[ ] Rain effect (soulash)

[ ] Make Inventory UI
	[ ] Display Weight and MaxWeight
	[ ] P0 - Display all categories 
	[ ] Fold categories
	[ ] P2 - Scroll in categories or whole window. Simpler the better
*/

using namespace NuakeRenderer;

void LoadColors()
{
	Globals::Colors[ColorNames::Black] = Color(0, 0, 0, 1);
	Globals::Colors[ColorNames::White] = Color(1, 1, 1, 1);
	Globals::Colors[ColorNames::DarkGrey] = Color(0.05, 0.05, 0.05, 1);
	Globals::Colors[ColorNames::Grey] = Color(0.5, 0.5, 0.5, 1);
	Globals::Colors[ColorNames::LightGrey] = Color(0.7, 0.7, 0.7, 1);
	Globals::Colors[ColorNames::Blue] = Color(0, 0.38, 1, 1);
	Globals::Colors[ColorNames::DarkBlue] = Color(0, 0.2, 0.5, 1);
	Globals::Colors[ColorNames::Green] = Color(0, 1, 0.2, 1);
	Globals::Colors[ColorNames::DarkGreen] = Color(0, 0.4, 0.05, 1);
	Globals::Colors[ColorNames::DarkRed] = Color(0.54, 0.0, 0.0, 1);
	Globals::Colors[ColorNames::Red] = Color(1, 0.0, 0.0, 1);

	std::cout << "Colors initialized" << std::endl;
}

void InitGL()
{
	NuakeRenderer::Init();
	NuakeRenderer::ApplyNuakeImGuiTheme();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::cout << "Renderer Initialized" << std::endl;
}

int main()
{
	std::cout << "Initializing Lombie" << std::endl;

	Window gameWindow = Window("LOMBIE", Globals::WindowSize);
	Input::SetWindow(gameWindow.GetHandle());

	InitGL();
	LoadColors();

	World world = World("dev", 100, 100);

	float deltaTime = 0.0f;	
	float lastFrame = 0.0f; 
	while (!gameWindow.ShouldClose())
	{
		// Update
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		world.Update(deltaTime, gameWindow);

		// Render
		Clear();
		glfwSetWindowAspectRatio(gameWindow.GetHandle(), 16, 9);
		glViewport(0, 0, gameWindow.GetWindowSize().x, gameWindow.GetWindowSize().y);
		
		NuakeRenderer::BeginImGuiFrame();
		
		world.Render();
		
		NuakeRenderer::EndImGuiFrame();

		// Finish
		Input::Update();
		gameWindow.SwapBuffers();
		NuakeRenderer::PollEvents();
	}

	return 1;
}
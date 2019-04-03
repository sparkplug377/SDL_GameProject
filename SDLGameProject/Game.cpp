#include "Game.h"
#include <iostream>

// default constructor
Game::Game() {
	// set the SDL window pointer to null
	sdlWindow = nullptr;
	// set the SDL renderer pointer to null
	sdlRenderer = nullptr;

	// initialize SDL 
	// if the initialization was not successful
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		// disable the game loop
		isGameOver = true;
		// print a failed message on to the console window
		std::cout << "Initialize SDL - failed" << std::endl;
	}
	// if the initialization was successful
	else {
		// enable to game loop
		isGameOver = false;
		// print a success message on to the console window
		std::cout << "Initialize SDL - success" << std::endl;
	}
}


bool Game::Start() {
	// create the renderer for the window created.
	sdlRenderer = SDL_CreateRenderer(sdlWindow, 0, -1);
	if (sdlRenderer != nullptr) {
		std::cout << "Create Renderer - success" << std::endl;

		// TODO: Initialize objects here

		// initialize player texture
		m_playerTexture = new Texture();
		// load the texture
		if (m_playerTexture->LoadPNGFromFile("../assets/old_enemies.png", sdlRenderer)) {
			std::cout << "Load player texture - success" << std::endl;
			// initialize player animation
			anim = new Animation(m_playerTexture, 0.05f);
			anim->AddFrame(17, 18, 31 - 17, 14);
			anim->AddFrame(32, 18, 47 - 32, 14);
			anim->AddFrame(47, 18, 64 - 47, 14);
			anim->AddFrame(65, 18, 79 - 64, 14);
			anim->AddFrame(80, 18, 95 - 80, 14);
			anim->AddFrame(96, 18, 111 - 96, 14);
		}
		else {
			std::cout << "Load player texture - failed" << std::endl;
			return false;
		}

		
		// Get the current clock time
		lastUpdate = SDL_GetTicks();

		return true;
	}
	std::cout << "Create Renderer - failed" << std::endl;
	return false;
}


void Game::ProcessInput() {
	// TODO: Get the user input here
}


void Game::Update() {
	// calculate deltaTime
	// current time - time since last update
	unsigned int ticks = SDL_GetTicks() - lastUpdate;
	// change this to milliseconds;
	float deltaTime = ticks / 1000.0f;
	// Get the current time 
	lastUpdate = SDL_GetTicks();
	std::cout << "DeltaTime: " << deltaTime <<  std::endl;

	// TODO: update your stuff here
	anim->Update(deltaTime);
}


void Game::Draw() {
	// set the Draw color to black
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
	// clears the render color with the color set above
	SDL_RenderClear(sdlRenderer);

	// TODO: draw your stuff here
	// Render the animation on the screen
	anim->Draw(sdlRenderer, 100, 200);

	// SDL_Renderer* draws to the hidden target. 
	// This function will take all of that and draws all of that in the window tied to the renderer
	SDL_RenderPresent(sdlRenderer);
}


void Game::Run(char * title, int width, int height, bool fullscreen) {
	// maintians the creation flags
	int creationFlag = 0;

	// if the full screen is set to false, set to windowed mode
	if (!fullscreen) {
		creationFlag = SDL_WINDOW_SHOWN;
	}
	// if true, set to full screen mode
	else {
		creationFlag = SDL_WINDOW_FULLSCREEN;
	}

	// create the SDL window
	sdlWindow = SDL_CreateWindow(title, 
								SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
								width, height,
								creationFlag);

	// if the Window has been created successfully
	// create the renderer and start the game loop
	if (sdlWindow != nullptr && Start()) {
		// debug message if the window has been successfully created
		std::cout << "Create Window - success" << std::endl;

		// start the game loop
		while (!isGameOver) {
			// checks for input from the input
			ProcessInput();

			// any changes to the AI, physics or player movement
			Update();

			// draws on the window
			Draw();
		}
	}

	// debug message if the window has been successfully created
	std::cout << "Create Window - failed" << std::endl;

	// clean up
	ShutDown();
	Destroy();
}


void Game::ShutDown() {
	// TODO: deallocate the stuff you created in Start()
}


void Game::Destroy() {
	// deallocates the SDL_Window*
	SDL_DestroyWindow(sdlWindow);
	sdlWindow = nullptr;
	// deallocates the SDL_Renderer*
	SDL_DestroyRenderer(sdlRenderer);
	sdlRenderer = nullptr;
	// shuts down the SDL framework
	SDL_Quit();
}

// destructor
Game::~Game() {
}

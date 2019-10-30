#include "Game.h"
#include <iostream>
#include <string>
#include "MenuState.h"
#include <SDL_mixer.h>
#include "Input.h"

Game* Game::m_instance = nullptr;

// default constructor
Game::Game() {
	// set the SDL window pointer to null
	sdlWindow = nullptr;
	// set the SDL renderer pointer to null
	sdlRenderer = nullptr;

	// initialize SDL 
	// if the initialization was not successful
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() == -1 || 
		Mix_OpenAudio(192000, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		// disable the game loop
		isGameOver = true;
		// print a failed message on to the console window
		SDL_Log("Initialize SDL - failed");
	}
	// if the initialization was successful
	else {
		// enable to game loop
		isGameOver = false;
		// print a success message on to the console window
		SDL_Log("Initialize SDL - success");
	}
}


Game * Game::GetInstance()
{
	return m_instance;
}

void Game::Create()
{
	if (m_instance == nullptr) {
		m_instance = new Game();
	}
}

SDL_Renderer* Game::GetRenderer() {
	return sdlRenderer;
}

int Game::GetWindowWidth() {
	return m_width;
}

int Game::GetWindowHeight() {
	return m_height;
}

bool Game::Start() {
	// create the renderer for the window created.
	sdlRenderer = SDL_CreateRenderer(sdlWindow, 0, -1);
	if (sdlRenderer != nullptr) {
		SDL_Log("Create Renderer - success");

		// TODO: Initialize objects here
		m_fsm = new FiniteStateMachine();
		// set the initial game state - Menu State
		m_fsm->PushState(new MenuState());

		// Get the current clock time
		lastUpdate = SDL_GetTicks();
		

		// Create an input
		Input::Create();

		return true;
	}
	SDL_Log("Create Renderer - failed");
	return false;
}


void Game::ProcessInput() {
	// calculate deltaTime
	// current time - time since last update
	unsigned int ticks = SDL_GetTicks() - lastUpdate;
	// change this to milliseconds;
	float deltaTime = (ticks / 1000.0f);

	// Get the current time 
	lastUpdate = SDL_GetTicks();
	/*SDL_Log("Deltatime: %f", deltaTime);*/

	// Update the input
	Input::GetInstance()->UpdateInput();

	// TODO: Get the user input here
	m_fsm->GetCurrentState()->HandleInput(deltaTime, m_fsm);

	// Call update after the input
	Update(deltaTime);
}


void Game::Update(float deltaTime) {

	// TODO: update your stuff here
	m_fsm->GetCurrentState()->Update(deltaTime);
}


void Game::Draw() {
	// set the Draw color to black
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
	// clears the render color with the color set above
	SDL_RenderClear(sdlRenderer);

	// TODO: draw your stuff here
	m_fsm->GetCurrentState()->Draw(sdlRenderer);
	

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

	if (sdlWindow == nullptr) {
		// debug message if the window has been successfully created
		SDL_Log("Create Window - failed");
	}
	// if the Window has been created successfully
	// create the renderer and start the game loop
	else {
		// Get the game window dimensions
		SDL_GetWindowSize(sdlWindow, &m_width, &m_height);

		// log messages to print out the width and height of the window
		SDL_Log("Window width: %i", m_width);
		SDL_Log("Window Height: %i", m_height);

		if (Start()) {
			// debug message if the window has been successfully created
			SDL_Log("Create Window - success");

			// start the game loop
			while (!isGameOver) {
				// any changes to the AI, physics or player movement
				ProcessInput();

				// draws on the window
				Draw();
			}
		}
	}

	// clean up
	ShutDown();
	Destroy();
}


void Game::ShutDown() {
	// TODO: deallocate the stuff you created in Start()

	// remove the finite state machine from memory
	if (m_fsm != nullptr) {
		delete m_fsm;
		m_fsm = nullptr;
	}
	// remove input from memory
	Input::Destroy();
}


void Game::Destroy() {
	// deallocates the SDL_Window*
	if (sdlWindow != nullptr) {
		// de-allocate the window
		SDL_DestroyWindow(sdlWindow);
		// reset the pointer to null
		sdlWindow = nullptr;
	}
	// deallocates the SDL_Renderer*
	if (sdlRenderer != nullptr) {
		// de-allocate the renderer
		SDL_DestroyRenderer(sdlRenderer);
		// reset the pointer to null
		sdlRenderer = nullptr;
	}
	// shuts down the SDL framework
	SDL_Quit();

	// shut down the TTF 
	TTF_Quit();

	// shutdown audio
	Mix_CloseAudio();

	// destory this class
	if (m_instance != nullptr) {
		delete m_instance;
		m_instance = nullptr;
	}
}

void Game::Quit()
{
	if (!isGameOver) {
		isGameOver = true;
	}
}

// destructor
Game::~Game() {
}

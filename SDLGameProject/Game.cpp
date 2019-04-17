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
		if (m_playerTexture->LoadPNGFromFile("../assets/braid_run.png", sdlRenderer)) {
			std::cout << "Load player texture - success" << std::endl;
			// initialize player animation
			anim = new Animation(m_playerTexture, 0.03f);
			int texWidth = m_playerTexture->GetImageWidth() / 10;
			int texHeight = m_playerTexture->GetImageHeight() / 3;
			int totalFrames = 26;
			int col = 0;
			int row = 0;
			while (totalFrames >= 0) {
				anim->AddFrame(col * texWidth, row * texHeight, 200, 200);
				++col;
				if (col >= 10) {
					col = 0;
					++row;
				}
				--totalFrames;
			}
		}
		else {
			std::cout << "Load player texture - failed" << std::endl;
			return false;
		}

		Texture* playerTexture = new Texture();
		playerTexture->LoadBMPFromFile("../assets/knight.bmp", sdlRenderer);
		m_player = new Player(playerTexture, Vector2(100, 10));
		
		for (int i = 0; i < 5; ++i) {
			Texture* enemyTexture = new Texture();
			enemyTexture->LoadPNGFromFile("../assets/fighter02.png", sdlRenderer);
			Vector2 pos = Vector2(i * 10, i * 20);
			Enemy* enemy = new Enemy(enemyTexture, pos);
			m_enemies.push_back(enemy);
		}

		// Get the current clock time
		lastUpdate = SDL_GetTicks();

		return true;
	}
	std::cout << "Create Renderer - failed" << std::endl;
	return false;
}


void Game::ProcessInput() {
	// Escape key to exit
	SDL_Event inputEvent;
	if (SDL_PollEvent(&inputEvent)) {
		switch (inputEvent.type) {
		case SDL_KEYDOWN:
			if (inputEvent.key.keysym.sym == SDLK_ESCAPE) {
				isGameOver = true;
			}
		}
	}

	// TODO: Get the user input here
	m_player->Input();

	for (int i = 0; i < m_enemies.size(); ++i) {
		m_enemies[i]->Input();
	}
}


void Game::Update() {

	// calculate deltaTime
	// current time - time since last update
	unsigned int ticks = SDL_GetTicks() - lastUpdate;
	// change this to milliseconds;
	float deltaTime = (ticks / 1000.0f);

	// Get the current time 
	lastUpdate = SDL_GetTicks();
	std::cout << "DeltaTime: " << deltaTime <<  std::endl;

	// TODO: update your stuff here
	anim->Update(deltaTime);
	m_player->Update(deltaTime);

	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr) {
		(*itr)->Update(deltaTime);
	}
}


void Game::Draw() {
	// set the Draw color to black
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
	// clears the render color with the color set above
	SDL_RenderClear(sdlRenderer);

	// TODO: draw your stuff here
	// Render the animation on the screen
	if (anim->GetFrameSize() > 0) {
		anim->Draw(sdlRenderer, 100, 200);
	}
	
	m_player->Draw(sdlRenderer);

	for (GameObject* e : m_enemies) {
		e->Draw(sdlRenderer);
	}

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

	// deallocate animation
	if (anim != nullptr) {
		delete anim;
		anim = nullptr;
	}

	// deallocate player
	if (m_player != nullptr) {
		delete m_player;
		m_player = nullptr;
	}

	// deallocate the array of enemies
	for (auto e : m_enemies) {
		if (e != nullptr) {
			delete e;
			e = nullptr;
		}
	}
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
}

// destructor
Game::~Game() {
}

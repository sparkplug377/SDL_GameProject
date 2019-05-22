#include "Game.h"
#include <iostream>
#include <string>

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

bool Game::Start() {
	// create the renderer for the window created.
	sdlRenderer = SDL_CreateRenderer(sdlWindow, 0, -1);
	if (sdlRenderer != nullptr) {
		SDL_Log("Create Renderer - success");

		// TODO: Initialize objects here

		// initialize player texture
		m_playerTexture = new Texture();
		// load the texture
		if (m_playerTexture->LoadPNGFromFile("../assets/braid_run.png", sdlRenderer)) {
			SDL_Log("Load player texture - success");
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
			SDL_Log("Load player texture - failed");
			return false;
		}

		Texture* playerTexture = new Texture();
		if (playerTexture->LoadPNGFromFile("../assets/ship.png", sdlRenderer)) {
			SDL_Log("Load ship texture - success");

			m_player = new Player(playerTexture, Vector2(200, 100));

			for (int i = 0; i < 5; ++i) {
				Texture* enemyTexture = new Texture();
				enemyTexture->LoadPNGFromFile("../assets/fighter02.png", sdlRenderer);
				Vector2 pos = Vector2(i * 10, i * 20);
				Enemy* enemy = new Enemy(enemyTexture, pos);
				m_enemies.push_back(enemy);
			}
		}
		else {
			SDL_Log("Load ship texture - failed");
		}

		// load font
		// initialize the text texture
		m_textTexture = new Texture();
		
		// load the font with size
		m_font = TTF_OpenFont("../assets/PressStart2P.ttf", 15);

		// Get the current clock time
		lastUpdate = SDL_GetTicks();
		
		// load audio
		m_backAudio = Mix_LoadMUS("../assets/audio.mp3");
		if (m_backAudio != nullptr)
		{
			if (Mix_PlayingMusic() == 0)
			{
				if (Mix_PlayMusic(m_backAudio, 0) == -1) {
					return false;
				}
			}
		}
		else
		{
			return false;
		}

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
	SDL_Log("Deltatime: %f", deltaTime);

	// Update the input
	Input::GetInstance()->UpdateInput();

	// press escape to exit
	if (Input::GetInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
		Quit();
	}

	// TODO: Get the user input here
	
	// process input from the player
	m_player->HandleInput(deltaTime);

	// Call update after the input
	Update(deltaTime);
}


void Game::Update(float deltaTime) {

	// TODO: update your stuff here
	anim->Update(deltaTime);
	m_player->Update(deltaTime);

	// Check player-enemy collision
	PECollisionCheck();

	// check if the font has successfully loaded
	if (m_font != nullptr)
	{
		// color of the font
		SDL_Color color = { 255, 125 , 0, 255 };
		// rendering text
		std::string sPosX = std::to_string((int)m_player->GetPosition().x);
		std::string sPosY = std::to_string((int)m_player->GetPosition().y);
		if (!m_textTexture->RenderText(("Player Pos, x: " + sPosX + ", y: " + sPosY).c_str(),
			m_font, sdlRenderer, color)) {
		}
	}
	
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
	
	SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255);
	m_player->Draw(sdlRenderer);

	for (GameObject* e : m_enemies) {
		e->Draw(sdlRenderer);
	}

	// draw text texture
	m_textTexture->Draw(sdlRenderer, 0, 575);

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
		SDL_Log("Create Window - success");

		// start the game loop
		while (!isGameOver) {
			// any changes to the AI, physics or player movement
			ProcessInput();

			// draws on the window
			Draw();
		}
	}

	// debug message if the window has been successfully created
	SDL_Log("Create Window - failed");

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

	// remove input from memory
	Input::Destroy();

	// remove font from memory
	if (m_textTexture != nullptr)
	{
		delete m_textTexture;
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

void Game::PECollisionCheck()
{
	// collision check between player and enemy
	if (m_player->GetCollider())
	{
		for (auto itr = m_enemies.end(); itr != m_enemies.begin();) {
			--itr;
			if ((*itr) != nullptr && m_player->GetCollider()->RectangleCollision(*(*itr)->GetCollider())) {
				delete *itr;
				*itr = nullptr;
				itr = m_enemies.erase(itr);
			}
		}
	}
}

// destructor
Game::~Game() {
}

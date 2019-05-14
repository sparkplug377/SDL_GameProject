#pragma once

#include "Animation.h"
#include "Player.h"
#include "Enemy.h"

class Game {
public:
	static Game* GetInstance();

	// Engine Functions =====================================================================

	// @brief creates an instance of this class
	static void Create();

	// @brief	creates the renderer 
	//			Intial allocations of the objects are done here 
	bool Start();
	
	// @brief	handles any user input has happened since the last call 
	void ProcessInput();

	// @brief	advances the game simulation, it runs AI, Physics, player movement
	void Update();

	// @brief	draws the game so the player can see what happened
	void Draw();

	// @brief	deallocates the objects created
	void ShutDown();

	// @brief	creates a window and begin the game loop
	//			it first calls the start once and after it is successful,
	//			it calls the ProcessInput(), Update() and Draw() in the game loop, and
	//			ends with calling ShutDown() after the game loop has ended.
	// @param title - title for the window
	// @param width - width of the window
	// @param height - height of the window
	// @param fullscreen - enables or disables fullscreen for the window
	void Run(char* title, int width, int height, bool fullscreen);

	// @brief	delete the window and the renderer when closing the application
	//			shutdown the SDL framework
	void Destroy();

	// @brief	returns if the game loop has ended
	void Quit();

	// Game Functions =====================================================================
	// @brief	player and enemy collision check
	void PECollisionCheck();


	~Game();

private:
	Game();
	// Singleton instance of this class
	static Game* m_instance;

	// the window we will be rendering to
	SDL_Window* sdlWindow;
	// 2D rendering context for a window
	SDL_Renderer* sdlRenderer;

	// flag for the game loop
	bool isGameOver;
	// gets the current time since last update
	unsigned int lastUpdate;

	// player texture
	Texture* m_playerTexture;
	// Animating the player
	Animation* anim;

	// creating a player
	Player* m_player;

	// creating enemies
	std::vector<Enemy*> m_enemies;
 };


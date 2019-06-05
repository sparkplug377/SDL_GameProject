#pragma once
#include "State.h"
#include "Animation.h"
#include "Player.h"
#include "Enemy.h"
#include <SDL_mixer.h>
class GameState : public State {
public:
	GameState();

	// Initializes all the variables
	virtual void OnEnter();

	// @brief	handles any user input has happened since the last call 
	virtual void HandleInput(float deltaTime, FiniteStateMachine* fsm);

	// @brief	updates every frame
	virtual void Update(float deltaTime);

	// @brief	render objects on to the screen
	virtual void Draw(SDL_Renderer* renderer);

	// cleans up the memory
	virtual void OnExit();


	~GameState();

private:
	// @brief	player and enemy collision check
	void PECollisionCheck();

	// Animating the player
	Animation* anim;

	// creating a player
	Player* m_player;

	// creating enemies
	std::vector<Enemy*> m_enemies;

	// font
	TTF_Font* m_font;
	Texture* m_textTexture;

	// music
	Mix_Music* m_backAudio = nullptr;
};


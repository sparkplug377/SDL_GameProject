#pragma once
#include "State.h"
#include "Texture.h"

class MenuState : public State {
public:
	MenuState();

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

	~MenuState();

private:
	Texture* m_textTexture;
	TTF_Font* m_font;
};


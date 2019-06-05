#pragma once
#include "SDL.h"
class FiniteStateMachine;
class State {
public:
	State() {}

	// Initializes all the variables
	virtual void OnEnter() = 0;

	// @brief	handles any user input has happened since the last call 
	virtual void HandleInput(float deltaTime, FiniteStateMachine* fsm) = 0;

	// @brief	updates every frame
	virtual void Update(float deltaTime) = 0;

	// @brief	render objects on to the screen
	virtual void Draw(SDL_Renderer* renderer) = 0;

	// cleans up the memory
	virtual void OnExit() = 0;

	~State() {}
};


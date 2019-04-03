#pragma once
#include <SDL.h>
class GameObject {
public:
	GameObject();
	
	virtual void ProcessInput() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(SDL_Renderer* renderer, int posX, int posY) = 0;
	virtual void Clean() = 0;

	~GameObject();
	
protected:
	SDL_Point position;
};


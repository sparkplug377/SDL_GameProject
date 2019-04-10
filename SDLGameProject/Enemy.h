#pragma once
#include "GameObject.h"
class Enemy : public GameObject{
public:
	Enemy();
	Enemy(Texture* texture, int posX, int posY);
	virtual void Draw(SDL_Renderer* renderer);
	virtual void Update(float deltaTime);
	virtual void Input();
	~Enemy();
};


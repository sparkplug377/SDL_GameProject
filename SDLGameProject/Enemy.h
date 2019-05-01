#pragma once
#include "GameObject.h"
class Enemy : public GameObject{
public:
	Enemy();
	Enemy(Texture* texture, Vector2 pos);
	virtual void Draw(SDL_Renderer* renderer);
	virtual void Update(float deltaTime);
	virtual void HandleInput();
	~Enemy();
};


#pragma once
#include "GameObject.h"
class Player :
	public GameObject {
public:
	Player();
	Player(Texture* texture, int posX, int posY);

	void Update(float deltaTime)override;
	void Draw(SDL_Renderer* renderer) override;
	void Input() override;

	~Player();
};


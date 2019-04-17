#pragma once
#include "GameObject.h"
class Player :
	public GameObject {
public:
	Player();
	Player(Texture* texture, Vector2 pos);

	void Update(float deltaTime)override;
	void Draw(SDL_Renderer* renderer) override;
	void Input() override;

	void SetForce(Vector2 force);
	Vector2 GetVelocity();

	~Player();
private:
	Vector2 m_velocity;
	Vector2 m_acceleration;
};


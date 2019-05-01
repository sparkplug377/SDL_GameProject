#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Input.h"
class Player :
	public GameObject {
public:
	Player();
	Player(Texture* texture, Vector2 pos);

	void Update(float deltaTime)override;
	void Draw(SDL_Renderer* renderer) override;
	void HandleInput() override;

	void SetForce(Vector2 force);
	Vector2 GetVelocity();

	~Player();

private:
	Vector2 m_velocity;
	Vector2 m_acceleration;
	Input*	m_input;
};

#endif
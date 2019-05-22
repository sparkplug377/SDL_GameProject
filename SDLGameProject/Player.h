#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "Input.h"
#include "AABB.h"

class Player :
	public GameObject {

public:
	// @brief	default constructor
	Player();
	// @brief	overloaded constructor
	Player(Texture* texture, Vector2 pos);

	void Update(float deltaTime)override;
	void Draw(SDL_Renderer* renderer) override;
	void HandleInput(float deltaTime) override;

	// @brief	adds acceleration
	void SetForce(Vector2 force);
	// @brief	retuns player's velocity
	Vector2 GetVelocity();

	// @brief	returns player's position
	const Vector2 GetPosition() const;

	// @brief	returns collider 
	AABB* GetCollider();

	~Player();

private:
	Vector2 m_velocity;
	Vector2 m_acceleration;
	Input*	m_input;
	AABB*	m_collider;
	float	m_maxVelocity;

	// for rotation
	float	m_rotation;
};

#endif
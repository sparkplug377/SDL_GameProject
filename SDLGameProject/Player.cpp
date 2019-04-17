#include "Player.h"
#include <iostream>


Player::Player() {
	m_position = Vector2(0, 0);
	m_acceleration = Vector2(0, 0);
	m_texture = nullptr;
	std::cout << "player constructor" << std::endl;
}

Player::Player(Texture * texture, Vector2 pos) {
	m_texture = texture;
	this->m_position = pos;
	m_acceleration = Vector2(0, 0);
}

void Player::Update(float deltaTime) {
	SetForce(m_velocity * -0.15f);
	m_velocity = m_velocity + m_acceleration * deltaTime;
	m_position = m_position + m_velocity * deltaTime;
	m_acceleration = Vector2(0, 0);
	//std::cout << m_position.x << ", " << m_position.y << std::endl;
}

void Player::Draw(SDL_Renderer* renderer) {
	m_texture->Draw(renderer, m_position.x, m_position.y);
}

void Player::Input() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_w) {
				SetForce(Vector2(0, -1000));
			}
			if (event.key.keysym.sym == SDLK_s) {
				SetForce(Vector2(0, 1000));
			}
			if (event.key.keysym.sym == SDLK_a) {
				SetForce(Vector2(-1000, 0));
			}
			if (event.key.keysym.sym == SDLK_d) {
				SetForce(Vector2(1000, 0));
			}
		}
	}
}

void Player::SetForce(Vector2 force)
{
	m_acceleration = m_acceleration + force;
}

Vector2 Player::GetVelocity()
{
	return m_velocity;
}

Player::~Player() {
	std::cout << "player destructor" << std::endl;
}

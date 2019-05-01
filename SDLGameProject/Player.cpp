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

void Player::HandleInput() {
	m_input = Input::GetInstance();
	if (m_input->IsKeyDown(SDL_SCANCODE_W)) {
		SetForce(Vector2(0, -100));
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_S)) {
		SetForce(Vector2(0, 100));
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_A)) {
		SetForce(Vector2(-100, 0));
	}
	if (m_input->IsKeyDown(SDL_SCANCODE_D)) {
		SetForce(Vector2(100, 0));
	}
	int x = 0;
	int y = 0;
	m_input->GetMousePos(&x, &y);

	if (m_input->IsMouseUp(MOUSE_BUTTON_LEFT)) {
		SetForce(Vector2(x - m_position.x, y - m_position.y));
	}

	//std::cout << x << ", " << y << std::endl;
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

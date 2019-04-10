#include "Player.h"
#include <iostream>


Player::Player() {
	m_positionX = 0;
	m_positionY = 0;
	m_texture = nullptr;
	std::cout << "player constructor" << std::endl;
}

Player::Player(Texture * texture, int posX, int posY) {
	m_texture = texture;
	m_positionX = posX;
	m_positionY = posY;
}

void Player::Update(float deltaTime) {
}

void Player::Draw(SDL_Renderer* renderer) {
	m_texture->Draw(renderer, m_positionX, m_positionY);
}

void Player::Input() {
}

Player::~Player() {
	std::cout << "player destructor" << std::endl;
}

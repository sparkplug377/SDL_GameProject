#include "Enemy.h"
#include <iostream>


Enemy::Enemy() {
	m_positionX = 0;
	m_positionY = 0;
	m_texture = nullptr;
	std::cout << "Enemy constructor" << std::endl;
}

Enemy::Enemy(Texture * texture, int posX, int posY) {
	m_texture = texture;
	m_positionX = posX;
	m_positionY = posY;
}

void Enemy::Draw(SDL_Renderer * renderer) {
	m_texture->Draw(renderer, m_positionX, m_positionY);
}

void Enemy::Update(float deltaTime) {
	m_positionX += 100.0f * deltaTime;
}

void Enemy::Input() {
}


Enemy::~Enemy() {
	std::cout << "Enemy destructor" << std::endl;

}

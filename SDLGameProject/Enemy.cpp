#include "Enemy.h"
#include <iostream>


Enemy::Enemy() {
	m_position = Vector2(0, 0);
	m_texture = nullptr;
	std::cout << "Enemy constructor" << std::endl;
}

Enemy::Enemy(Texture * texture, Vector2 pos) {
	m_texture = texture;
	this->m_position = pos;
}

void Enemy::Draw(SDL_Renderer * renderer) {
	m_texture->Draw(renderer, m_position.x, m_position.y);
}

void Enemy::Update(float deltaTime) {
}

void Enemy::HandleInput() {
}


Enemy::~Enemy() {
	std::cout << "Enemy destructor" << std::endl;

}

#include "Enemy.h"
#include <iostream>


Enemy::Enemy() {
	m_position = Vector2(0, 0);
	m_texture = nullptr;
	std::cout << "Enemy constructor" << std::endl;
	m_collider = nullptr;
}

Enemy::Enemy(Texture * texture, Vector2 pos) {
	m_texture = texture;
	this->m_position = pos;
	m_collider = new AABB(m_position, m_texture->GetImageWidth(), m_texture->GetImageHeight());
}

void Enemy::Draw(SDL_Renderer * renderer) {
	m_texture->Draw(renderer, m_position.x, m_position.y);

	SDL_Rect rect = { m_collider->GetPosition().x, m_collider->GetPosition().y, 
						m_collider->GetWidth(), m_collider->GetHeight()};
	SDL_RenderDrawRect(renderer, &rect);
}

void Enemy::Update(float deltaTime) {
}

void Enemy::HandleInput() {
}


Enemy::~Enemy() {
	std::cout << "Enemy destructor" << std::endl;
	// delete AABB
	if (m_collider != nullptr) {
		delete m_collider;
		m_collider = nullptr;
	}
}

AABB * Enemy::GetCollider()
{
	return m_collider;
}

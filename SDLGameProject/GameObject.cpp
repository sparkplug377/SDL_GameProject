#include "GameObject.h"


GameObject::GameObject() {
	SDL_Log("gameobject constructor");
	m_position = Vector2(0, 0);
	m_texture = nullptr;
}


GameObject::~GameObject() {
	SDL_Log("gameobject destructor");
	if (m_texture != nullptr) {
		delete m_texture;
		m_texture = nullptr;
	}

}

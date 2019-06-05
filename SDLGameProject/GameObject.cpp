#include "GameObject.h"


GameObject::GameObject() {
	SDL_Log("gameobject constructor");
	m_position = Vector2(0, 0);
	m_texture = nullptr;
}


GameObject::~GameObject() {

}

#include "GameObject.h"
#include <iostream>


GameObject::GameObject() {
	std::cout << "gameobject constructor" << std::endl;
	m_positionX = 0;
	m_positionY = 0;
	m_texture = nullptr;
}


GameObject::~GameObject() {
	std::cout << "gameobject destructor" << std::endl;
	if (m_texture != nullptr) {
		delete m_texture;
		m_texture = nullptr;
	}

}

#include "Enemy.h"
#include <iostream>


Enemy::Enemy() {
	m_positionX = 0;
	m_positionY = 0;
	m_texture = nullptr;
	std::cout << "Enemy constructor" << std::endl;
}


Enemy::~Enemy() {
	std::cout << "Enemy destructor" << std::endl;

}

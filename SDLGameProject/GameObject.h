#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Texture.h"

class GameObject {
public:
	GameObject();
	~GameObject();

	virtual void Draw(SDL_Renderer* renderer) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Input() = 0;

protected:
	int m_positionX;
	int m_positionY;
	Texture* m_texture;
};
#endif

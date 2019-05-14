#pragma once
#include "Vector2.h"

class AABB;

class Circle
{
public:
	Circle();
	Circle(Vector2 position, int radius);
	~Circle();
	// @breif returns pos of the circle
	const Vector2 GetPosition() const;
	// @breif returns the radius of the circle
	const int GetRadius() const;
	// @breif checks if mouse collided with circle
	bool PointCollision(Vector2 point);
	// @brief check if a circle collided with another circle
	bool CircleCollision(const Circle& c);

	// @brief update circle
	void Update(Vector2 newPosition);

private:
	int m_radius;
	Vector2 m_position;
};


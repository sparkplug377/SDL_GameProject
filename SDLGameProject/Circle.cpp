#include "Circle.h"
#include "AABB.h"


Circle::Circle()
{
}

Circle::Circle(Vector2 position, int radius)
{
	m_position = position;
	m_radius = radius;
}


Circle::~Circle()
{
}

const Vector2 Circle::GetPosition() const
{
	return m_position;
}

const int Circle::GetRadius() const
{
	return m_radius;
}

bool Circle::PointCollision(Vector2 point)
{
	Vector2 distance;
	distance.x = point.x - m_position.x;
	distance.y = point.y - m_position.y;
	float length = distance.Magnitude();
	if (length <= m_radius)
	{
		return true;
	}
	return false;
}

bool Circle::CircleCollision(const Circle & c)
{
	Vector2 distance;
	distance.x = c.GetPosition().x - m_position.x;
	distance.y = c.GetPosition().y - m_position.y;
	int length = distance.Magnitude();

	if (length <= (m_radius + c.GetRadius()));
	{
		return true;
	}

	return false;
}

void Circle::Update(Vector2 newPosition)
{
	m_position = newPosition;
}

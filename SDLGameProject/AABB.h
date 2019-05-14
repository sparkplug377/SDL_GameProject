#ifndef AABB_H_
#define AABB_H_
#include "Vector2.h"

class Circle;

class AABB
{
public:
	AABB();
	AABB(Vector2 position, int width, int height);
	~AABB();

	// @brief returns position of the bounding box
	const Vector2 GetPosition() const;

	// @brief returns width of the bounding box
	const int GetWidth() const;

	// @brief returns height of the bounding box
	const int GetHeight() const;

	// @brief check if a point collides with a rectangle
	bool PointCollision(Vector2 point);

	// @brief check if a rectangle collides with a rectangle
	bool RectangleCollision(const AABB & rect);

	// @brief check if a circle collides with a rectangle
	bool CircleCollision(const Circle& c);

	// @brief update AABB
	void Update(Vector2 position);


private:
	Vector2 m_position;
	int m_width;
	int m_height;
};

#endif

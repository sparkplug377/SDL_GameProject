#ifndef VECTOR2_H_
#define VECTOR2_H_
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);

	// adds two vectors
	Vector2 operator+ (const Vector2& anotherVector);
	void operator+= (const Vector2& anotherVector);

	// subtracts two vectors
	Vector2 operator- (const Vector2& anotherVector);
	Vector2 operator-= (const Vector2& anotherVector);

	// multiplying a scalar value with a vector
	Vector2 operator* (const float& scalarValue);

	// assigns another operator
	void operator= (const Vector2& anotherVector);

	// calculates the length of the vector
	float Magnitude();

	// calulate the normalized vector
	void Normalize();
	~Vector2();

public:
	float x;
	float y;
};
#endif

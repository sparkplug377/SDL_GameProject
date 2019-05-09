#include "Vector2.h"
#include <math.h>


Vector2::Vector2() : x(0), y(0){ }

Vector2::Vector2(float x, float y){
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator+(const Vector2 & anotherVector){
	return Vector2(this->x + anotherVector.x, this->y + anotherVector.y);
}

void Vector2::operator+=(const Vector2 & anotherVector){
	this->x += anotherVector.x;
	this->y += anotherVector.y;
}

Vector2 Vector2::operator-(const Vector2 & anotherVector){
	return Vector2(this->x - anotherVector.x, this->y - anotherVector.y);
}

Vector2 Vector2::operator-=(const Vector2 & anotherVector){
	this->x -= anotherVector.x;
	this->y -= anotherVector.y;
	return *this;
}

Vector2 Vector2::operator*(const float & scalarValue){
	return Vector2(this->x * scalarValue, this->y * scalarValue);
}

void Vector2::operator=(const Vector2 & anotherVector){
	this->x = anotherVector.x;
	this->y = anotherVector.y;
}

float Vector2::Magnitude(){
	float mag = 0.0f;
	mag = sqrtf(x * x + y * y);
	return mag;
}

void Vector2::Normalize(){
	float mag = 0.0f;
	mag = sqrtf(x * x + y * y);
	this->x /= mag;
	this->y /= mag;
}

Vector2::~Vector2(){
}

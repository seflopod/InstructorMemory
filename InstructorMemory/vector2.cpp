#ifndef _VECTOR2_H_
#include "vector2.h"
#endif

//static methods
float Vector2::dotProduct(Vector2 a, Vector2 b)
{
	return a.x*b.x + a.y*b.y;
}

Vector2 Vector2::normalize(Vector2 v)
{
	return v/v.magnitude();
}

//non-static methods
Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}
	
Vector2::Vector2(float fill)
{
	x = fill;
	y = fill;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

//returns the vector as an array, because I guess that's sometimes handy.
float* Vector2::toArray()
{
	float ret[2] = {x, y};
	return ret;
}

float Vector2::sqrMagnitude()
{
	return x*x + y*y;
}

float Vector2::magnitude()
{
	return sqrt(x*x+y*y);
}

//Operator overloads
Vector2& Vector2::operator=(const Vector2 &rhs)
{
	if(this == &rhs) //check self-assignment
		return *this;

	this->x = rhs.x;
	this->y = rhs.y;

	return *this;
}

//Vector addition and substraction maths
Vector2& Vector2::operator+=(const Vector2 &rhs)
{
	this->x+=rhs.x;
	this->y+=rhs.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2 &rhs)
{
	this->x-=rhs.x;
	this->y-=rhs.y;
	return *this;
}

const Vector2 Vector2::operator+(const Vector2 &rhs) const
{
	Vector2 ret = *this;
	ret+=rhs;
	return ret;
}

const Vector2 Vector2::operator-(const Vector2 &rhs) const
{
	Vector2 ret = *this;
	ret-=rhs;
	return ret;
}

//scalar multiplication
Vector2& Vector2::operator*=(const float &rhs)
{
	this->x*=rhs;
	this->y*=rhs;

	return *this;
}

const Vector2 Vector2::operator*(const float &rhs) const
{
	Vector2 ret = *this;
	ret*=rhs;
	return ret;
}

//scalar division
Vector2& Vector2::operator/=(const float &rhs)
{
	this->x/=rhs;
	this->y/=rhs;

	return *this;
}

const Vector2 Vector2::operator/(const float &rhs) const
{
	Vector2 ret = *this;
	ret*=rhs;
	return ret;
}

//Equality check
bool Vector2::operator==(const Vector2 &rhs)
{
	return (this->x==rhs.x && this->y==rhs.y);
}

bool Vector2::operator!=(const Vector2 &rhs)
{
	return !(*this==rhs);
}

//Ostream overload
std::ostream& operator<<(std::ostream& s, const Vector2& v)
{
	s << "(" << v.x << ", " << v.y << ")";
	return s;
}
#ifndef _VECTOR3_H_
#include "vector3.h"
#endif

//static methods
Vector3 Vector3::crossProduct(Vector3 a, Vector3 b)
{
	return Vector3(a.y*b.z - a.z*b.y,
					a.z*b.x - a.x*b.z,
					a.x*b.y - a.y*b.x);
}

float Vector3::dotProduct(Vector3 a, Vector3 b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector3 Vector3::normalize(Vector3 v)
{
	return v/v.magnitude();
}

//non-static methods
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
	
Vector3::Vector3(float fill)
{
	x = fill;
	y = fill;
	z = fill;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//returns the vector as an array, because I guess that's sometimes handy.
float* Vector3::toArray()
{
	float ret[3] = {x, y, z};
	return ret;
}

float Vector3::magnitude()
{
	return sqrt(x*x+y*y+z*z);
}

//Operator overloads
Vector3& Vector3::operator=(const Vector3 &rhs)
{
	if(this == &rhs) //check self-assignment
		return *this;

	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;

	return *this;
}

//Vector addition and substraction maths
Vector3& Vector3::operator+=(const Vector3 &rhs)
{
	this->x+=rhs.x;
	this->y+=rhs.y;
	this->z+=rhs.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3 &rhs)
{
	this->x-=rhs.x;
	this->y-=rhs.y;
	this->z-=rhs.z;
	return *this;
}

const Vector3 Vector3::operator+(const Vector3 &rhs) const
{
	Vector3 ret = *this;
	ret+=rhs;
	return ret;
}

const Vector3 Vector3::operator-(const Vector3 &rhs) const
{
	Vector3 ret = *this;
	ret-=rhs;
	return ret;
}

//scalar multiplication
Vector3& Vector3::operator*=(const float &rhs)
{
	this->x*=rhs;
	this->y*=rhs;
	this->z*=rhs;

	return *this;
}

const Vector3 Vector3::operator*(const float &rhs) const
{
	Vector3 ret = *this;
	ret*=rhs;
	return ret;
}

//scalar division
Vector3& Vector3::operator/=(const float &rhs)
{
	this->x/=rhs;
	this->y/=rhs;
	this->z/=rhs;

	return *this;
}

const Vector3 Vector3::operator/(const float &rhs) const
{
	Vector3 ret = *this;
	ret*=rhs;
	return ret;
}

//Equality check
bool Vector3::operator==(const Vector3 &rhs)
{
	return (this->x==rhs.x && this->y==rhs.y && this->z==rhs.z);
}

bool Vector3::operator!=(const Vector3 &rhs)
{
	return !(*this==rhs);
}

//Ostream overload
std::ostream& operator<<(std::ostream& s, const Vector3& v)
{
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return s;
}
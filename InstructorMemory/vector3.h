/*vector3.h
 * Peter Bartosch
 * created: sometime a few weeks back
 * last modified: 4/15/2013
 *
 * defines class: Vector3
 * Vector3 should make the use of three-element vectors a easier.  Standard
 * vector maths included, though I don't have overloads for scalar maths where
 * the vector is an rvalue.  This grew to the point where managing the single
 * header file was getting a little bothersome, so split into header and
 * implementation.
 *
 */
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>
#include <iostream>

class Vector3
{
public:
	static Vector3 crossProduct(Vector3 a, Vector3 b);
	static float dotProduct(Vector3 a, Vector3 b);
	static Vector3 normalize(Vector3 v);

	float x;
	float y;
	float z;

	Vector3();
	Vector3(float fill);
	Vector3(float x, float y, float z);

	float* toArray();
	float magnitude();

	//Operator overloads
	Vector3& operator=(const Vector3 &rhs);
	Vector3& operator+=(const Vector3 &rhs);
	Vector3& operator-=(const Vector3 &rhs);
	const Vector3 operator+(const Vector3 &rhs) const;
	const Vector3 operator-(const Vector3 &rhs) const;
	
	//scalar multiplication and division
	Vector3& operator*=(const float &rhs);
	const Vector3 operator*(const float &rhs) const;
	Vector3& operator/=(const float &rhs);
	const Vector3 operator/(const float &rhs) const;

	//equality checks
	bool operator==(const Vector3 &rhs);
	bool operator!=(const Vector3 &rhs);

	//Ostream overload
	friend std::ostream& operator<<(std::ostream& s, const Vector3& v);
};
#endif
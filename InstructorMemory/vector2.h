/*vector2.h
 * Peter Bartosch
 * created: 4/15/2013
 * last modified: 4/15/2013
 *
 * class defined: Vector2
 * A Vector2 represents a vector on a plane.  At this point I should maybe just
 * switch to glm, but rather than learn it now I will stick with custom vector
 * classes.  Vector2 should include all standard vector maths.  This was created
 * after I made Vector3, and rather than refactor and do some inheritance, I am
 * simply rewriting code.  A little faster for right now.
 *
 */
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <math.h>
#include <iostream>

class Vector2
{
public:
	static float dotProduct(Vector2 a, Vector2 b);
	static Vector2 normalize(Vector2 v);

	float x;
	float y;

	Vector2();
	Vector2(float fill);
	Vector2(float x, float y);

	float* toArray();
	float sqrMagnitude();
	float magnitude();

	//Operator overloads
	Vector2& operator=(const Vector2 &rhs);
	Vector2& operator+=(const Vector2 &rhs);
	Vector2& operator-=(const Vector2 &rhs);
	const Vector2 operator+(const Vector2 &rhs) const;
	const Vector2 operator-(const Vector2 &rhs) const;
	
	//scalar multiplication and division
	Vector2& operator*=(const float &rhs);
	const Vector2 operator*(const float &rhs) const;
	Vector2& operator/=(const float &rhs);
	const Vector2 operator/(const float &rhs) const;

	//equality checks
	bool operator==(const Vector2 &rhs);
	bool operator!=(const Vector2 &rhs);

	//Ostream overload
	friend std::ostream& operator<<(std::ostream& s, const Vector2& v);
};
#endif
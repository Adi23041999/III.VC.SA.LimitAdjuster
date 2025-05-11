/*
* Copyright (c) re3
*/

#pragma once
#include "math.h"

typedef float float32;

inline float Sin(float x) { return sinf(x); }
inline float Asin(float x) { return asinf(x); }
inline float Cos(float x) { return cosf(x); }
inline float Acos(float x) { return acosf(x); }
inline float Tan(float x) { return tanf(x); }
inline float Atan(float x) { return atanf(x); }
inline float Atan2(float y, float x) { return atan2f(y, x); }
inline float Abs(float x) { return fabsf(x); }
inline float Sqrt(float x) { return sqrtf(x); }
inline float RecipSqrt(float x, float y) { return x / Sqrt(y); }
inline float RecipSqrt(float x) { return RecipSqrt(1.0f, x); }
inline float Pow(float x, float y) { return powf(x, y); }
inline float Floor(float x) { return floorf(x); }
inline float Ceil(float x) { return ceilf(x); }

namespace rw
{
struct V3d
{
	float32 x, y, z;
	void set(float32 x, float32 y, float32 z) {
		this->x = x; this->y = y; this->z = z;
	}

};
};

typedef rw::V3d RwV3d;

class CVector : public RwV3d
{
public:
	CVector(void) {}
	CVector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	CVector(const RwV3d& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	// (0,1,0) means no rotation. So get right vector and its atan
	float Heading(void) const { return Atan2(-x, y); }
	float Magnitude(void) const { return Sqrt(x * x + y * y + z * z); }
	float MagnitudeSqr(void) const { return x * x + y * y + z * z; }
	float Magnitude2D(void) const { return Sqrt(x * x + y * y); }
	float MagnitudeSqr2D(void) const { return x * x + y * y; }
	void Normalise(void);

	void Normalise2D(void) {
		float sq = MagnitudeSqr2D();
		float invsqrt = RecipSqrt(sq);
		x *= invsqrt;
		y *= invsqrt;
	}

	const CVector& operator+=(CVector const& right) {
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	const CVector& operator-=(CVector const& right) {
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	const CVector& operator*=(float right) {
		x *= right;
		y *= right;
		z *= right;
		return *this;
	}

	const CVector& operator/=(float right) {
		x /= right;
		y /= right;
		z /= right;
		return *this;
	}

	CVector operator-() const {
		return CVector(-x, -y, -z);
	}

	const bool operator==(CVector const& right) {
		return x == right.x && y == right.y && z == right.z;
	}

	const bool operator!=(CVector const& right) {
		return x != right.x || y != right.y || z != right.z;
	}

	bool IsZero(void) const { return x == 0.0f && y == 0.0f && z == 0.0f; }
};

inline CVector operator+(const CVector& left, const CVector& right)
{
	return CVector(left.x + right.x, left.y + right.y, left.z + right.z);
}

inline CVector operator-(const CVector& left, const CVector& right)
{
	return CVector(left.x - right.x, left.y - right.y, left.z - right.z);
}

inline CVector operator*(const CVector& left, float right)
{
	return CVector(left.x * right, left.y * right, left.z * right);
}

inline CVector operator*(float left, const CVector& right)
{
	return CVector(left * right.x, left * right.y, left * right.z);
}

inline CVector operator/(const CVector& left, float right)
{
	return CVector(left.x / right, left.y / right, left.z / right);
}

inline float
DotProduct(const CVector& v1, const CVector& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

CVector CrossProduct(const CVector& v1, const CVector& v2);

inline float
Distance(const CVector& v1, const CVector& v2)
{
	return (v2 - v1).Magnitude();
}

inline float
Distance2D(const CVector& v1, const CVector& v2)
{
	float x = v2.x - v1.x;
	float y = v2.y - v1.y;
	return Sqrt(x * x + y * y);
}

class CMatrix;

CVector Multiply3x3(const CMatrix& mat, const CVector& vec);
CVector Multiply3x3(const CVector& vec, const CMatrix& mat);
CVector operator*(const CMatrix& mat, const CVector& vec);

class CVector2D
{
public:
	float x, y;
	CVector2D(void) {}
	CVector2D(float x, float y) : x(x), y(y) {}
	CVector2D(const CVector& v) : x(v.x), y(v.y) {}
	float Heading(void) const { return Atan2(-x, y); }
	float Magnitude(void) const { return Sqrt(x * x + y * y); }
	float MagnitudeSqr(void) const { return x * x + y * y; }

	void Normalise(void) {
		float sq = MagnitudeSqr();
		// assert(sq != 0.0f);	// just be safe here
		float invsqrt = RecipSqrt(sq);
		x *= invsqrt;
		y *= invsqrt;
	}

	void NormaliseSafe(void) {
		float sq = MagnitudeSqr();
		if (sq > 0.0f) {
			float invsqrt = RecipSqrt(sq);
			x *= invsqrt;
			y *= invsqrt;
		}
		else
			x = 1.0f;
	}

	const CVector2D& operator+=(CVector2D const& right) {
		x += right.x;
		y += right.y;
		return *this;
	}

	const CVector2D& operator-=(CVector2D const& right) {
		x -= right.x;
		y -= right.y;
		return *this;
	}

	const CVector2D& operator*=(float right) {
		x *= right;
		y *= right;
		return *this;
	}

	const CVector2D& operator/=(float right) {
		x /= right;
		y /= right;
		return *this;
	}
	CVector2D operator-(const CVector2D& rhs) const {
		return CVector2D(x - rhs.x, y - rhs.y);
	}
	CVector2D operator+(const CVector2D& rhs) const {
		return CVector2D(x + rhs.x, y + rhs.y);
	}
	CVector2D operator/(float t) const {
		return CVector2D(x / t, y / t);
	}
};

inline float
DotProduct2D(const CVector2D& v1, const CVector2D& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

inline float
CrossProduct2D(const CVector2D& v1, const CVector2D& v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

inline float
Distance2D(const CVector2D& v, float x, float y)
{
	return Sqrt((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
}

inline float
DistanceSqr2D(const CVector2D& v, float x, float y)
{
	return (v.x - x) * (v.x - x) + (v.y - y) * (v.y - y);
}

inline void
NormalizeXY(float& x, float& y)
{
	float l = Sqrt(x * x + y * y);
	if (l != 0.0f) {
		x /= l;
		y /= l;
	}
	else
		x = 1.0f;
}

inline CVector2D operator*(const CVector2D& left, float right)
{
	return CVector2D(left.x * right, left.y * right);
}

inline CVector2D operator*(float left, const CVector2D& right)
{
	return CVector2D(left * right.x, left * right.y);
}

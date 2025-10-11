/*
* Copyright (c) re3
*/

#pragma once
#include "CVector2D.h"

typedef uint8_t uint8;
typedef int8_t int8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef int32_t int32;

#define FIX_BUGS
#define Max(a,b) ((a) > (b) ? (a) : (b))
#define Min(a,b) ((a) < (b) ? (a) : (b))
#define TWOPI (PI*2)
#define HALFPI (PI/2)
#define DEGTORAD(x) ((x) * PI / 180.0f)
#define RADTODEG(x) ((x) * 180.0f / PI)
inline float sq(float x) { return x * x; }
#define ARRAY_SIZE(array)                (sizeof(array) / sizeof(array[0]))
#define SQR(x) ((x) * (x))
#define nil nullptr
#define Abs std::abs
#define Sqrt std::sqrt

inline float Sin(float x) { return sinf(x); }
inline float Cos(float x) { return cosf(x); }

inline float
DotProduct2D(const CVector2D& v1, const CVector2D& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
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
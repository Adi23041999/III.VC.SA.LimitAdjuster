/*
* Copyright (c) re3
*/

#pragma once
#include "stdint.h"
#include "Vector.h"

typedef uint32_t uint32;

namespace rw 
{
struct Matrix
{
	V3d right;
	uint32 flags;
	V3d up;
	uint32 pad1;
	V3d at;
	uint32 pad2;
	V3d pos;
	uint32 pad3;
};
}

typedef rw::Matrix RwMatrix;
#define nil NULL

class CMatrix
{
public:
	union
	{
		float f[4][4];
		struct
		{
			float rx, ry, rz, rw;
			float fx, fy, fz, fw;
			float ux, uy, uz, uw;
			float px, py, pz, pw;
		};
	};

	RwMatrix* m_attachment;
	bool m_hasRwMatrix;	// are we the owner?

	CVector& GetPosition(void) { return *(CVector*)&px; }
	CVector& GetRight(void) { return *(CVector*)&rx; }
	CVector& GetForward(void) { return *(CVector*)&fx; }
	CVector& GetUp(void) { return *(CVector*)&ux; }

	const CVector& GetPosition(void) const { return *(CVector*)&px; }
	const CVector& GetRight(void) const { return *(CVector*)&rx; }
	const CVector& GetForward(void) const { return *(CVector*)&fx; }
	const CVector& GetUp(void) const { return *(CVector*)&ux; }
};

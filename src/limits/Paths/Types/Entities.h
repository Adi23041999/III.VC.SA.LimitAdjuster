/*
* Copyright (c) re3
*/

#pragma once
#include "stdint.h"
#include "Matrix.h"

struct CPlaceable
{
	CMatrix m_matrix;
	CMatrix &GetMatrix(void) { return m_matrix; }
	const CVector& GetPosition(void) { return m_matrix.GetPosition(); }
	CVector& GetRight(void) { return m_matrix.GetRight(); }
	CVector& GetForward(void) { return m_matrix.GetForward(); }
	CVector& GetUp(void) { return m_matrix.GetUp(); }

	virtual ~CPlaceable() {}

};
static_assert(sizeof(CPlaceable) == 0x4C, "");

struct CEntity : public CPlaceable
{                        
	void* m_rwObject;
	char bfTypeStatus;
	char bfFlagsA;
	char bfFlagsB;
	char bfFlagsC;
	char bfFlagsD;
	char bfFlagsE;
	char __f0052[2];
	__int16 m_scanCode;
	__int16 uiPathMedianRand;
	__int16 nModelIndex;                
	__int16 level;
	void* pFirstRef;

	int16 GetModelIndex(void) const { return nModelIndex; }
};
static_assert(sizeof(CEntity) == 0x64, "");

struct CBuilding : public CEntity
{

};
static_assert(sizeof(CBuilding) == 0x64, "");

struct CTreadable : public CBuilding
{
	int16_t m_nodeIndices[2][12];	// first car, then ped
};
static_assert(sizeof(CTreadable) == 0x94, "");

struct CPhysical : public CEntity
{
	int m_audioEntityId;
	float m_phys_unused1;
	CTreadable* m_treadable[2];
	char members[0xB4];
};
static_assert(sizeof(CPhysical) == 0x128, "");


namespace CCamera
{
	typedef bool(__thiscall* _IsSphereVisible1)(void* ECX, const CVector& point, float radius, CMatrix* mat);
	_IsSphereVisible1 IsSphereVisible1 = (_IsSphereVisible1)0x42C760;

	typedef bool(__thiscall* _IsSphereVisible2)(void* ECX, const CVector& point, float radius);
	_IsSphereVisible2 IsSphereVisible2 = (_IsSphereVisible2)0x43D3B0;

	struct CCamera : public CPlaceable
	{
		char members1[0xF0 - sizeof(CPlaceable)];
		float GenerationDistMultiplier;
		char members2[0xE9D8 - 0xF4];

		bool IsSphereVisible(const CVector& point, float radius, CMatrix* mat)
		{
			return IsSphereVisible1(this, point, radius, mat);
		}
		bool IsSphereVisible(const CVector& point, float radius)
		{
			return IsSphereVisible2(this, point, radius);
		}
	};
}

static_assert(sizeof(CCamera::CCamera) == 0xE9D8, "");

namespace CWorld
{
	auto FindGroundZFor3DCoord = (float(__cdecl*)(float x, float y, float z, bool* outResult)) 0x4B3AE0;
	auto GetIsLineOfSightClear = (bool(__cdecl*)(const CVector& origin, const CVector& target, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck)) 0x4AEAA0;
}

namespace CFileMgr
{
	auto SetDir = (void(__cdecl*)(const char* dir)) 0x479020;
}

namespace CGeneral
{
	auto GetRadianAngleBetweenPoints = (float(__cdecl*)(float x1, float y1, float x2, float y2)) 0x48CA50;
	//auto GetRandomNumber = (uint32(__cdecl*)()) 0x54A4B0;

	// paths don't generate vehicles correctly with the broken random number generator
#define MYRAND_MAX		65535
	unsigned long long myrand_seed = 1;
	int myrand(void)
	{
		// Use our own implementation of rand, stolen from PS2
		myrand_seed = 0x5851F42D4C957F2D * myrand_seed + 1;
		return ((myrand_seed >> 32) & 0x7FFFFFFF);
	}

	uint16 GetRandomNumber()
	{
		return myrand() & MYRAND_MAX;
	}
}

namespace CCollision
{
	auto DistToLine = (float(__cdecl*)(const CVector* lineStart, const CVector* lineEnd, const CVector* point)) 0x40DC70;
}

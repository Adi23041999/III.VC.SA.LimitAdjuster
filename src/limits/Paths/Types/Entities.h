/*
* Copyright (c) re3
*/

#pragma once
#include "stdint.h"
#include "CMatrix.h"
#include "injector.hpp"
#include "General.h"

using namespace injector;

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

enum eEntityStatus
{
	STATUS_PLAYER,
	STATUS_PLAYER_PLAYBACKFROMBUFFER,
	STATUS_SIMPLE,
	STATUS_PHYSICS,
	STATUS_ABANDONED,
	STATUS_WRECKED,
	STATUS_TRAIN_MOVING,
	STATUS_TRAIN_NOT_MOVING,
	STATUS_HELI,
	STATUS_PLANE,
	STATUS_PLAYER_REMOTE,
	STATUS_PLAYER_DISABLED,
};

struct CEntity : public CPlaceable
{                        
public:
	void* m_rwObject;
protected:
	uint32 m_type : 3;
private:
	uint32 m_status : 5;
public:
	// flagsA
	uint32 bUsesCollision : 1;			// does entity use collision
	uint32 bCollisionProcessed : 1;		// has object been processed by a ProcessEntityCollision function
	uint32 bIsStatic : 1;				// is entity static
	uint32 bHasContacted : 1;			// has entity processed some contact forces
	uint32 bPedPhysics : 1;
	uint32 bIsStuck : 1;				// is entity stuck
	uint32 bIsInSafePosition : 1;		// is entity in a collision free safe position
	uint32 bUseCollisionRecords : 1;

	// flagsB
	uint32 bWasPostponed : 1;			// was entity control processing postponed
	uint32 bExplosionProof : 1;
	uint32 bIsVisible : 1;				//is the entity visible
	uint32 bHasCollided : 1;
	uint32 bRenderScorched : 1;
	uint32 bHasBlip : 1;
	uint32 bIsBIGBuilding : 1;			// Set if this entity is a big building
	uint32 bRenderDamaged : 1;			// use damaged LOD models for objects with applicable damage

	// flagsC
	uint32 bBulletProof : 1;
	uint32 bFireProof : 1;
	uint32 bCollisionProof : 1;
	uint32 bMeleeProof : 1;
	uint32 bOnlyDamagedByPlayer : 1;
	uint32 bStreamingDontDelete : 1;	// Dont let the streaming remove this 
	uint32 bZoneCulled : 1;
	uint32 bZoneCulled2 : 1;    // only treadables+10m

	// flagsD
	uint32 bRemoveFromWorld : 1;		// remove this entity next time it should be processed
	uint32 bHasHitWall : 1;				// has collided with a building (changes subsequent collisions)
	uint32 bImBeingRendered : 1;		// don't delete me because I'm being rendered
	uint32 bTouchingWater : 1;	// used by cBuoyancy::ProcessBuoyancy
	uint32 bIsSubway : 1;	// set when subway, but maybe different meaning?
	uint32 bDrawLast : 1;				// draw object last
	uint32 bNoBrightHeadLights : 1;
	uint32 bDoNotRender : 1;

	// flagsE
	uint32 bDistanceFade : 1;			// Fade entity because it is far away
	uint32 m_flagE2 : 1;

	uint16 m_scanCode;
	uint16 m_randomSeed;
	int16 m_modelIndex;
	uint16 m_level;	// int16
	void* m_pFirstReference;

	int16 GetModelIndex(void) const { return m_modelIndex; }
	void SetStatus(uint8 status) { m_status = status; }
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

enum
{
	NUM_PATH_NODES_IN_AUTOPILOT = 8,
};

struct CAutoPilot {
public:
	int32 m_nCurrentRouteNode;
	int32 m_nNextRouteNode;
	int32 m_nPrevRouteNode;
	int32 m_nTimeEnteredCurve;
	int32 m_nTimeToSpendOnCurrentCurve;
	uint32 m_nCurrentPathNodeInfo;
	uint32 m_nNextPathNodeInfo;
	uint32 m_nPreviousPathNodeInfo;
	uint32 m_nAntiReverseTimer;
	uint32 m_nTimeToStartMission;
	int8 m_nPreviousDirection;
	int8 m_nCurrentDirection;
	int8 m_nNextDirection;
	int8 m_nCurrentLane;
	int8 m_nNextLane;
	uint8 m_nDrivingStyle;
	uint8 m_nCarMission;
	uint8 m_nTempAction;
	uint32 m_nTimeTempAction;
	float m_fMaxTrafficSpeed;
	uint8 m_nCruiseSpeed;
	uint8 m_bSlowedDownBecauseOfCars : 1;
	uint8 m_bSlowedDownBecauseOfPeds : 1;
	uint8 m_bStayInCurrentLevel : 1;
	uint8 m_bStayInFastLane : 1;
	uint8 m_bIgnorePathfinding : 1;
	CVector m_vecDestinationCoors;
	struct CPathNode* m_aPathFindNodesInfo[NUM_PATH_NODES_IN_AUTOPILOT];
	int16 m_nPathFindNodesCount;
	struct CVehicle* m_pTargetCar;
};
static_assert(sizeof(CAutoPilot) == 0x70, "");

struct CVehicle : public CPhysical
{
public:
	void* pHandling;
	CAutoPilot AutoPilot;
	char members[0x288 - sizeof(CPhysical) - 0x4 - sizeof(CAutoPilot)];
};
static_assert(sizeof(CVehicle) == 0x288, "");

namespace CCamera
{
	typedef bool(__thiscall* _IsSphereVisible1)(void* ECX, const CVector& point, float radius, CMatrix* mat);
	extern _IsSphereVisible1 IsSphereVisible1;

	typedef bool(__thiscall* _IsSphereVisible2)(void* ECX, const CVector& point, float radius);
	extern _IsSphereVisible2 IsSphereVisible2;

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
	typedef float(__cdecl* _FindGroundZFor3DCoord)(float x, float y, float z, bool* outResult);
	extern _FindGroundZFor3DCoord FindGroundZFor3DCoord;

	typedef bool(__cdecl* _GetIsLineOfSightClear)(const CVector& origin, const CVector& target, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck);
	extern _GetIsLineOfSightClear GetIsLineOfSightClear;
}

namespace CFileMgr
{
	typedef void(__cdecl* _SetDir)(const char* dir);
	extern _SetDir SetDir;
}

namespace CGeneral
{
	typedef float(__cdecl* _GetRadianAngleBetweenPoints)(float x1, float y1, float x2, float y2);
	extern _GetRadianAngleBetweenPoints GetRadianAngleBetweenPoints;

	//auto GetRandomNumber = (uint32(__cdecl*)()) 0x54A4B0;

	// paths don't generate vehicles correctly with the broken random number generator
#define MYRAND_MAX		65535
	extern unsigned long long myrand_seed;
	int myrand(void);

	static uint16 GetRandomNumber()
	{
		return myrand() & MYRAND_MAX;
	}

	static bool GetRandomTrueFalse(void)
	{
		return GetRandomNumber() < MYRAND_MAX / 2;
	}
}

namespace CCollision
{
	typedef float(__cdecl* _DistToLine)(const CVector* lineStart, const CVector* lineEnd, const CVector* point);
	extern _DistToLine DistToLine;
}

namespace CCarCtrl
{
	typedef uint8(__cdecl* _FindPathDirection)(int32 prevNode, int32 curNode, int32 nextNode);
	extern _FindPathDirection FindPathDirection;

	typedef void(__cdecl* _SwitchVehicleToRealPhysics)(CVehicle* pVehicle);
	extern _SwitchVehicleToRealPhysics SwitchVehicleToRealPhysics;
}

namespace CCurves
{
	typedef float(__cdecl* _CalcSpeedScaleFactor)(CVector* pPoint1, CVector* pPoint2, float dir1X, float dir1Y, float dir2X, float dir2Y);
	extern _CalcSpeedScaleFactor CalcSpeedScaleFactor;
}
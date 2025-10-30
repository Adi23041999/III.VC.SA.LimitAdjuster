#pragma once
#if GTASA
#include <math.h>
#include <windows.h>
#include "CVector.h"
#include "CMatrix.h"
#include "CPlaceable.h"

#define RAD_TO_DEG								(180.0/M_PI)
#define DEG_TO_RAD								(M_PI/180.0)

// TODO: Reverse it
#define FUNC_CPlaceable__GetRotation			0x441DB0

#define FUNC_CEntity__GetBoundCentre				0x534250

struct CShadowImage
{
	RwCamera *camera;
	RwTexture *texture;
};

struct CShadowData
{
	int *owner;
	char isExist, intensity, _pad1[2];
	CShadowImage image;
	char isBlurred, _pad2[3];
	CShadowImage blurredImage;
	int blurLevel;
	char createBlurTypeB, _pad3[3];
	int objectType;
	RpLight *light;
	RwSphere boundingSphere, baseSphere;
};

struct CRegisteredShadow
{
	RwV3d position;
	float x1, y1, x2, y2, zDistance, scale;
	RwTexture *texture;
	CShadowData *shadowData;
	short intensity;
	char type, red, green, blue;
	short flags; /*
				 0001 DRAW_ON_WATER
				 0010 IGNORE_MAP_OBJECTS
				 0100 DRAW_ON_BUILDINGS
				 */
};

// TODO: Move it away
class CKeyGen
{
public:
	static unsigned int		GetUppercaseKey(const char* pEntry);
};

// TODO: Move away?
class CGame
{
private:
	static bool&			bMissionPackGame;

public:
	static inline bool		IsMissionPackGame()
		{ return bMissionPackGame; }
};


bool CalcScreenCoors(const CVector& vecIn, CVector* vecOut);
void LoadingScreenLoadingFile(const char* pText);

#endif // GTASA
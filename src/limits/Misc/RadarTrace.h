/*
* Blips Limit Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"
#include "OLACommon.h"
#include "CRadar.h"

#ifdef GTA3

class PLUGIN_API tRadarTraceEx {
public:
	unsigned int m_nColour; //!< see eBlipColour
	unsigned int m_nBlipType; //!< see eBlipType
	int m_nEntityHandle;
	CVector2D m_vec2DPos;
	CVector m_vecPos;
	unsigned short m_nBlipIndex;
	bool m_bDim;
	bool m_bInUse;
	float m_fSphereRadius;
	unsigned short m_nBlipSize;
	unsigned short m_nBlipDisplay; //!< see eBlipDisplay
	unsigned short m_nRadarSprite; //!< see eRadarSprite
	unsigned short m_nExtra; // OLA extra
};
VALIDATE_SIZE(tRadarTraceEx, 0x30);

class RadarTrace : public SimpleAdjuster {
public:
	static std::vector<tRadarTraceEx> ms_RadarTrace;
	static uint8 NumRadarTrace;

	virtual const char* GetLimitName() override;
	virtual void ChangeLimit(int id, const std::string& value) override;
	
	static void Initialise();
	static int SetCoordBlip(eBlipType type, CVector pos, int32 color, eBlipDisplay display);
	static int SetEntityBlip(eBlipType type, int32 handle, int32 color, eBlipDisplay display);
	static void ClearBlipForEntity(eBlipType type, int32 id);
	static void ClearBlip(int32 i);
	static void LoadAllRadarBlips(uint8* buf, uint32 size);
	static void SaveAllRadarBlips(uint8* buf, uint32* size);
} RadarTrace;
#endif // GTA3

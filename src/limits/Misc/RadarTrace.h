/*
* Ped Groups Limit Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "LimitAdjuster.h"
#include "OLACommon.h"
#include "CRadar.h"

using namespace injector;

#ifdef GTA3
class RadarTrace : public SimpleAdjuster {
public:
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

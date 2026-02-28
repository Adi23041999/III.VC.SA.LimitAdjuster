#ifdef GTA3
#include "ObjectInfo.h"

using namespace injector;

std::vector<CObjectInfo> ObjectInfo::aObjectInfo;

void ObjectInfo::ChangeLimit(int, const std::string& value)
{
	uint32_t numObjectInfo = std::stoi(value);
	aObjectInfo.resize(numObjectInfo);

	WriteMemory(0x4BC11E, &aObjectInfo[0], true);
	WriteMemory(0x4BC1E8, &aObjectInfo[0].m_fMass, true);
	WriteMemory(0x4BC1FC, &aObjectInfo[0].m_fBuoyancy, true);
	WriteMemory(0x4BC202, &aObjectInfo[0].m_nCollisionDamageEffect, true);
	WriteMemory(0x4BC20F, &aObjectInfo[0].m_nSpecialCollisionResponseCases, true);
	WriteMemory(0x4BC21C, &aObjectInfo[0].m_bCameraToAvoidThisObject, true);
	WriteMemory(0x4BC295, &aObjectInfo[0], true);
}

#endif // GTA3
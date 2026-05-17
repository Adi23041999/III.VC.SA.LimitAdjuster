#ifdef GTA3
#include "RadarTrace.h"
#include "OLACommon.h"
#include "SaveBuf.h"
#include "CTxdStore.h"

using namespace injector;

std::vector<tRadarTraceEx> RadarTrace::ms_RadarTrace;
uint8 RadarTrace::NumRadarTrace = 32;

const char* RadarTrace::GetLimitName()
{
	return "RadarBlips";
}

void RadarTrace::ChangeLimit(int id, const std::string& value)
{
	NumRadarTrace = std::min(std::stoi(value), 127);
	ms_RadarTrace.resize(NumRadarTrace);

	MakeJMP(0x4A3EF0, Initialise);
	MakeJMP(0x4A5590, SetCoordBlip);
	MakeJMP(0x4A5640, SetEntityBlip);
	MakeJMP(0x4A56C0, ClearBlipForEntity);
	MakeJMP(0x4A5720, ClearBlip);
	MakeJMP(0x4A6F30, LoadAllRadarBlips);
	MakeJMP(0x4A6E30, SaveAllRadarBlips);

	WriteMemory<uint8_t>(0x4A3F2E + 2, NumRadarTrace, true);
	WriteMemory<uint8_t>(0x4A47F8 + 4, NumRadarTrace, true);
	WriteMemory<uint8_t>(0x4A4A3C + 4, NumRadarTrace, true);
	WriteMemory<uint8_t>(0x4A4C00 + 2, NumRadarTrace, true);
	WriteMemory<uint8_t>(0x4A4F0F + 2, NumRadarTrace, true);
	WriteMemory(0x59631C + 1, ms_RadarTrace.size() * sizeof(tRadarTraceEx), true);
	WriteMemory(0x59632C + 1, ms_RadarTrace.size() * sizeof(tRadarTraceEx), true);
	WriteMemory(0x596864 + 1, ms_RadarTrace.size() * sizeof(tRadarTraceEx), true);

	WriteMemory(0x4A418C, &ms_RadarTrace[0].m_nBlipIndex, true);
	WriteMemory(0x4A4196, &ms_RadarTrace[0].m_nBlipIndex, true);
	WriteMemory(0x4A41A3, &ms_RadarTrace[0].m_nBlipIndex, true);
	WriteMemory(0x4A41AC, &ms_RadarTrace[0].m_nBlipIndex, true);

	WriteMemory(0x4A41EA, &ms_RadarTrace[0].m_nBlipIndex, true);

	WriteMemory(0x4A4469, &ms_RadarTrace[0], true);
	WriteMemory(0x4A4484, &ms_RadarTrace[0].m_bInUse, true);
	WriteMemory(0x4A4491, &ms_RadarTrace[0].m_nBlipType, true);
	WriteMemory(0x4A44AD, &ms_RadarTrace[0].m_nRadarSprite, true);
	WriteMemory(0x4A44DE, &ms_RadarTrace[0].m_nColour, true);
	WriteMemory(0x4A44E4, &ms_RadarTrace[0].m_bDim, true);
	WriteMemory(0x4A44F4, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A4511, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4518, &ms_RadarTrace[0].m_vecPos.z, true);
	WriteMemory(0x4A451E, &ms_RadarTrace[0].m_vecPos.y, true);
	WriteMemory(0x4A4524, &ms_RadarTrace[0].m_vecPos.x, true);
	WriteMemory(0x4A452F, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A453E, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4544, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A455A, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4565, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A45BC, &ms_RadarTrace[0].m_nRadarSprite, true);
	WriteMemory(0x4A45EF, &ms_RadarTrace[0].m_nBlipSize, true);
	WriteMemory(0x4A461C, &ms_RadarTrace[0].m_nRadarSprite, true);
	WriteMemory(0x4A464A, &ms_RadarTrace[0].m_nEntityHandle, true);
	WriteMemory(0x4A465E, &ms_RadarTrace[0].m_nEntityHandle, true);
	WriteMemory(0x4A4687, &ms_RadarTrace[0].m_nEntityHandle, true);
	WriteMemory(0x4A46A3, &ms_RadarTrace[0].m_nColour, true);
	WriteMemory(0x4A46A9, &ms_RadarTrace[0].m_bDim, true);
	WriteMemory(0x4A46B9, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A46D9, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A46ED, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A46FC, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4702, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4718, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4723, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A478D, &ms_RadarTrace[0].m_nRadarSprite, true);
	WriteMemory(0x4A47C0, &ms_RadarTrace[0].m_nBlipSize, true);
	WriteMemory(0x4A4812, &ms_RadarTrace[0].m_bInUse, true);
	WriteMemory(0x4A481F, &ms_RadarTrace[0].m_nBlipType, true);
	WriteMemory(0x4A483B, &ms_RadarTrace[0].m_nRadarSprite, true);
	WriteMemory(0x4A4878, &ms_RadarTrace[0].m_nEntityHandle, true);
	WriteMemory(0x4A488C, &ms_RadarTrace[0].m_nEntityHandle, true);
	WriteMemory(0x4A48C6, &ms_RadarTrace[0].m_nEntityHandle, true);
	WriteMemory(0x4A48E2, &ms_RadarTrace[0].m_nColour, true);
	WriteMemory(0x4A48E8, &ms_RadarTrace[0].m_bDim, true);
	WriteMemory(0x4A48F8, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A4918, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A492C, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A493B, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4941, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4957, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4962, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A49CF, &ms_RadarTrace[0].m_nRadarSprite, true);
	WriteMemory(0x4A4A02, &ms_RadarTrace[0].m_nBlipSize, true);
	WriteMemory(0x4A4A52, &ms_RadarTrace[0].m_bInUse, true);
	WriteMemory(0x4A4A5F, &ms_RadarTrace[0].m_nBlipType, true);
	WriteMemory(0x4A4A7B, &ms_RadarTrace[0].m_nRadarSprite, true);
	WriteMemory(0x4A4ABB, &ms_RadarTrace[0].m_nColour, true);
	WriteMemory(0x4A4AC1, &ms_RadarTrace[0].m_bDim, true);
	WriteMemory(0x4A4AD1, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A4AEE, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4AF5, &ms_RadarTrace[0].m_vecPos.z, true);
	WriteMemory(0x4A4AFB, &ms_RadarTrace[0].m_vecPos.y, true);
	WriteMemory(0x4A4B01, &ms_RadarTrace[0].m_vecPos.x, true);
	WriteMemory(0x4A4B0C, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4B1B, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4B21, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4B37, &ms_RadarTrace[0].m_fSphereRadius, true);
	WriteMemory(0x4A4B42, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A4B99, &ms_RadarTrace[0].m_nRadarSprite, true);
	WriteMemory(0x4A4BCC, &ms_RadarTrace[0].m_nBlipSize, true);

	WriteMemory(0x4A4C7E, &ms_RadarTrace[0], true);
	WriteMemory(0x4A4C84, &ms_RadarTrace[0].m_bInUse, true);
	WriteMemory(0x4A4C91, &ms_RadarTrace[0].m_nBlipType, true);
	WriteMemory(0x4A4C97, &ms_RadarTrace[0].m_nBlipType, true);
	WriteMemory(0x4A4CBC, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A4CFE, &ms_RadarTrace[0].m_nBlipIndex, true);
	WriteMemory(0x4A4D16, &ms_RadarTrace[0].m_nEntityHandle, true);
	WriteMemory(0x4A4D29, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A4D98, &ms_RadarTrace[0].m_nBlipIndex, true);
	WriteMemory(0x4A4DBD, &ms_RadarTrace[0].m_nEntityHandle, true);
	WriteMemory(0x4A4DF5, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A4E41, &ms_RadarTrace[0].m_nBlipIndex, true);
	WriteMemory(0x4A4E67, &ms_RadarTrace[0].m_nEntityHandle, true);
	WriteMemory(0x4A4E7A, &ms_RadarTrace[0].m_nBlipDisplay, true);
	WriteMemory(0x4A4EE9, &ms_RadarTrace[0].m_nBlipIndex, true);

	WriteMemory(0x4A578D, &ms_RadarTrace[0].m_nColour, true);
	WriteMemory(0x4A57C0, &ms_RadarTrace[0].m_bDim, true);
	WriteMemory(0x4A57CF, &ms_RadarTrace[0].m_bDim, true);
	WriteMemory(0x4A57FE, &ms_RadarTrace[0].m_nBlipSize, true);
	WriteMemory(0x4A582E, &ms_RadarTrace[0].m_nBlipDisplay, true);

	WriteMemory(0x4A585E, &ms_RadarTrace[0].m_nRadarSprite, true);

	WriteMemory(0x4A5C6E, &ms_RadarTrace[0].m_nBlipType, true);
	WriteMemory(0x4A5C74, &ms_RadarTrace[0].m_nBlipType, true);
	WriteMemory(0x4A5C8B, &ms_RadarTrace[0].m_nEntityHandle, true);
	WriteMemory(0x4A5CB6, &ms_RadarTrace[0].m_nEntityHandle, true);
	WriteMemory(0x4A5CDF, &ms_RadarTrace[0].m_nEntityHandle, true);

	WriteMemory(0x596332, &ms_RadarTrace[0], true);
	WriteMemory(0x596875, &ms_RadarTrace[0], true);
}

void RadarTrace::Initialise()
{
	for (int i = 0; i < NumRadarTrace; i++) {
		ms_RadarTrace[i].m_nBlipIndex = 1;
		CRadar::SetRadarMarkerState(i, false);
		ms_RadarTrace[i].m_bInUse = false;
		ms_RadarTrace[i].m_nBlipType = BLIP_NONE;
		ms_RadarTrace[i].m_nBlipDisplay = BLIP_DISPLAY_NEITHER;
		ms_RadarTrace[i].m_nRadarSprite = RADAR_SPRITE_NONE;
		ms_RadarTrace[i].m_nExtra = 0;
	}

	CRadar::m_radarRange = 350.0f;
	for (int i = 0; i < 64; i++)
		gRadarTxdIds[i] = CTxdStore::FindTxdSlot(gRadarTexNames[i]);
}

int RadarTrace::SetCoordBlip(eBlipType type, CVector pos, int32 color, eBlipDisplay display)
{
	int32 nextBlip;
	for (nextBlip = 0; nextBlip < NumRadarTrace; nextBlip++) {
		if (!ms_RadarTrace[nextBlip].m_bInUse)
			break;
	}
#ifdef FIX_BUGS
	if (nextBlip == NumRadarTrace)
		return -1;
#endif
	ms_RadarTrace[nextBlip].m_nBlipType = type;
	ms_RadarTrace[nextBlip].m_nColour = color;
	ms_RadarTrace[nextBlip].m_bDim = 1;
	ms_RadarTrace[nextBlip].m_bInUse = 1;
	ms_RadarTrace[nextBlip].m_fSphereRadius = 1.0f;
	ms_RadarTrace[nextBlip].m_vec2DPos = pos.To2D();
	ms_RadarTrace[nextBlip].m_vecPos = pos;
	ms_RadarTrace[nextBlip].m_nEntityHandle = 0;
	ms_RadarTrace[nextBlip].m_nBlipSize = 1;
	ms_RadarTrace[nextBlip].m_nBlipDisplay = display;
	ms_RadarTrace[nextBlip].m_nRadarSprite = RADAR_SPRITE_NONE;
	ms_RadarTrace[nextBlip].m_nExtra = 0;
	return CRadar::GetNewUniqueBlipIndex(nextBlip);
}

int RadarTrace::SetEntityBlip(eBlipType type, int32 handle, int32 color, eBlipDisplay display)
{
	int32 nextBlip;
	for (nextBlip = 0; nextBlip < NumRadarTrace; nextBlip++) {
		if (!ms_RadarTrace[nextBlip].m_bInUse)
			break;
	}
#ifdef FIX_BUGS
	if (nextBlip == NumRadarTrace)
		return -1;
#endif
	ms_RadarTrace[nextBlip].m_nBlipType = type;
	ms_RadarTrace[nextBlip].m_nColour = color;
	ms_RadarTrace[nextBlip].m_bDim = 1;
	ms_RadarTrace[nextBlip].m_bInUse = 1;
	ms_RadarTrace[nextBlip].m_fSphereRadius = 1.0f;
	ms_RadarTrace[nextBlip].m_nEntityHandle = handle;
	ms_RadarTrace[nextBlip].m_nBlipSize = 1;
	ms_RadarTrace[nextBlip].m_nBlipDisplay = display;
	ms_RadarTrace[nextBlip].m_nRadarSprite = RADAR_SPRITE_NONE;
	ms_RadarTrace[nextBlip].m_nExtra = 0;
	return CRadar::GetNewUniqueBlipIndex(nextBlip);
}

void RadarTrace::ClearBlipForEntity(eBlipType type, int32 id)
{
	for (int32 i = 0; i < NumRadarTrace; i++) {
		if (type == ms_RadarTrace[i].m_nBlipType && id == ms_RadarTrace[i].m_nEntityHandle) {
			CRadar::SetRadarMarkerState(i, false);
			ms_RadarTrace[i].m_bInUse = false;
			ms_RadarTrace[i].m_nBlipType = BLIP_NONE;
			ms_RadarTrace[i].m_nBlipDisplay = BLIP_DISPLAY_NEITHER;
			ms_RadarTrace[i].m_nRadarSprite = RADAR_SPRITE_NONE;
		}
	};
}

void RadarTrace::ClearBlip(int32 i)
{
	int32 index = CRadar::GetActualBlipArrayIndex(i);
	if (index != -1) {
		CRadar::SetRadarMarkerState(index, false);
		ms_RadarTrace[index].m_bInUse = false;
	}
}

void RadarTrace::LoadAllRadarBlips(uint8* buf, uint32 size)
{
	CRadar::Initialise();
	INITSAVEBUF
		CheckSaveHeader(buf, 'R', 'D', 'R', '\0', size - SAVE_HEADER_SIZE);

	for (int i = 0; i < NumRadarTrace; i++)
		ReadSaveBuf(&ms_RadarTrace[i], buf);

	VALIDATESAVEBUF(size);
}

void RadarTrace::SaveAllRadarBlips(uint8* buf, uint32* size)
{
	*size = SAVE_HEADER_SIZE + sizeof(tRadarTraceEx) * NumRadarTrace;
	INITSAVEBUF
		WriteSaveHeader(buf, 'R', 'D', 'R', '\0', *size - SAVE_HEADER_SIZE);

	for (int i = 0; i < NumRadarTrace; i++)
		WriteSaveBuf(buf, ms_RadarTrace[i]);

	VALIDATESAVEBUF(*size);
}
#endif

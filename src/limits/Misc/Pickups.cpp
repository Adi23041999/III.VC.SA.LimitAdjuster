#ifdef GTA3
#include "Pickups.h"
#include "CPickups.h"
#include "CPools.h"
#include "CTimer.h"
#include "CWorld.h"
#include "common.h"

using namespace injector;

#define PICKUPS_FRAME_SPAN (6)
std::vector<class CPickup> Pickups::aPickUps;
int32 Pickups::NumPickups = 336;
int32 Pickups::NumGeneralPickups = 320;

const char* Pickups::GetLimitName()
{
    return "Pickups";
}

void Pickups::ChangeLimit(int, const std::string& value)
{        
    NumPickups = std::stoi(value);
    while (NumPickups % PICKUPS_FRAME_SPAN != 0) // not sure if needed
        ++NumPickups;

    NumGeneralPickups = NumPickups - 16; // should this be exposed as well?
	
	MakeJMP(0x4303D0, Pickups_Update);

    WriteMemory(0x430496 + 2, NumPickups, true);
    WriteMemory(0x430568 + 2, NumPickups, true);
    WriteMemory(0x430852 + 2, NumPickups, true);
    WriteMemory(0x433B8F + 2, NumPickups, true);
    WriteMemory(0x433EE4 + 2, NumPickups, true);
    WriteMemory(0x434015 + 2, NumPickups, true);
    WriteMemory(0x4304CD + 1, NumPickups - 1, true);
    WriteMemory(0x43044F + 1, NumGeneralPickups, true);
    WriteMemory(0x4304FA + 2, NumGeneralPickups, true);
    WriteMemory(0x43050B + 2, NumGeneralPickups, true);
    WriteMemory(0x430524 + 2, NumGeneralPickups, true);
    WriteMemory(0x430535 + 2, NumGeneralPickups, true);
    WriteMemory(0x430547 + 2, NumGeneralPickups, true);
    WriteMemory(0x430558 + 2, NumGeneralPickups, true);

    size_t pickupsSize = sizeof(CPickup) * NumPickups;
    size_t pickupsGeneralSize = sizeof(CPickup) * NumGeneralPickups;
    WriteMemory(0x433E48 + 2, pickupsSize, true);
    WriteMemory(0x5962A4 + 1, pickupsSize, true);
    WriteMemory(0x5962B9 + 1, pickupsSize, true);
    WriteMemory(0x5967C6 + 1, pickupsSize, true);
    WriteMemory(0x4304C8 + 1, pickupsSize - sizeof(CPickup), true);
    WriteMemory(0x430454 + 1, pickupsGeneralSize, true);

    aPickUps.resize(NumPickups);
	//memset(&aPickUps[0], 0, sizeof(CPickup) * aPickUps.size());

    WriteMemory(0x4303E9, &aPickUps[0], true);
    WriteMemory(0x430412, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x43044B, &aPickUps[0].m_nPickupType + pickupsGeneralSize, true);
    WriteMemory(0x430462, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x4304DE, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x430504, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x43052E, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x430551, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x43058B, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x430591, &aPickUps[0].m_bRemoved, true);
    WriteMemory(0x430599, &aPickUps[0].m_nQuantity, true);
    WriteMemory(0x4305AD, &aPickUps[0].m_nTimer, true);
    WriteMemory(0x4305C3, &aPickUps[0].m_nTimer, true);
    WriteMemory(0x4305D7, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x4305E4, &aPickUps[0].m_nTimer, true);
    WriteMemory(0x4305F7, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x430603, &aPickUps[0].m_nTimer, true);
    WriteMemory(0x430610, &aPickUps[0], true);
    WriteMemory(0x430617, &aPickUps[0].m_nModelIndex, true);
    WriteMemory(0x43061F, &aPickUps[0].m_vecPos.x, true);
    WriteMemory(0x430625, &aPickUps[0].m_vecPos.y, true);
    WriteMemory(0x43062D, &aPickUps[0].m_vecPos.z, true);
    WriteMemory(0x43063C, &aPickUps[0].m_pObject, true);
    WriteMemory(0x430642, &aPickUps[0].m_pObject, true);
    WriteMemory(0x4307BD, &aPickUps[0].m_pObject, true);
    WriteMemory(0x4307CE, &aPickUps[0].m_pObject, true);
    WriteMemory(0x4307DE, &aPickUps[0].m_pObject, true);
    WriteMemory(0x4307E8, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x4307EF, &aPickUps[0].m_bRemoved, true);
    WriteMemory(0x430809, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x430817, &aPickUps[0].m_pObject, true);
    WriteMemory(0x430828, &aPickUps[0].m_pObject, true);
    WriteMemory(0x430838, &aPickUps[0].m_pObject, true);
    WriteMemory(0x430842, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x430849, &aPickUps[0].m_bRemoved, true);
    WriteMemory(0x433B6A, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x433B73, &aPickUps[0].m_nTimer, true);
    WriteMemory(0x433B7B, &aPickUps[0].m_nTimer, true);
    WriteMemory(0x433B83, &aPickUps[0].m_nTimer, true);
    WriteMemory(0x433D75, &aPickUps[0].m_nReferenceIndex, true);
    WriteMemory(0x433DC1, &aPickUps[0].m_nReferenceIndex, true);
    WriteMemory(0x433DCB, &aPickUps[0].m_nReferenceIndex, true);
    WriteMemory(0x433DD4, &aPickUps[0].m_nReferenceIndex, true);
    WriteMemory(0x433DDD, &aPickUps[0].m_nReferenceIndex, true);
    WriteMemory(0x433E20, &aPickUps[0].m_nReferenceIndex, true);
    WriteMemory(0x433E62, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x433E6C, &aPickUps[0].m_bRemoved, true);
    WriteMemory(0x433E76, &aPickUps[0].m_nQuantity, true);
    WriteMemory(0x433E80, &aPickUps[0].m_pObject, true);
    WriteMemory(0x433E89, &aPickUps[0].m_nTimer, true);
    WriteMemory(0x433E93, &aPickUps[0].m_nModelIndex, true);
    WriteMemory(0x433E9E, &aPickUps[0].m_nReferenceIndex, true);
    WriteMemory(0x433EA8, &aPickUps[0].m_vecPos.x, true);
    WriteMemory(0x433EB1, &aPickUps[0].m_vecPos.y, true);
    WriteMemory(0x433EBA, &aPickUps[0].m_vecPos.z, true);
    WriteMemory(0x433F74, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x433F7D, &aPickUps[0].m_bRemoved, true);
    WriteMemory(0x433F88, &aPickUps[0].m_nQuantity, true);
    WriteMemory(0x433F91, &aPickUps[0].m_pObject, true);
    WriteMemory(0x433F9A, &aPickUps[0].m_nTimer, true);
    WriteMemory(0x433FA5, &aPickUps[0].m_nModelIndex, true);
    WriteMemory(0x433FB0, &aPickUps[0].m_nReferenceIndex, true);
    WriteMemory(0x433FB9, &aPickUps[0].m_vecPos.x, true);
    WriteMemory(0x433FC2, &aPickUps[0].m_vecPos.y, true);
    WriteMemory(0x433FCB, &aPickUps[0].m_vecPos.z, true);
    WriteMemory(0x433FD1, &aPickUps[0].m_nPickupType, true);
    WriteMemory(0x433FDA, &aPickUps[0].m_pObject, true);
    WriteMemory(0x43400A, &aPickUps[0].m_pObject, true);
    WriteMemory(0x44F5A4, &aPickUps[0].m_pObject, true);
    WriteMemory(0x44F637, &aPickUps[0].m_pObject, true);
    WriteMemory(0x44F6CD, &aPickUps[0].m_pObject, true);
    WriteMemory(0x5962BF, &aPickUps[0], true);
    WriteMemory(0x5967D7, &aPickUps[0], true);

    // init
    MakeInline<0x430230, 0x430375>([](injector::reg_pack& regs)
        {
            for (int32 i = 0; i < NumPickups; i++)
            {
                aPickUps[i].m_nPickupType = PICKUP_NONE;
                aPickUps[i].m_pObject = nil;
                aPickUps[i].m_nReferenceIndex = 1;
            }

            regs.eip = 0x430375;
        });
}

void Pickups::Pickups_Update()
{
    for (uint32 i = NumGeneralPickups * (CTimer::m_FrameCounter % PICKUPS_FRAME_SPAN) / PICKUPS_FRAME_SPAN; i < NumGeneralPickups * (CTimer::m_FrameCounter % PICKUPS_FRAME_SPAN + 1) / PICKUPS_FRAME_SPAN; i++) {
        if (aPickUps[i].m_nPickupType != PICKUP_NONE && aPickUps[i].Update(FindPlayerPed(), FindPlayerVehicle(), CWorld::PlayerInFocus)) {
            CPickups::AddToCollectedPickupsArray(i);
        }
    }

    for (uint32 i = NumGeneralPickups; i < NumPickups; i++) {
        if (aPickUps[i].m_nPickupType != PICKUP_NONE && aPickUps[i].Update( FindPlayerPed(), FindPlayerVehicle(), CWorld::PlayerInFocus)) {
            CPickups::AddToCollectedPickupsArray(i);
        }
    }
}
#endif // GTA3

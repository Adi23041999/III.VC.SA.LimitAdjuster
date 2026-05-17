#ifdef GTA3
#include "Scripts.h"

using namespace injector;

int32 Script::NumUsedObjects = 200;
std::vector<tUsedObject> Script::UsedObjectsArray;
int32 Script::NumMultiScripts = 120;
std::vector<uint8> Script::MultiScriptArray;
int8 Script::NumBuildingSwaps = 25;
std::vector<tBuildingSwap> Script::BuildingSwapArray;
int32 Script::NumInvisibilitySettings = 20;
std::vector<CEntity*> Script::InvisibilitySettingArray;

const Adjuster::Limit* Script::GetLimits()
{
    static Limit limits[] =
    {
        DEFINE_LIMIT(UsedObjects),
        DEFINE_LIMIT(MissionScripts),
		DEFINE_LIMIT(BuildingSwaps),
		DEFINE_LIMIT(InvisibilitySettings),
        FINISH_LIMITS()
    };
    return limits;
}

void Script::ChangeLimit(int id, const std::string& value)
{
    switch (id)
    {
    case UsedObjects:
	{
		NumUsedObjects = std::stoi(value);
		UsedObjectsArray.resize(NumUsedObjects);

		WriteMemory(0x438A40 + 2, NumUsedObjects, true);

		WriteMemory(0x438A0B, &UsedObjectsArray[0].name, true);
		WriteMemory(0x438A19, &UsedObjectsArray[0].name, true);
		WriteMemory(0x438A2C, &UsedObjectsArray[0].name, true);
		WriteMemory(0x438A35, &UsedObjectsArray[0].index, true);
		WriteMemory(0x43DD45, &UsedObjectsArray[0].index, true);
		WriteMemory(0x4432B2, &UsedObjectsArray[0].index, true);
		WriteMemory(0x4445BA, &UsedObjectsArray[0].index, true);
		WriteMemory(0x4445FB, &UsedObjectsArray[0].index, true);
		WriteMemory(0x44464D, &UsedObjectsArray[0].index, true);
		WriteMemory(0x444DF6, &UsedObjectsArray[0].index, true);
		WriteMemory(0x448A3D, &UsedObjectsArray[0].index, true);
		WriteMemory(0x44B600, &UsedObjectsArray[0].index, true);
		WriteMemory(0x44E505, &UsedObjectsArray[0].index, true);
		WriteMemory(0x44E521, &UsedObjectsArray[0].index, true);
		WriteMemory(0x4549E4, &UsedObjectsArray[0].name, true);
		WriteMemory(0x4549FB, &UsedObjectsArray[0].name, true);
		WriteMemory(0x454A15, &UsedObjectsArray[0].name, true);
		WriteMemory(0x454A2F, &UsedObjectsArray[0].name, true);
		WriteMemory(0x454A49, &UsedObjectsArray[0].name, true);
		WriteMemory(0x454A63, &UsedObjectsArray[0].name, true);
		WriteMemory(0x454A7D, &UsedObjectsArray[0].name, true);
		WriteMemory(0x454AA1, &UsedObjectsArray[0].name, true);
		WriteMemory(0x454AAE, &UsedObjectsArray[0].index, true);
		WriteMemory(0x454AFC, &UsedObjectsArray[1].name, true);
		WriteMemory(0x454B63, &UsedObjectsArray[0].index, true);
		WriteMemory(0x58A54A, &UsedObjectsArray[0].index, true);
		break;
	}
    case MissionScripts:
	{
		NumMultiScripts = std::stoi(value);
		while (NumMultiScripts % 16 != 8)
			++NumMultiScripts;

		MultiScriptArray.resize(4 * NumMultiScripts, 0);
		
		WriteMemory(0x438A74, &MultiScriptArray[0] + 0x0, true);
		WriteMemory(0x438A7C, &MultiScriptArray[0] + 0x8, true);
		WriteMemory(0x438A84, &MultiScriptArray[0] + 0x10, true);
		WriteMemory(0x438A8C, &MultiScriptArray[0] + 0x18, true);
		WriteMemory(0x438A94, &MultiScriptArray[0] + 0x20, true);
		WriteMemory(0x438A9C, &MultiScriptArray[0] + 0x28, true);
		WriteMemory(0x438AA4, &MultiScriptArray[0] + 0x30, true);
		WriteMemory(0x438AAC, &MultiScriptArray[0] + 0x38, true);
		WriteMemory(0x438AC6, &MultiScriptArray[0] + 0x0, true);
		WriteMemory(0x438ADB, &MultiScriptArray[0] + 0x4, true);
		WriteMemory(0x438AF0, &MultiScriptArray[0] + 0x8, true);
		WriteMemory(0x438AFB, &MultiScriptArray[0] + 0xC, true);
		WriteMemory(0x438B06, &MultiScriptArray[0] + 0x10, true);
		WriteMemory(0x438B11, &MultiScriptArray[0] + 0x14, true);
		WriteMemory(0x438B1C, &MultiScriptArray[0] + 0x18, true);
		WriteMemory(0x438B27, &MultiScriptArray[0] + 0x1C, true);
		WriteMemory(0x454D1C, &MultiScriptArray[0] + 0x0, true);
		WriteMemory(0x454D5C, &MultiScriptArray[0] + 0x4, true);
		WriteMemory(0x454D9C, &MultiScriptArray[0] + 0x8, true);
		WriteMemory(0x454DDC, &MultiScriptArray[0] + 0xC, true);
		WriteMemory(0x454E1C, &MultiScriptArray[0] + 0x10, true);
		WriteMemory(0x454E5C, &MultiScriptArray[0] + 0x14, true);
		WriteMemory(0x454E9C, &MultiScriptArray[0] + 0x18, true);
		WriteMemory(0x454EDF, &MultiScriptArray[0] + 0x1C, true);
		WriteMemory(0x454F2A, &MultiScriptArray[0] + 0x0, true);
		WriteMemory(0x588DFF, &MultiScriptArray[0] + 0x0, true);

		//WriteMemory<uint8>(0x438AB3 + 2, 127, true);
		MakeInline<0x438AB3>([](injector::reg_pack& regs)
			{
				regs.eip = (int32)regs.eax < NumMultiScripts - 16 ? 0x438A70 : 0x438AB8;
			});

		break;
	}
    case BuildingSwaps:
	{
		NumBuildingSwaps = Min(127, std::stoi(value));
		while (NumBuildingSwaps % 5 != 0)
			--NumBuildingSwaps;
		assert(NumBuildingSwaps > 0);

		BuildingSwapArray.resize(NumBuildingSwaps + 5);

		WriteMemory<int8>(0x438F55 + 2, NumBuildingSwaps, true);
		WriteMemory<int8>(0x44FBF4 + 3, NumBuildingSwaps, true);
		WriteMemory<int8>(0x44FC57 + 3, NumBuildingSwaps, true);
		WriteMemory<int8>(0x44FD48 + 3, NumBuildingSwaps, true);

		WriteMemory<int8>(0x453990 + 4, NumBuildingSwaps, true);
		WriteMemory<int8>(0x453E8C + 4, NumBuildingSwaps, true);

		int32 SaveSize = injector::ReadMemory<int32>(0x453658 + 2, true);
		SaveSize -= 4 * sizeof(uint32) * 25;
		SaveSize += 4 * sizeof(uint32) * NumBuildingSwaps;
		WriteMemory<int32>(0x453658 + 2, SaveSize, true);

		WriteMemory(0x44FBE4, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x438EB0, &BuildingSwapArray[0].m_nNewModel, true);
		WriteMemory(0x438EB7, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x438ECC, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x438ED6, &BuildingSwapArray[0].m_nNewModel, true);
		WriteMemory(0x438EDD, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x438EF1, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x438EFB, &BuildingSwapArray[0].m_nNewModel, true);
		WriteMemory(0x438F02, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x438F17, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x438F21, &BuildingSwapArray[0].m_nNewModel, true);
		WriteMemory(0x438F28, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x438F3F, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x438F49, &BuildingSwapArray[0].m_nNewModel, true);
		WriteMemory(0x438F50, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x44FBE4, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x44FC11, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x44FC19, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x44FC23, &BuildingSwapArray[0].m_nNewModel, true);
		WriteMemory(0x44FC2A, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x44FC33, &BuildingSwapArray[0].m_nNewModel, true);
		WriteMemory(0x44FC48, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x44FC79, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x44FC7F, &BuildingSwapArray[0].m_nNewModel, true);
		WriteMemory(0x44FC85, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x44FD18, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x44FD22, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x44FD2E, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x44FD38, &BuildingSwapArray[0].m_nNewModel, true);
		WriteMemory(0x44FD3F, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x453912, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x453925, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x453942, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x453970, &BuildingSwapArray[0].m_nNewModel, true);
		WriteMemory(0x45397B, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x453DE7, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x453E1A, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x453E4D, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x453E58, &BuildingSwapArray[0].m_nNewModel, true);
		WriteMemory(0x453E66, &BuildingSwapArray[0].m_nOldModel, true);
		WriteMemory(0x453E6C, &BuildingSwapArray[0].m_pBuilding, true);
		WriteMemory(0x453E7B, &BuildingSwapArray[0].m_nNewModel, true);
		break;
	}
	case InvisibilitySettings:
	{
		NumInvisibilitySettings = Min(127, std::stoi(value));
		while (NumInvisibilitySettings % 5 != 0)
			--NumInvisibilitySettings;
		assert(NumInvisibilitySettings > 0);

		InvisibilitySettingArray.resize(NumInvisibilitySettings + 5);
		
		WriteMemory<int8>(0x438F9A + 2, NumInvisibilitySettings, true);
		WriteMemory<int8>(0x44FCB1 + 3, NumInvisibilitySettings, true);
		WriteMemory<int8>(0x44FCF2 + 3, NumInvisibilitySettings, true);
		WriteMemory<int8>(0x44FD87 + 3, NumInvisibilitySettings, true);
		WriteMemory<int8>(0x453A54 + 2, NumInvisibilitySettings, true);
		WriteMemory<int8>(0x453FA0 + 2, NumInvisibilitySettings, true);

		int32 SaveSize = injector::ReadMemory<int32>(0x453658 + 2, true);
		SaveSize -= 2 * sizeof(uint32) * 20;
		SaveSize += 2 * sizeof(uint32) * NumInvisibilitySettings;
		WriteMemory<int32>(0x453658 + 2, SaveSize, true);

		WriteMemory(0x438F63, &InvisibilitySettingArray[0], true);
		WriteMemory(0x438F6E, &InvisibilitySettingArray[1], true);
		WriteMemory(0x438F79, &InvisibilitySettingArray[2], true);
		WriteMemory(0x438F84, &InvisibilitySettingArray[3], true);
		WriteMemory(0x438F8F, &InvisibilitySettingArray[4], true);
		WriteMemory(0x44FCA6, &InvisibilitySettingArray[0], true);
		WriteMemory(0x44FCC9, &InvisibilitySettingArray[0], true);
		WriteMemory(0x44FCE6, &InvisibilitySettingArray[0], true);
		WriteMemory(0x44FD06, &InvisibilitySettingArray[0], true);
		WriteMemory(0x44FD69, &InvisibilitySettingArray[0], true);
		WriteMemory(0x44FD7E, &InvisibilitySettingArray[0], true);
		WriteMemory(0x4539A3, &InvisibilitySettingArray[0], true);
		WriteMemory(0x4539C4, &InvisibilitySettingArray[0], true);
		WriteMemory(0x4539E3, &InvisibilitySettingArray[0], true);
		WriteMemory(0x453EC4, &InvisibilitySettingArray[0], true);
		WriteMemory(0x453EFB, &InvisibilitySettingArray[0], true);
		WriteMemory(0x453F2F, &InvisibilitySettingArray[0], true);
		WriteMemory(0x453F5D, &InvisibilitySettingArray[0], true);
		WriteMemory(0x453F88, &InvisibilitySettingArray[0], true);
		WriteMemory(0x453F8F, &InvisibilitySettingArray[0], true);
		break;
	}
    }
}

#endif // GTA3

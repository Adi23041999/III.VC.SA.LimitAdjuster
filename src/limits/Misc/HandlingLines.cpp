#ifdef GTA3
#include "HandlingLines.h"
#include "string.h"
#include "plugin.h"
#include "ModuleList.hpp"

using namespace injector;

constexpr int32 NumDefaultNames = 57;
constexpr int32 NumAircraftNames = 8;
int32 HandlingLines::NumHandlingLines = 0;
std::vector<char> HandlingLines::HandlingManager;
std::vector<std::string> HandlingLines::VehicleNames;
void* aircraftHandlingDataMgr = nullptr;
int8 NumAircraftHandlings = 0;

const char* HandlingLines::GetLimitName()
{
	return "HandlingLines";
}


void HandlingLines::ChangeLimit(int, const std::string& value)
{
    NumHandlingLines = std::stoi(value);
	size_t mgrSize = (sizeof(float) * 5) + (sizeof(uint32)) + (sizeof(tHandlingData) * NumHandlingLines);
	HandlingManager.resize(mgrSize);
	tHandlingData* HandlingData = reinterpret_cast<tHandlingData*>(&HandlingManager[sizeof(float) * 5]);
	float* fWheelFriction = reinterpret_cast<float*>(&HandlingManager[sizeof(float)]);
	
	AddDefaultVehicleNames(); // to retain the vanilla indexes

	MakeJMP(0x546B70, &cNewHandlingDataMgr::GetHandlingId);
	MakeJMP(0x546AA0, &cNewHandlingDataMgr::FindExactWord);

#ifdef COMPAT_AIRCRAFT
	// aircraft uses its own handling manager; copy ola data into it
	aircraftHandlingDataMgr = ReadMemory<void*>(0x477B8D);
	NumAircraftHandlings = ReadMemory<int8>(0x546EC9 + 1);
	plugin::Events::initRwEvent.after.Add(CopyAircraftHandlingData);
#endif // COMPAT_AIRCRAFT

	WriteMemory(0x477B8D, &HandlingManager[0], true);
	WriteMemory(0x48BD78, &HandlingManager[0], true);
	WriteMemory(0x5203D9, &HandlingManager[0], true);
	WriteMemory(0x52C811, &HandlingManager[0], true);
	WriteMemory(0x5335ED, &HandlingData->m_transmissionData.m_nDriveType, true);
	WriteMemory(0x533754, &HandlingData->m_transmissionData.m_nDriveType, true);
	WriteMemory(0x5338DB, &HandlingData->m_transmissionData.m_nDriveType, true);
	WriteMemory(0x5339B0, &HandlingData->m_transmissionData.m_nDriveType, true);
	WriteMemory(0x533AD4, &HandlingData->m_transmissionData.m_nDriveType, true);
	WriteMemory(0x533C4F, &HandlingData->m_transmissionData.m_nDriveType, true);
	WriteMemory(0x533E02, &HandlingData->m_transmissionData.m_nDriveType, true);
	WriteMemory(0x533EF5, &HandlingData->m_transmissionData.m_nDriveType, true);
	WriteMemory(0x53E493, &HandlingManager[0], true);
	WriteMemory(0x547266, &HandlingManager[0], true);
	WriteMemory(0x54B1B6, &HandlingManager[0], true);
	WriteMemory(0x54E303, &HandlingManager[0], true);
	WriteMemory(0x5515EF, fWheelFriction, true);
	WriteMemory(0x551602, fWheelFriction, true);
}

int32 cNewHandlingDataMgr::GetHandlingId(const char* name)
{
	size_t i = -1;
	for (i = 0; i < HandlingLines::VehicleNames.size(); i++)
		if (strcmp(HandlingLines::VehicleNames[i].c_str(), name) == 0)
			break;
	
	assert(i >= 0 && "Failed to find Handling line");
	return i;
}

int32 cNewHandlingDataMgr::FindExactWord(const char* word, const char* words, int wordLen, int numWords)
{
	int32 id = -1;
	for (size_t i = 0; i < HandlingLines::VehicleNames.size(); i++)
	{
		if (strcmp(HandlingLines::VehicleNames[i].c_str(), word) == 0)
		{
			id = i;
			break;
		}
	}

	if (id == -1)
	{
		std::string w = std::string(word, 14);
		HandlingLines::VehicleNames.push_back(std::move(w));
		id = HandlingLines::VehicleNames.size() - 1;
	}

	return id;
}

void HandlingLines::AddDefaultVehicleNames()
{
	const char VanillaVehicleNames[NumDefaultNames][14] = {
	"LANDSTAL",
	"IDAHO",
	"STINGER",
	"LINERUN",
	"PEREN",
	"SENTINEL",
	"PATRIOT",
	"FIRETRUK",
	"TRASH",
	"STRETCH",
	"MANANA",
	"INFERNUS",
	"BLISTA",
	"PONY",
	"MULE",
	"CHEETAH",
	"AMBULAN",
	"FBICAR",
	"MOONBEAM",
	"ESPERANT",
	"TAXI",
	"KURUMA",
	"BOBCAT",
	"MRWHOOP",
	"BFINJECT",
	"POLICE",
	"ENFORCER",
	"SECURICA",
	"BANSHEE",
	"PREDATOR",
	"BUS",
	"RHINO",
	"BARRACKS",
	"TRAIN",
	"HELI",
	"DODO",
	"COACH",
	"CABBIE",
	"STALLION",
	"RUMPO",
	"RCBANDIT",
	"BELLYUP",
	"MRWONGS",
	"MAFIA",
	"YARDIE",
	"YAKUZA",
	"DIABLOS",
	"COLUMB",
	"HOODS",
	"AIRTRAIN",
	"DEADDODO",
	"SPEEDER",
	"REEFER",
	"PANLANT",
	"FLATBED",
	"YANKEE",
	"BORGNINE"
	};

	for (int32 i = 0; i < NumDefaultNames; i++)
		VehicleNames.push_back(std::string(VanillaVehicleNames[i], 14));

#ifdef COMPAT_AIRCRAFT
	const char AircraftVehicleNames[NumAircraftNames][14] = {
	"MAVERICK",
	"POLMAV",
	"LCNMAV",
	"HUNTER",
	"HUEY",
	"FULLDODO",
	"BIPLANE",
	"SEAPLANE",
	};

	for (int32 i = 0; i < NumAircraftNames; i++)
		VehicleNames.push_back(std::string(AircraftVehicleNames[i], 14));
#endif // COMPAT_AIRCRAFT
}

void HandlingLines::CopyAircraftHandlingData()
{
	const ModuleList moduleList;
	HMODULE iiiAircraftModule = moduleList.Get(L"IIIAircraft");
	if (!iiiAircraftModule)
		iiiAircraftModule = moduleList.Get(L"III.Aircraft");
	if (!iiiAircraftModule)
		return;

	if (aircraftHandlingDataMgr)
	{
		const HMODULE mgrModule = OLA::GetModuleHandleFromAddress(aircraftHandlingDataMgr);
		if (mgrModule != iiiAircraftModule)
			return;

		bool bOldModVersion = true;
		auto func = (uint32_t(*)())GetProcAddress(mgrModule, "GetBuildNumber");
		if (func != nullptr)
		{
			bOldModVersion = func() <= 0x100;
		}
		
		if (bOldModVersion)
		{
			const size_t aircraftHandlingsSize = (sizeof(float) * 5) + (sizeof(tHandlingData) * NumAircraftHandlings);
			memcpy(aircraftHandlingDataMgr, &HandlingManager[0], aircraftHandlingsSize);
		}

	}
}

#endif // GTA3

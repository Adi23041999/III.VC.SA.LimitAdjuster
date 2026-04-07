#ifdef GTA3
#include "CarGenerators.h"
#include "SaveBuf.h"
#include "CCarGenerator.h"
#include "CTheCarGenerators.h"

using namespace injector;

std::vector<CCarGenerator> CarGenerators::CarGeneratorArray;

const char* CarGenerators::GetLimitName()
{
    return "CarGenerators";
}

void CarGenerators::ChangeLimit(int id, const std::string& value)
{
    int32 numCarGenerators = std::stoi(value);
    CarGeneratorArray.resize(numCarGenerators);

    WriteMemory(0x43F0F2, &CarGeneratorArray[0] + 0x0, true);
    WriteMemory(0x542F83, &CarGeneratorArray[0] + 0x0, true);
    WriteMemory(0x543003, &CarGeneratorArray[0] + 0x0, true);
    MakeJMP(0x543050, SaveAllCarGenerators);
    MakeJMP(0x5431E0, LoadAllCarGenerators);

#ifdef FIX_BUGS
    // overriden because cleo cargens overflow the car gen array when game is loaded
    // ie. game loads saved car gens (including cleo ones) and cleo car gens also get added again on top
    // VC guards for overflow but still duplication happens
    MakeJMP(0x542FC0, CreateCarGenerator);
#endif // FIX_BUGS
}

void CarGenerators::CopyCarGen(CCarGenerator& lhs, const CCarGenerator& rhs)
{
	lhs.m_nModelId = rhs.m_nModelId;
	lhs.m_vecPos = rhs.m_vecPos;
	lhs.m_fAngle = rhs.m_fAngle;
	lhs.m_nPrimaryColor = rhs.m_nPrimaryColor;
	lhs.m_nSecondaryColor = rhs.m_nSecondaryColor;
	lhs.m_nForceSpawn = rhs.m_nForceSpawn;
	lhs.m_nAlarm = rhs.m_nAlarm;
	lhs.m_nDoorLock = rhs.m_nDoorLock;
	lhs.m_nMinDelay = rhs.m_nMinDelay;
	lhs.m_nMaxDelay = rhs.m_nMaxDelay;
	lhs.m_nTimeNextGen = rhs.m_nTimeNextGen;
	lhs.m_nVehicleHandle = rhs.m_nVehicleHandle;
	lhs.m_nEnabled = rhs.m_nEnabled;
	lhs.m_bIsBlocking = rhs.m_bIsBlocking;
	lhs.m_vecInf = rhs.m_vecInf;
	lhs.m_vecSup = rhs.m_vecSup;
	lhs.m_fDistance = rhs.m_fDistance;
}

bool CarGenerators::DoesCarGenExistAtLocation(float x, float y, float z, float angle, int32 mi, uint32& carGenIdx)
{
    for (size_t i = 0; i < CarGeneratorArray.size(); i++)
    {
        CCarGenerator& cg = CarGeneratorArray[i];
        if (cg.m_nModelId == mi && NearlyEqual(cg.m_vecPos.x, x) && NearlyEqual(cg.m_vecPos.y, y) && NearlyEqual(cg.m_vecPos.z, z) && NearlyEqual(cg.m_fAngle, angle))
        {
            carGenIdx = i;
            return true;
        }
    }

    return false;
}

void CarGenerators::SaveAllCarGenerators(uint8* buffer, uint32* size)
{
    const uint32 carGenSize = (sizeof(CCarGenerator) * CarGeneratorArray.size());
    const uint32 nGeneralDataSize = sizeof(CTheCarGenerators::NumOfCarGenerators) + sizeof(CTheCarGenerators::CurrentActiveCount) + sizeof(CTheCarGenerators::ProcessCounter) + sizeof(CTheCarGenerators::GenerateEvenIfPlayerIsCloseCounter) + sizeof(int16);
    *size = sizeof(int) + nGeneralDataSize + sizeof(uint32) + carGenSize + SAVE_HEADER_SIZE;
    INITSAVEBUF
        WriteSaveHeader(buffer, 'C', 'G', 'N', '\0', *size - SAVE_HEADER_SIZE);

    WriteSaveBuf(buffer, nGeneralDataSize);
    WriteSaveBuf(buffer, CTheCarGenerators::NumOfCarGenerators);
    WriteSaveBuf(buffer, CTheCarGenerators::CurrentActiveCount);
    WriteSaveBuf(buffer, CTheCarGenerators::ProcessCounter);
    WriteSaveBuf(buffer, CTheCarGenerators::GenerateEvenIfPlayerIsCloseCounter);
    WriteSaveBuf(buffer, (int16)0); // alignment
    WriteSaveBuf(buffer, carGenSize);
    for (size_t i = 0; i < CarGeneratorArray.size(); i++)
    {
        //WriteSaveBuf(buffer, CarGeneratorArray[i]);
        CopyCarGen(*(CCarGenerator*)buffer, CarGeneratorArray[i]);
        SkipSaveBuf(buffer, sizeof(CCarGenerator));
    }
    VALIDATESAVEBUF(*size)
}

void CarGenerators::LoadAllCarGenerators(uint8* buffer, uint32 size)
{
    const uint32 carGenSize = (sizeof(CCarGenerator) * CarGeneratorArray.size());
    const int32 nGeneralDataSize = sizeof(CTheCarGenerators::NumOfCarGenerators) + sizeof(CTheCarGenerators::CurrentActiveCount) + sizeof(CTheCarGenerators::ProcessCounter) + sizeof(CTheCarGenerators::GenerateEvenIfPlayerIsCloseCounter) + sizeof(int16);

    //Init();
    plugin::Call<0x543020>();

    INITSAVEBUF
        CheckSaveHeader(buffer, 'C', 'G', 'N', '\0', size - SAVE_HEADER_SIZE);
    uint32 tmp;
    ReadSaveBuf(&tmp, buffer);
    assert(tmp == nGeneralDataSize);
    ReadSaveBuf(&CTheCarGenerators::NumOfCarGenerators, buffer);
    ReadSaveBuf(&CTheCarGenerators::CurrentActiveCount, buffer);
    ReadSaveBuf(&CTheCarGenerators::ProcessCounter, buffer);
    ReadSaveBuf(&CTheCarGenerators::GenerateEvenIfPlayerIsCloseCounter, buffer);
    SkipSaveBuf(buffer, 2);
    ReadSaveBuf(&tmp, buffer);
    assert(tmp == carGenSize);
    for (size_t i = 0; i < CarGeneratorArray.size(); i++)
    {
        //ReadSaveBuf(&CarGeneratorArray[i], buffer);
		CopyCarGen(CarGeneratorArray[i], *(CCarGenerator*)buffer);
        SkipSaveBuf(buffer, sizeof(CCarGenerator));
    }
    VALIDATESAVEBUF(size)
}

int32 CarGenerators::CreateCarGenerator(float x, float y, float z, float angle, int32 mi, int16 color1, int16 color2, uint8 force, uint8 alarm, uint8 lock, uint16 min_delay, uint16 max_delay)
{
	uint32 carGenIdx;
    if (DoesCarGenExistAtLocation(x, y, z, angle, mi, carGenIdx))
    {
        CarGeneratorArray[carGenIdx].Setup(x, y, z, angle, mi, color1, color2, force, alarm, lock, min_delay, max_delay);
		return carGenIdx;
    }
    else if (CTheCarGenerators::NumOfCarGenerators < CarGeneratorArray.size())
    {
        CarGeneratorArray[CTheCarGenerators::NumOfCarGenerators].Setup(x, y, z, angle, mi, color1, color2, force, alarm, lock, min_delay, max_delay);
        return CTheCarGenerators::NumOfCarGenerators++;
    }
    return CTheCarGenerators::NumOfCarGenerators;
}
#endif // GTA3

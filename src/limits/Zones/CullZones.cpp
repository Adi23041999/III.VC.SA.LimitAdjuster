/*
* Cull Zone Limits Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "LimitAdjuster.h"

using namespace injector;

#define PATCH_CULLZONE_DAT_SIZE 0
int numCullZones = 512;
int numAttribZones = 288;
int numIndices = 55000;
int numBuildings = 5500;
int numTreadables = 1214;
size_t CCullZone_t = 0x34;
size_t CAttributeZone_t = 0x1C;
std::vector<char> aZones;
std::vector<char> aAttributeZones;
std::vector<unsigned short> aIndices;
std::vector<short> aPointersToBigBuildingsForBuildings;
std::vector<short> aPointersToBigBuildingsForTreadables;

void PatchCullZonesIII()
{
    aZones.resize(CCullZone_t * numCullZones);
    
    WriteMemory(0x524F09, &aZones[0] + 0x0, true);
    WriteMemory(0x524FFD, &aZones[0] + 0x0, true);
    WriteMemory(0x525011, &aZones[0] + 0x0, true);
    WriteMemory(0x525103, &aZones[0] + 0x0, true);
    WriteMemory(0x525117, &aZones[0] + 0x0, true);
    WriteMemory(0x525150, &aZones[0] + 0xC + 0x0, true);
    WriteMemory(0x525160, &aZones[0] + 0xC + 0x4, true);
    WriteMemory(0x52516F, &aZones[0] + 0xC + 0x8, true);
    WriteMemory(0x525181, &aZones[0] + 0x18 + 0x0, true);
    WriteMemory(0x525190, &aZones[0] + 0x18 + 0x4, true);
    WriteMemory(0x5251A2, &aZones[0] + 0x18 + 0x8, true);
    WriteMemory(0x525519, &aZones[0] + 0x0, true);
    WriteMemory(0x52553D, &aZones[0] + 0xC + 0x0, true);
    WriteMemory(0x525547, &aZones[0] + 0xC + 0x4, true);
    WriteMemory(0x525551, &aZones[0] + 0xC + 0x8, true);
    WriteMemory(0x52555B, &aZones[0] + 0x18 + 0x0, true);
    WriteMemory(0x525565, &aZones[0] + 0x18 + 0x4, true);
    WriteMemory(0x52556F, &aZones[0] + 0x18 + 0x8, true);
    WriteMemory(0x525576, &aZones[0] + 0x28, true);
    WriteMemory(0x52557F, &aZones[0] + 0x2A, true);
    WriteMemory(0x525588, &aZones[0] + 0x2C, true);
    WriteMemory(0x525590, &aZones[0] + 0x24, true);
}

void PatchAttribZonesIII()
{
    aAttributeZones.resize(CAttributeZone_t * numAttribZones);

    WriteMemory(0x524F2C, &aAttributeZones[0] + 0x0 + 0x0, true);
    WriteMemory(0x5251F2, &aAttributeZones[0] + 0x0 + 0x0, true);
    WriteMemory(0x5251FF, &aAttributeZones[0] + 0x0 + 0x4, true);
    WriteMemory(0x525211, &aAttributeZones[0] + 0x0 + 0x8, true);
    WriteMemory(0x525220, &aAttributeZones[0] + 0xC + 0x0, true);
    WriteMemory(0x525232, &aAttributeZones[0] + 0xC + 0x4, true);
    WriteMemory(0x525241, &aAttributeZones[0] + 0xC + 0x8, true);
    WriteMemory(0x525252, &aAttributeZones[0] + 0x18 + 0x0, true);
    WriteMemory(0x52525F, &aAttributeZones[0] + 0x1A + 0x0, true);
    WriteMemory(0x5252D3, &aAttributeZones[0] + 0x18 + 0x0, true);
    WriteMemory(0x5252E1, &aAttributeZones[0] + 0x0 + 0x0, true);
    WriteMemory(0x5252F1, &aAttributeZones[0] + 0x0 + 0x4, true);
    WriteMemory(0x525303, &aAttributeZones[0] + 0x0 + 0x8, true);
    WriteMemory(0x525312, &aAttributeZones[0] + 0xC + 0x0, true);
    WriteMemory(0x525322, &aAttributeZones[0] + 0xC + 0x4, true);
    WriteMemory(0x52532F, &aAttributeZones[0] + 0xC + 0x8, true);
    WriteMemory(0x525348, &aAttributeZones[0] + 0x0 + 0x0, true);
    WriteMemory(0x5255B4, &aAttributeZones[0] + 0x0 + 0x0, true);
    WriteMemory(0x5255BE, &aAttributeZones[0] + 0x0 + 0x4, true);
    WriteMemory(0x5255C8, &aAttributeZones[0] + 0x0 + 0x8, true);
    WriteMemory(0x5255D2, &aAttributeZones[0] + 0xC + 0x0, true);
    WriteMemory(0x5255DC, &aAttributeZones[0] + 0xC + 0x4, true);
    WriteMemory(0x5255E6, &aAttributeZones[0] + 0xC + 0x8, true);
    WriteMemory(0x5255F3, &aAttributeZones[0] + 0x18 + 0x0, true);
    WriteMemory(0x5255FA, &aAttributeZones[0] + 0x1A + 0x0, true);
}

void PatchIndicesIII()
{
    aIndices.resize(numIndices);
 
    WriteMemory(0x524F3F, &aIndices[0], true);
    WriteMemory(0x52562A, &aIndices[0], true);
    WriteMemory(0x52564A, &aIndices[0], true);
    WriteMemory(0x52569C, &aIndices[0], true);
    WriteMemory(0x52574B, &aIndices[0], true);
    WriteMemory(0x52582A, &aIndices[0], true);
    WriteMemory(0x52584A, &aIndices[0], true);
    WriteMemory(0x525879, &aIndices[0], true);
    WriteMemory(0x5258BC, &aIndices[0], true);
    WriteMemory(0x52596B, &aIndices[0], true);
    WriteMemory(0x525A54, &aIndices[0], true);
}

void PatchBuildingPointersIII()
{
    aPointersToBigBuildingsForBuildings.resize(numBuildings);
    std::fill(aPointersToBigBuildingsForBuildings.begin(), aPointersToBigBuildingsForBuildings.end(), -1);
    
    //MakeRangedNOP(0x524C10, 0x524C50);
    //MakeRangedNOP(0x524C5A, 0x524D56);
    WriteMemory(0x524F52, &aPointersToBigBuildingsForBuildings[0], true);
    WriteMemory(0x5256ED, &aPointersToBigBuildingsForBuildings[0], true);
    WriteMemory(0x525910, &aPointersToBigBuildingsForBuildings[0], true);
}

void PatchTreadablePointersIII()
{
    aPointersToBigBuildingsForTreadables.resize(numTreadables);
    std::fill(aPointersToBigBuildingsForTreadables.begin(), aPointersToBigBuildingsForTreadables.end(), -1);
    
    //MakeRangedNOP(0x524D60, 0x524DA0);
    //MakeRangedNOP(0x524DAA, 0x524EB8);
    WriteMemory(0x524F65, &aPointersToBigBuildingsForTreadables[0], true);
    WriteMemory(0x5257C8, &aPointersToBigBuildingsForTreadables[0], true);
    WriteMemory(0x5259EB, &aPointersToBigBuildingsForTreadables[0], true);
    WriteMemory(0x525AAA, &aPointersToBigBuildingsForTreadables[0], true);
}

void ReloadCullZonesIII()
{
    WriteMemory(0x8E2C90, -1, true);
    std::fill(aPointersToBigBuildingsForBuildings.begin(), aPointersToBigBuildingsForBuildings.end(), -1);
    std::fill(aPointersToBigBuildingsForTreadables.begin(), aPointersToBigBuildingsForTreadables.end(), -1);
}

class CullZone : public Adjuster
{
public:
    enum
    {
        CullZones,
        AttribZones,
        ZoneIndices,
        CZBuildings, // TODO: figure out how to reuse existing ini entry
        CZTreadables, // - || -
    };

    const Limit* GetLimits()
    {
        if (GetGVM().IsIII())
        {
            static Limit limits[] =
            {
                DEFINE_LIMIT(CullZones),
                DEFINE_LIMIT(AttribZones),
                DEFINE_LIMIT(ZoneIndices),
                DEFINE_LIMIT(CZBuildings),
                DEFINE_LIMIT(CZTreadables),
                FINISH_LIMITS()
            };
            return limits;
        }
        return nullptr;
    }

    void ChangeLimit(int id, const std::string& value)
    {
        if (GetGVM().IsIII())
        {
            switch (id)
            {
            case CullZones:
                numCullZones = std::stoi(value);
                PatchCullZonesIII();
                break;
            case AttribZones:
                numAttribZones = std::stoi(value);
                PatchAttribZonesIII();
                break;
            case ZoneIndices:
                numIndices = std::stoi(value);
                PatchIndicesIII();
                break;
            case CZBuildings:
                numBuildings = std::stoi(value);
                PatchBuildingPointersIII();
                break;
            case CZTreadables:
                numTreadables = std::stoi(value);
                PatchTreadablePointersIII();
                break;
            }
        }
    }

    void Process()
    {
        if (GetGVM().IsIII())
        {
            MakeRangedNOP(0x524BEB, 0x524BF2);
            MakeCALL(0x524BEB, ReloadCullZonesIII);

            // this patches the size of the data read from cullzone.dat
            // we don't need this because we can just make the game read the cull.ipl file instead
            // and also we'd have to regenerate the .dat file to account for the new size
#if PATCH_CULLZONE_DAT_SIZE
            WriteMemory(0x524F04, numCullZones * CCullZone_t, true);
            WriteMemory(0x524F27, numAttribZones * CAttributeZone_t, true);
            WriteMemory(0x524F3A, numIndices * sizeof(unsigned short), true);
            WriteMemory(0x524F4D, numBuildings * sizeof(short), true);
            WriteMemory(0x524F60, numTreadables * sizeof(short), true);
#endif
        }
    }
} CullZone;

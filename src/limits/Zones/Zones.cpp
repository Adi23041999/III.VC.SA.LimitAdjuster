#ifdef GTA3
#include "Zones.h"
#include "Events.h"
#include "CTheZones.h"
#include "cMusicManager.h"
#include "eCrimeType.h"
#include "helpers/SaveBuf.h"

using namespace injector;

bool GameZones::bPatchAudioZones = false;
bool GameZones::bPatchZones = false;
bool GameZones::bPatchMapZones = false;
uint16 GameZones::NumAudioZones = 36;
uint16 GameZones::NumZones = 50;
uint16 GameZones::NumZonesInfos = NumZones * 2;
uint16 GameZones::NumMapZones = 25;

std::vector<short> GameZones::AudioZoneArray;
std::vector<tPoliceRadioZone> GameZones::ZoneSfx;
std::vector<CZone> GameZones::ZoneArray;
std::vector<CZoneInfo> GameZones::ZoneInfoArray;
std::vector<CZone> GameZones::MapZoneArray;

short* ogAudioZoneArray = (short*)(0x713BC0);
CZone* ogZoneArray = (CZone*)(0x86BEE0);
CZoneInfo* ogZoneInfoArray = (CZoneInfo*)(0x714400);
CZone* ogMapZoneArray = (CZone*)(0x663EC0);

uint16& NumberOfAudioZones = *(uint16*)0x95CC84;
uint16& TotalNumberOfMapZones = *(uint16*)0x95CC74;
uint16& TotalNumberOfZones = *(uint16*)0x95CC36;
uint16& TotalNumberOfZoneInfos = *(uint16*)0x95CC3C;

eLevelName& m_CurrLevel = *(eLevelName*)0x8F2BC8;
CZone* m_pPlayersZone = (CZone*)(0x8F254C);
uint16& FindIndex = *(uint16*)0x95CC40;

char* SubZo2Label = (char*)(0x6E9918);
char* SubZo3Label = (char*)(0x6E9870);
bool8& gSpecialSuspectLastSeenReport = *(bool8*)(0x95CD4D);

// -- patches

const Adjuster::Limit* GameZones::GetLimits()
{
    static Limit limits[] =
    {
        DEFINE_LIMIT(AudioZones),
        DEFINE_LIMIT(Zones),
        DEFINE_LIMIT(MapZones),
        FINISH_LIMITS()
    };
    return limits;
}

void GameZones::ChangeLimit(int id, const std::string& value)
{
    switch (id)
    {
    case AudioZones:
        bPatchAudioZones = true;
        NumAudioZones = std::stoi(value);
        PatchAudioZones();
        PatchZoneSfx();
        break;
    case Zones:
        bPatchZones = true;
        NumZones = std::stoi(value);
        NumZonesInfos = NumZones * 2;
        PatchZoneArray();
        PatchZoneInfoArray();
        break;
    case MapZones:
        bPatchMapZones = true;
        NumMapZones = std::stoi(value);
        PatchMapZoneArray();
        break;
    }
}

void GameZones::Process()
{
    if (bPatchAudioZones || bPatchZones || bPatchMapZones)
    {
        MakeCALL(0x48BFDD, TheZones_Init);
        MakeCALL(0x590322, TheZones_SaveAllZones);
        MakeCALL(0x5913F5, TheZones_LoadAllZones);

        if (bPatchAudioZones)
        {
			WriteMemory(0x57EB59, &ZoneSfx[0], true); // just so others can access the patched array
            MakeJMP(0x57EAC0, cAudioManagerEx::InitialisePoliceRadioZones);
            MakeJMP(0x57F5B0, &cAudioManagerEx::SetupCrimeReport);
            MakeJMP(0x580500, &cAudioManagerEx::PlaySuspectLastSeen);
            MakeJMP(0x4B83E0, cAudioManagerEx::FindAudioZone);
            MakeJMP(0x4B8340, AddZoneToAudioZoneArray);
        }

        if (!bPatchMapZones)
        {
            // vanilla fix
            MakeCALL(0x4B8886, GetIndexForMapZonePointerOgFixed);
            MakeCALL(0x4B8898, GetIndexForMapZonePointerOgFixed);
            MakeCALL(0x4B88AA, GetIndexForMapZonePointerOgFixed);
            MakeCALL(0x4B8CA7, GetPointerForMapZoneIndexOgFixed);
            MakeCALL(0x4B8CB9, GetPointerForMapZoneIndexOgFixed);
            MakeCALL(0x4B8CD1, GetPointerForMapZoneIndexOgFixed);
        }
    }
}

void GameZones::PatchAudioZones()
{
    AudioZoneArray.resize(NumAudioZones);

    WriteMemory(0x4B8377, &AudioZoneArray[0], true);
    WriteMemory(0x4B83F9, &AudioZoneArray[0], true);
    WriteMemory(0x57F66A, &AudioZoneArray[0], true);
    WriteMemory(0x580586, &AudioZoneArray[0], true);
}

void GameZones::PatchZoneSfx()
{
    ZoneSfx.resize(NumAudioZones);

    //// ul test
    //tPoliceRadioZone* sfx = (tPoliceRadioZone*)ZoneSfx.data();
    //tPoliceRadioZone& ultest = sfx[numAudioZones - 1];
    //strcpy(ultest.m_aName, "UL_ZON0");
    //ultest.m_nSampleIndex = 236; // chinatown
}

void GameZones::PatchZoneArray()
{
    ZoneArray.resize(NumZones);

    WriteMemory(0x4B62DE, &ZoneArray[0], true);
    WriteMemory(0x4B6301, &ZoneArray[0].m_eZoneType, true);
    WriteMemory(0x4B6307, &ZoneArray[0].m_vecMin.x, true);
    WriteMemory(0x4B6311, &ZoneArray[0].m_vecMin.y, true);
    WriteMemory(0x4B631B, &ZoneArray[0].m_vecMin.z, true);
    WriteMemory(0x4B6325, &ZoneArray[0].m_vecMax.x, true);
    WriteMemory(0x4B632F, &ZoneArray[0].m_vecMax.y, true);
    WriteMemory(0x4B6339, &ZoneArray[0].m_vecMax.z, true);
    WriteMemory(0x4B633F, &ZoneArray[0].m_eLevel, true);
    WriteMemory(0x4B635A, &ZoneArray[0].m_nZoneDay, true);
    WriteMemory(0x4B636E, &ZoneArray[0].m_nZoneNight, true);
    WriteMemory(0x4B64D2, &ZoneArray[1], true);
    WriteMemory(0x4B6505, &ZoneArray[0], true);
    WriteMemory(0x4B6795, &ZoneArray[0], true);
    WriteMemory(0x4B67AA, &ZoneArray[0].m_eZoneType, true);
    WriteMemory(0x4B67B3, &ZoneArray[0], true);
    WriteMemory(0x4B67BB, &ZoneArray[0].m_pChild, true);
    WriteMemory(0x4B689B, &ZoneArray[0], true);
    WriteMemory(0x4B68A6, &ZoneArray[0].m_eZoneType, true);
    WriteMemory(0x4B68BB, &ZoneArray[0], true);
    WriteMemory(0x4B68C3, &ZoneArray[0].m_pChild, true);
    WriteMemory(0x4B69B9, &ZoneArray[0], true);
    WriteMemory(0x4B69C8, &ZoneArray[0].m_pChild, true);
    WriteMemory(0x4B69CE, &ZoneArray[0], true);
    WriteMemory(0x4B6FA9, &ZoneArray[0], true);
    WriteMemory(0x4B8351, &ZoneArray[0], true);
    WriteMemory(0x4B8381, &ZoneArray[0], true);
    WriteMemory(0x4B838C, &ZoneArray[0], true);
    //WriteMemory(0x4B84D7, &ZoneArray[0], true); // GetIndexForZonePointer
    //WriteMemory(0x4B8503, &ZoneArray[0], true); // GetPointerForZoneIndex
    WriteMemory(0x57F673, &ZoneArray[0], true);
    WriteMemory(0x58058F, &ZoneArray[0], true);
}

void GameZones::PatchZoneInfoArray()
{
    ZoneInfoArray.resize(NumZonesInfos);

    WriteMemory(0x4B6A2E, &ZoneInfoArray[0], true);
    WriteMemory(0x4B6A3B, &ZoneInfoArray[0], true);
    WriteMemory(0x4B6A41, &ZoneInfoArray[0], true);
    WriteMemory(0x4B6A7F, &ZoneInfoArray[0], true);
    WriteMemory(0x4B6DFC, &ZoneInfoArray[0], true);
    WriteMemory(0x4B6EF9, &ZoneInfoArray[0].carDensity, true);
    WriteMemory(0x4B6F49, &ZoneInfoArray[0].pedDensity, true);
    WriteMemory(0x4B6F99, &ZoneInfoArray[0].pedgrp, true);
}

void GameZones::PatchMapZoneArray()
{
    MapZoneArray.resize(NumMapZones);

    WriteMemory(0x4B6445, &MapZoneArray[0], true);
    WriteMemory(0x4B646C, &MapZoneArray[0].m_eZoneType, true);
    WriteMemory(0x4B6476, &MapZoneArray[0].m_vecMin.x, true);
    WriteMemory(0x4B6480, &MapZoneArray[0].m_vecMin.y, true);
    WriteMemory(0x4B648A, &MapZoneArray[0].m_vecMin.z, true);
    WriteMemory(0x4B6494, &MapZoneArray[0].m_vecMax.x, true);
    WriteMemory(0x4B649E, &MapZoneArray[0].m_vecMax.y, true);
    WriteMemory(0x4B64A8, &MapZoneArray[0].m_vecMax.z, true);
    WriteMemory(0x4B64AE, &MapZoneArray[0].m_eLevel, true);
    WriteMemory(0x4B691C, &MapZoneArray[0], true);
    WriteMemory(0x4B695E, &MapZoneArray[0], true);
    WriteMemory(0x4B696A, &MapZoneArray[1], true);
    WriteMemory(0x4B6985, &MapZoneArray[0], true);
}

void GameZones::TheZones_Init()
{
    plugin::CallDynGlobal(0x4B5DE0);

    if (bPatchAudioZones)
    {
        for (size_t i = 0; i < NumAudioZones; i++)
            AudioZoneArray[i] = -1;
    }

    if (bPatchZones)
    {
        for (size_t i = 0; i < NumZones; i++)
            memset(&ZoneArray[i], 0, sizeof(CZone));

        CZoneInfo* zonei;
        int x = 1000 / 6;
        for (size_t i = 0; i < NumZonesInfos; i++) {
            zonei = &ZoneInfoArray[i];
            zonei->carDensity = 10;
            zonei->carPoorfamily = x;
            zonei->carRichfamily = zonei->carPoorfamily + x;
            zonei->carExecutive = zonei->carRichfamily + x;
            zonei->carWorker = zonei->carExecutive + x;
            zonei->carSpecial = zonei->carWorker;
            zonei->carBig = zonei->carSpecial;
            zonei->carCops = zonei->carBig + x;
            zonei->carLeone = zonei->carCops;
            zonei->carTriad = zonei->carLeone;
            zonei->carDiablo = zonei->carTriad;
            zonei->carYakuza = zonei->carDiablo;
            zonei->carYardie = zonei->carYakuza;
            zonei->carColombian = zonei->carYardie;
            zonei->carHood = zonei->carColombian;
            zonei->carForelli = zonei->carHood;
            zonei->carSindacco = zonei->carForelli;
            // not in re3 wtf?
            zonei->pedDensity = 12;
            zonei->copDensity = 50;
            zonei->pedLeone = 0;
            zonei->pedTriad = 0;
            zonei->pedDiablo = 0;
            zonei->pedYakuza = 0;
            zonei->pedYardie = 0;
            zonei->pedColombian = 0;
            zonei->pedHood = 0;
            zonei->pedForelli = 0;
            zonei->pedSindacco = 0;
            zonei->pedgrp = 0;
        }

        m_pPlayersZone = &ZoneArray[0];

        CZone& zone = ZoneArray[0];
        strcpy(zone.m_aName, "CITYZON");
        zone.m_vecMin.x = -4000.0f;
        zone.m_vecMin.y = -4000.0f;
        zone.m_vecMin.z = -500.0f;
        zone.m_vecMax.x = 4000.0f;
        zone.m_vecMax.y = 4000.0f;
        zone.m_vecMax.z = 500.0f;
        zone.m_eLevel = GENERIC;
    }

    if (bPatchMapZones)
    {
        for (size_t i = 0; i < NumMapZones; i++) {
            memset(&MapZoneArray[i], 0, sizeof(CZone));
            MapZoneArray[i].m_eZoneType = ZONE_MAPZONE;
        }

        CZone& mapzone = (CZone&)MapZoneArray[0];
        strcpy(mapzone.m_aName, "THEMAP");
        mapzone.m_vecMin.x = -4000.0f;
        mapzone.m_vecMin.y = -4000.0f;
        mapzone.m_vecMin.z = -500.0f;
        mapzone.m_vecMax.x = 4000.0f;
        mapzone.m_vecMax.y = 4000.0f;
        mapzone.m_vecMax.z = 500.0f;
        mapzone.m_eLevel = GENERIC;
    }
}

void GameZones::TheZones_SaveAllZones(uint8_t* buffer, uint32_t* size)
{
    INITSAVEBUF

    *size = SAVE_HEADER_SIZE
        + sizeof(int) // GetIndexForZonePointer
        + sizeof(m_CurrLevel) + sizeof(FindIndex)
        + sizeof(int16_t); // padding

    WriteSaveHeader(buffer, 'Z', 'N', 'S', '\0', *size - SAVE_HEADER_SIZE);

    WriteSaveBuf(buffer, (int)GetIndexForZonePointer(m_pPlayersZone));
    WriteSaveBuf(buffer, m_CurrLevel);
    WriteSaveBuf(buffer, FindIndex);
    WriteSaveBuf(buffer, (int16_t)0); // padding

    short* savedAudioZoneArray = bPatchAudioZones ? &AudioZoneArray[0] : ogAudioZoneArray;
    CZone* savedZoneArray = bPatchZones ? &ZoneArray[0] : ogZoneArray;
    CZoneInfo* savedZoneInfoArray = bPatchZones ? &ZoneInfoArray[0] : ogZoneInfoArray;
    CZone* savedMapZoneArray = bPatchMapZones ? &MapZoneArray[0] : ogMapZoneArray;

    *size +=
          (sizeof(short) * NumAudioZones) 
        + (sizeof(CZone) * NumZones)
        + (sizeof(CZoneInfo) * NumZonesInfos)
        + (sizeof(CZone) * NumMapZones);

    for (size_t i = 0; i < NumAudioZones; i++)
        WriteSaveBuf(buffer, savedAudioZoneArray[i]);

    for (size_t i = 0; i < NumZones; ++i)
    {
        CZone* zone = WriteSaveBuf(buffer, savedZoneArray[i]);
        zone->m_pChild = (CZone*)GetIndexForZonePointer(savedZoneArray[i].m_pChild);
        zone->m_pParent = (CZone*)GetIndexForZonePointer(savedZoneArray[i].m_pParent);
        zone->m_pNext = (CZone*)GetIndexForZonePointer(savedZoneArray[i].m_pNext);
    }

    for (size_t i = 0; i < NumZonesInfos; i++)
        WriteSaveBuf(buffer, savedZoneInfoArray[i]);

    for (size_t i = 0; i < NumMapZones; ++i)
    {
        CZone* zone = WriteSaveBuf(buffer, savedMapZoneArray[i]);
        zone->m_pChild = (CZone*)GetIndexForMapZonePointer(savedMapZoneArray[i].m_pChild);
        zone->m_pParent = (CZone*)GetIndexForMapZonePointer(savedMapZoneArray[i].m_pParent);
        zone->m_pNext = (CZone*)GetIndexForMapZonePointer(savedMapZoneArray[i].m_pNext);
    }
}

void GameZones::TheZones_LoadAllZones(uint8_t* buffer)
{
    TheZones_Init();

    SkipSaveBuf(buffer, 8); // CheckSaveHeader

    int index;
    ReadSaveBuf(&index, buffer);
    m_pPlayersZone = GetPointerForZoneIndex(index);
    ReadSaveBuf(&m_CurrLevel, buffer);
    ReadSaveBuf(&FindIndex, buffer);
    SkipSaveBuf(buffer, 2);
    
    short* loadedAudioZoneArray = bPatchAudioZones ? &AudioZoneArray[0] : ogAudioZoneArray;
    CZone* loadedZoneArray = bPatchZones ? &ZoneArray[0] : ogZoneArray;
    CZoneInfo* loadedZoneInfoArray = bPatchZones ? &ZoneInfoArray[0] : ogZoneInfoArray;
    CZone* loadedMapZoneArray = bPatchMapZones ? &MapZoneArray[0] : ogMapZoneArray;

    if (bPatchAudioZones)
        assert(AudioZoneArray.size() == NumAudioZones);
    if (bPatchZones) {
        assert(ZoneArray.size() == NumZones);
        assert(ZoneInfoArray.size() == NumZonesInfos);
    }
    if (bPatchMapZones)
        assert(MapZoneArray.size() == NumMapZones);

    for (size_t i = 0; i < NumAudioZones; ++i)
        ReadSaveBuf(&loadedAudioZoneArray[i], buffer);

    NumberOfAudioZones = NumAudioZones;

    for (size_t i = 0; i < NumZones; ++i)
    {
        ReadSaveBuf(&loadedZoneArray[i], buffer);
        loadedZoneArray[i].m_pChild = GetPointerForZoneIndex((uintptr_t)loadedZoneArray[i].m_pChild);
        loadedZoneArray[i].m_pParent = GetPointerForZoneIndex((uintptr_t)loadedZoneArray[i].m_pParent);
        loadedZoneArray[i].m_pNext = GetPointerForZoneIndex((uintptr_t)loadedZoneArray[i].m_pNext);
    }

    for (size_t i = 0; i < NumZonesInfos; i++)
        ReadSaveBuf(&loadedZoneInfoArray[i], buffer);

    TotalNumberOfZones = NumZones;
    TotalNumberOfZoneInfos = NumZonesInfos;

    for (size_t i = 0; i < NumMapZones; ++i)
    {
        ReadSaveBuf(&loadedMapZoneArray[i], buffer);
        loadedMapZoneArray[i].m_pChild = GetPointerForMapZoneIndex((uintptr_t)loadedMapZoneArray[i].m_pChild);
        loadedMapZoneArray[i].m_pParent = GetPointerForMapZoneIndex((uintptr_t)loadedMapZoneArray[i].m_pParent);
        loadedMapZoneArray[i].m_pNext = GetPointerForMapZoneIndex((uintptr_t)loadedMapZoneArray[i].m_pNext);
    }

    TotalNumberOfMapZones = NumMapZones;
}

void GameZones::AddZoneToAudioZoneArray(CZone* zone)
{
    CZone* usedZoneArray = bPatchZones ? &ZoneArray[0] : ogZoneArray;
    int i, z;

    if (zone->m_eZoneType != ZONE_DEFAULT)
        return;

    /* This is a bit stupid */
    z = -1;
    for (i = 0; i < NumZones; i++)
        if (&usedZoneArray[i] == zone)
            z = i;
    AudioZoneArray[NumberOfAudioZones++] = z;
}

ptrdiff_t GameZones::GetIndexForZonePointer(CZone* zone)
{
    return zone == nullptr ? -1 : zone - &ZoneArray[0];
}

CZone* GameZones::GetPointerForZoneIndex(ptrdiff_t i)
{
    return i == -1 ? nullptr : &ZoneArray[i];
}

ptrdiff_t GameZones::GetIndexForMapZonePointer(CZone* zone)
{
    return zone == nullptr ? -1 : zone - &MapZoneArray[0];
}

CZone* GameZones::GetPointerForMapZoneIndex(ptrdiff_t i)
{
    return i == -1 ? nullptr : &MapZoneArray[i];
}

ptrdiff_t GameZones::GetIndexForMapZonePointerOgFixed(CZone* zone)
{
    return zone == nullptr ? -1 : zone - ogMapZoneArray;
}

CZone* GameZones::GetPointerForMapZoneIndexOgFixed(ptrdiff_t i)
{
    return i == -1 ? nullptr : &ogMapZoneArray[i];
}

bool GameZones::PointLiesWithinZone(const CVector* v, CZone* zone)
{
    return zone->m_vecMin.x <= v->x && v->x <= zone->m_vecMax.x &&
        zone->m_vecMin.y <= v->y && v->y <= zone->m_vecMax.y &&
        zone->m_vecMin.z <= v->z && v->z <= zone->m_vecMax.z;
}

CZone* cAudioManagerEx::GetAudioZone(uint16 i)
{
    return &GameZones::ZoneArray[GameZones::AudioZoneArray[i]];
}

uint16 cAudioManagerEx::FindAudioZone(CVector* pos)
{
    int i;

    for (i = 0; i < GameZones::NumAudioZones; i++)
        if (GameZones::PointLiesWithinZone(pos, GetAudioZone(i)))
            return i;
    return -1;
}

void cAudioManagerEx::SETZONESFX(int i, const char* name, uint32_t sample)
{
    strcpy(GameZones::ZoneSfx[i].m_aName, name);
    GameZones::ZoneSfx[i].m_nSampleIndex = sample;
}

bool8 cAudioManagerEx::PoliceRadioQueue_Add(cPoliceRadioQueue& queue, uint32_t sample)
{
    if (queue.m_nSamplesInQueue != POLICE_RADIO_QUEUE_MAX_SAMPLES) {
        queue.m_aSamples[queue.m_nAddOffset] = sample;
        queue.m_nSamplesInQueue++;
        queue.m_nAddOffset = (queue.m_nAddOffset + 1) % POLICE_RADIO_QUEUE_MAX_SAMPLES;
        return TRUE;
    }
    return FALSE;
}

void cAudioManagerEx::InitialisePoliceRadioZones()
{
    for (int i = 0; i < GameZones::NumAudioZones; i++)
        SETZONESFX(i, "A", SFX_POLICE_RADIO_ROCKFORD);

    SETZONESFX(0, "HOSPI_2", SFX_POLICE_RADIO_ROCKFORD);
    SETZONESFX(1, "CONSTRU", SFX_POLICE_RADIO_FORT_STAUNTON);
    SETZONESFX(2, "STADIUM", SFX_POLICE_RADIO_ASPATRIA);
    SETZONESFX(3, "YAKUSA", SFX_POLICE_RADIO_TORRINGTON);
    SETZONESFX(4, "SHOPING", SFX_POLICE_RADIO_BEDFORD_POINT);
    SETZONESFX(5, "COM_EAS", SFX_POLICE_RADIO_NEWPORT);
    SETZONESFX(6, "PARK", SFX_POLICE_RADIO_BELLEVILLE_PARK);
    SETZONESFX(7, "UNIVERS", SFX_POLICE_RADIO_LIBERTY_CAMPUS);
    SETZONESFX(8, "BIG_DAM", SFX_POLICE_RADIO_COCHRANE_DAM);
    SETZONESFX(9, "SUB_IND", SFX_POLICE_RADIO_PIKE_CREEK);
    SETZONESFX(10, "SWANKS", SFX_POLICE_RADIO_CEDAR_GROVE);
    SETZONESFX(11, "PROJECT", SFX_POLICE_RADIO_WICHITA_GARDENS);
    SETZONESFX(12, "AIRPORT", SFX_POLICE_RADIO_FRANCIS_INTERNATIONAL_AIRPORT);
    SETZONESFX(13, "PORT_W", SFX_POLICE_RADIO_CALLAHAN_POINT);
    SETZONESFX(14, "PORT_S", SFX_POLICE_RADIO_ATLANTIC_QUAYS);
    SETZONESFX(15, "PORT_E", SFX_POLICE_RADIO_PORTLAND_HARBOUR);
    SETZONESFX(16, "PORT_I", SFX_POLICE_RADIO_TRENTON);
    SETZONESFX(17, "CHINA", SFX_POLICE_RADIO_CHINATOWN);
    SETZONESFX(18, "REDLIGH", SFX_POLICE_RADIO_RED_LIGHT_DISTRICT);
    SETZONESFX(19, "TOWERS", SFX_POLICE_RADIO_HEPBURN_HEIGHTS);
    SETZONESFX(20, "LITTLEI", SFX_POLICE_RADIO_SAINT_MARKS);
    SETZONESFX(21, "HARWOOD", SFX_POLICE_RADIO_HARWOOD);
    SETZONESFX(22, "EASTBAY", SFX_POLICE_RADIO_PORTLAND_BEACH);
    SETZONESFX(23, "S_VIEW", SFX_POLICE_RADIO_PORTLAND_STRAIGHTS);
    SETZONESFX(24, "CITYZON", SFX_POLICE_RADIO_LIBERTY_CITY);
    SETZONESFX(25, "IND_ZON", SFX_POLICE_RADIO_PORTLAND);
    SETZONESFX(26, "COM_ZON", SFX_POLICE_RADIO_STAUNTON_ISLAND);
    SETZONESFX(27, "SUB_ZON", SFX_POLICE_RADIO_SHORESIDE_VALE);
    SETZONESFX(28, "SUB_ZO2", SFX_POLICE_RADIO_SHORESIDE_VALE);
    SETZONESFX(29, "SUB_ZO3", SFX_POLICE_RADIO_SHORESIDE_VALE);
    SETZONESFX(30, "A", SFX_POLICE_RADIO_ROCKFORD);
    SETZONESFX(31, "A", SFX_POLICE_RADIO_ROCKFORD);
    SETZONESFX(32, "A", SFX_POLICE_RADIO_ROCKFORD);
    SETZONESFX(33, "A", SFX_POLICE_RADIO_ROCKFORD);
    SETZONESFX(34, "A", SFX_POLICE_RADIO_ROCKFORD);

#undef SETZONESFX

    strcpy(SubZo2Label, "SUB_ZO2");
    strcpy(SubZo3Label, "SUB_ZO3");
}

bool8 cAudioManagerEx::SetupCrimeReport()
{
    int16_t audioZoneId;
    CZone* zone;
    float rangeX;
    float rangeY;
    float halfX;
    float halfY;
    float quarterX;
    float quarterY;
    int i;
    uint32_t sampleIndex;
    bool8 processed = FALSE;
    if (gMusicManager.m_nMusicMode == MUSICMODE_CUTSCENE) return FALSE;

    if (POLICE_RADIO_QUEUE_MAX_SAMPLES - m_sPoliceRadioQueue.m_nSamplesInQueue <= 9) {
        plugin::CallMethod<0x580AF0>(this); //AgeCrimes();
        return TRUE;
    }

    for (i = 0; i < ARRAY_SIZE(cAudioManager::m_aCrimes); i++) {
        if (m_aCrimes[i].type != CRIME_NONE)
            break;
    }

    if (i == ARRAY_SIZE(m_aCrimes)) return FALSE;
    audioZoneId = FindAudioZone(&m_aCrimes[i].position);
    if (audioZoneId >= 0 && audioZoneId < GameZones::NumAudioZones) {
        zone = GetAudioZone(audioZoneId);
        for (int j = 0; j < GameZones::NumAudioZones; j++) {
            if (strcmp(zone->m_aName, GameZones::ZoneSfx[j].m_aName) == 0) {
                sampleIndex = GameZones::ZoneSfx[j].m_nSampleIndex;
                PoliceRadioQueue_Add(m_sPoliceRadioQueue, m_anRandomTable[4] % 3 + SFX_POLICE_RADIO_MESSAGE_NOISE_1);
                PoliceRadioQueue_Add(m_sPoliceRadioQueue, m_anRandomTable[0] % 3 + SFX_WEVE_GOT);
                PoliceRadioQueue_Add(m_sPoliceRadioQueue, m_anRandomTable[1] % 2 + SFX_A_10_1);
                switch (m_aCrimes[i].type) {
                case CRIME_PED_BURNED: m_aCrimes[i].type = CRIME_HIT_PED; break;
                case CRIME_COP_BURNED: m_aCrimes[i].type = CRIME_HIT_COP; break;
                case CRIME_VEHICLE_BURNED: m_aCrimes[i].type = CRIME_STEAL_CAR; break;
                case CRIME_DESTROYED_CESSNA: m_aCrimes[i].type = CRIME_SHOOT_HELI; break;
                default: break;
                }
                PoliceRadioQueue_Add(m_sPoliceRadioQueue, m_aCrimes[i].type + SFX_CRIME_1 - 1);
                PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_IN);
                if (sampleIndex == SFX_POLICE_RADIO_SHORESIDE_VALE &&
                    (strcmp(zone->m_aName, SubZo2Label) == 0 || strcmp(zone->m_aName, SubZo3Label) == 0)) {
                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_NORTH);
                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_EAST);
                }
                else {
                    rangeX = zone->m_vecMax.x - zone->m_vecMin.x;
                    rangeY = zone->m_vecMax.y - zone->m_vecMin.y;
                    halfX = 0.5f * rangeX + zone->m_vecMin.x;
                    halfY = 0.5f * rangeY + zone->m_vecMin.y;
                    quarterX = 0.25f * rangeX;
                    quarterY = 0.25f * rangeY;

                    if (m_aCrimes[i].position.y > halfY + quarterY) {
                        PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_NORTH);
                        processed = TRUE;
                    }
                    else if (m_aCrimes[i].position.y < halfY - quarterY) {
                        PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_SOUTH);
                        processed = TRUE;
                    }

                    if (m_aCrimes[i].position.x > halfX + quarterX)
                        PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_EAST);
                    else if (m_aCrimes[i].position.x < halfX - quarterX)
                        PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_WEST);
                    else if (!processed)
                        PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_CENTRAL);

                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, sampleIndex);
                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, m_anRandomTable[2] % 3 + SFX_POLICE_RADIO_MESSAGE_NOISE_1);
                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, TOTAL_AUDIO_SAMPLES);
                }
                break;
            }
        }
    }
    m_aCrimes[i].type = CRIME_NONE;
    plugin::CallMethod<0x580AF0>(this); //AgeCrimes();
    return TRUE;
}

void cAudioManagerEx::PlaySuspectLastSeen(float x, float y, float z)
{
    int16_t audioZone;
    CZone* zone;
    float rangeX;
    float rangeY;
    float halfX;
    float halfY;
    float quarterX;
    float quarterY;
    uint32_t sample;
    bool8 processed = FALSE;
    CVector vec = CVector(x, y, z);

    if (!m_bIsInitialised) return;

    if (gMusicManager.m_nMusicMode != MUSICMODE_CUTSCENE && POLICE_RADIO_QUEUE_MAX_SAMPLES - m_sPoliceRadioQueue.m_nSamplesInQueue > 9) {
        audioZone = FindAudioZone(&vec);
        if (audioZone >= 0 && audioZone < GameZones::NumAudioZones) {
            zone = GetAudioZone(audioZone);
            for (int i = 0; i < GameZones::NumAudioZones; i++) {
                if (strcmp(zone->m_aName, GameZones::ZoneSfx[i].m_aName) == 0) {
                    sample = GameZones::ZoneSfx[i].m_nSampleIndex;
                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, m_anRandomTable[4] % 3 + SFX_POLICE_RADIO_MESSAGE_NOISE_1);
                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_POLICE_RADIO_SUSPECT);
                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_POLICE_RADIO_LAST_SEEN);
                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_IN);
                    if (sample == SFX_POLICE_RADIO_SHORESIDE_VALE &&
                        (strcmp(zone->m_aName, SubZo2Label) == 0 ||
                            strcmp(zone->m_aName, SubZo3Label) == 0)) {
                        PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_NORTH);
                        PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_EAST);
                    }
                    else {
                        rangeX = zone->m_vecMax.x - zone->m_vecMin.x;
                        rangeY = zone->m_vecMax.y - zone->m_vecMin.y;
                        halfX = 0.5f * rangeX + zone->m_vecMin.x;
                        halfY = 0.5f * rangeY + zone->m_vecMin.y;
                        quarterX = 0.25f * rangeX;
                        quarterY = 0.25f * rangeY;

                        if (vec.y > halfY + quarterY) {
                            PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_NORTH);
                            processed = TRUE;
                        }
                        else if (vec.y < halfY - quarterY) {
                            PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_SOUTH);
                            processed = TRUE;
                        }

                        if (vec.x > halfX + quarterX)
                            PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_EAST);
                        else if (vec.x < halfX - quarterX)
                            PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_WEST);
                        else if (!processed)
                            PoliceRadioQueue_Add(m_sPoliceRadioQueue, SFX_CENTRAL);
                    }
                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, sample);
                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, m_anRandomTable[2] % 3 + SFX_POLICE_RADIO_MESSAGE_NOISE_1);
                    PoliceRadioQueue_Add(m_sPoliceRadioQueue, TOTAL_AUDIO_SAMPLES);
                    gSpecialSuspectLastSeenReport = TRUE;
                    break;
                }
            }
        }
    }
}
#endif // GTA3

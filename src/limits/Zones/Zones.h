/*
* Zones Limits Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "LimitAdjuster.h"
#include "Events.h"
#include "cAudioManager.h"

#ifdef GTA3
class GameZones : public Adjuster
{
public:
    enum
    {
        AudioZones,
        Zones,
        MapZones,
    };

    virtual const Limit* GetLimits() override;
    virtual void ChangeLimit(int id, const std::string& value) override;
    virtual void Process() override;

    static void PatchAudioZones();
    static void PatchZoneSfx();
    static void PatchZoneArray();
    static void PatchZoneInfoArray();
    static void PatchMapZoneArray();

    static void TheZones_Init();
    static void TheZones_SaveAllZones(uint8_t* buffer, uint32_t* size);
    static void TheZones_LoadAllZones(uint8_t* buffer);
} GameZones;

#define POLICE_RADIO_QUEUE_MAX_SAMPLES 60
#define ARRAY_SIZE(array)                (sizeof(array) / sizeof(array[0]))

class cAudioManagerEx : public cAudioManager
{
public:
    static void InitialisePoliceRadioZones();
    bool8 SetupCrimeReport();
    void PlaySuspectLastSeen(float x, float y, float z);
};

struct tPoliceRadioZone {
    char m_aName[8];
    unsigned int m_nSampleIndex;
    int field_12;
};

enum
{
    SFX_POLICE_RADIO_CRACKLE = 188,
    SFX_WEVE_GOT,
    SFX_THERES,
    SFX_RESPOND_TO,
    SFX_A_10_1,
    SFX_A_10_2,
    SFX_CRIME_1,
    SFX_CRIME_2,
    SFX_CRIME_3,
    SFX_CRIME_4,
    SFX_CRIME_5,
    SFX_CRIME_6,
    SFX_CRIME_7,
    SFX_CRIME_8,
    SFX_CRIME_9,
    SFX_CRIME_10,
    SFX_CRIME_11,
    SFX_CRIME_12,
    SFX_IN,
    SFX_NORTH,
    SFX_EAST,
    SFX_SOUTH,
    SFX_WEST,
    SFX_CENTRAL,
    SFX_POLICE_RADIO_MESSAGE_NOISE_1,
    SFX_POLICE_RADIO_MESSAGE_NOISE_2,
    SFX_POLICE_RADIO_MESSAGE_NOISE_3,
    SFX_POLICE_RADIO_LIBERTY_CITY,
    SFX_POLICE_RADIO_PORTLAND,
    SFX_POLICE_RADIO_STAUNTON_ISLAND,
    SFX_POLICE_RADIO_SHORESIDE_VALE,
    SFX_POLICE_RADIO_ROCKFORD,
    SFX_POLICE_RADIO_FORT_STAUNTON,
    SFX_POLICE_RADIO_ASPATRIA,
    SFX_POLICE_RADIO_TORRINGTON,
    SFX_POLICE_RADIO_BEDFORD_POINT,
    SFX_POLICE_RADIO_NEWPORT,
    SFX_POLICE_RADIO_BELLEVILLE_PARK,
    SFX_POLICE_RADIO_LIBERTY_CAMPUS,
    SFX_POLICE_RADIO_COCHRANE_DAM,
    SFX_POLICE_RADIO_PIKE_CREEK,
    SFX_POLICE_RADIO_CEDAR_GROVE,
    SFX_POLICE_RADIO_WICHITA_GARDENS,
    SFX_POLICE_RADIO_FRANCIS_INTERNATIONAL_AIRPORT,
    SFX_POLICE_RADIO_CALLAHAN_POINT,
    SFX_POLICE_RADIO_ATLANTIC_QUAYS,
    SFX_POLICE_RADIO_PORTLAND_HARBOUR,
    SFX_POLICE_RADIO_TRENTON,
    SFX_POLICE_RADIO_CHINATOWN,
    SFX_POLICE_RADIO_RED_LIGHT_DISTRICT,
    SFX_POLICE_RADIO_HEPBURN_HEIGHTS,
    SFX_POLICE_RADIO_SAINT_MARKS,
    SFX_POLICE_RADIO_HARWOOD,
    SFX_POLICE_RADIO_PORTLAND_BEACH,
    SFX_POLICE_RADIO_PORTLAND_STRAIGHTS, // shouldn't be used anymore
    SFX_POLICE_RADIO_SUSPECT,
    SFX_POLICE_RADIO_LAST_SEEN,
    TOTAL_AUDIO_SAMPLES = 3032,
};

enum eMusicMode
{
    MUSICMODE_FRONTEND = 0,
    MUSICMODE_GAME,
    MUSICMODE_CUTSCENE,
    MUSICMODE_DISABLE,
    MUSICMODE_DISABLED,
};

enum eCrimeTypeRe {
    CRIME_NONE,
    CRIME_POSSESSION_GUN,
    CRIME_HIT_PED,
    CRIME_HIT_COP,
    CRIME_SHOOT_PED,
    CRIME_SHOOT_COP,
    CRIME_STEAL_CAR,
    CRIME_RUN_REDLIGHT,
    CRIME_RECKLESS_DRIVING,
    CRIME_SPEEDING,
    CRIME_RUNOVER_PED,
    CRIME_RUNOVER_COP,
    CRIME_SHOOT_HELI,
    CRIME_PED_BURNED,
    CRIME_COP_BURNED,
    CRIME_VEHICLE_BURNED,
    CRIME_DESTROYED_CESSNA,
    NUM_CRIME_TYPES
};
#endif // GTA3

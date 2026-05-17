/*
* Script Limits Adjuster
* Copyright (c) 2026 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"
#include "OLACommon.h"


#ifdef GTA3

enum {
    USED_OBJECT_NAME_LENGTH = 24
};

struct tUsedObject
{
    char name[USED_OBJECT_NAME_LENGTH];
    int32 index;
};

struct tBuildingSwap
{
    class CBuilding* m_pBuilding;
    int32 m_nNewModel;
    int32 m_nOldModel;
};

class Script : public Adjuster
{
public:
    enum
    {
        UsedObjects,
        MissionScripts,
        BuildingSwaps,
        InvisibilitySettings,
    };

    static int32 NumUsedObjects;
    static std::vector<tUsedObject> UsedObjectsArray;
    static int32 NumMultiScripts;
    static std::vector<uint8> MultiScriptArray;
    static int8 NumBuildingSwaps;
    static std::vector<tBuildingSwap> BuildingSwapArray;
    static int32 NumInvisibilitySettings;
    static std::vector<class CEntity*> InvisibilitySettingArray;

    virtual const Limit* Script::GetLimits() override;
    virtual void ChangeLimit(int id, const std::string& value) override;
} Script;
#endif // GTA3

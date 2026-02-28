/*
* Car Generators Limit Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"
#include "OLACommon.h"

#ifdef GTA3
class CarGenerators : public SimpleAdjuster
{
public:
    static std::vector<class CCarGenerator> CarGeneratorArray;

    virtual const char* GetLimitName() override;
    virtual void ChangeLimit(int id, const std::string& value) override;

    static void CopyCarGen(CCarGenerator& lhs, const CCarGenerator& rhs);
    static bool DoesCarGenExistAtLocation(float x, float y, float z, float angle, int32 mi, uint32& carGenIdx);
    
    static void SaveAllCarGenerators(uint8* buffer, uint32* size);
    static void LoadAllCarGenerators(uint8* buffer, uint32 size);
    static int32 CreateCarGenerator(float x, float y, float z, float angle, int32 mi, int16 color1, int16 color2, uint8 force, uint8 alarm, uint8 lock, uint16 min_delay, uint16 max_delay);
} CarGenerators;
#endif // GTA3

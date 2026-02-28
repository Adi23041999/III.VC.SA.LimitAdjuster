/*
* Particle Object List Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"
#include "OLACommon.h"

#ifdef GTA3
class ParticleObjects : public SimpleAdjuster
{
public:
    static int32 NumParticleObjects;
    static std::vector<class CParticleObject> gPObjectArray;

    virtual const char* GetLimitName() override;
    virtual void ChangeLimit(int, const std::string& value) override;
} ParticleObjects;
#endif // GTA3

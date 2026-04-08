/*
* Pickups List Adjuster
* Copyright (c) 2026 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"
#include "OLACommon.h"

#ifdef GTA3
class Pickups : public SimpleAdjuster
{
public:
    static int32 NumGeneralPickups;
    static int32 NumPickups;
	static std::vector<class CPickup> aPickUps;

    virtual const char* GetLimitName();
    virtual void ChangeLimit(int, const std::string& value) override;
    static void Pickups_Update();
} Pickups;
#endif // GTA3

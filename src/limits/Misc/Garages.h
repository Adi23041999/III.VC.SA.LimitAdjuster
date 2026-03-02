/*
* Garage List Adjuster
* Copyright (c) 2026 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"
#include "OLACommon.h"

#ifdef GTA3
class Garages : public SimpleAdjuster
{
public:
    static std::vector<class CGarage> aGarages;

    virtual const char* GetLimitName();
    virtual void ChangeLimit(int, const std::string& value) override;
} Garages;
#endif // GTA3

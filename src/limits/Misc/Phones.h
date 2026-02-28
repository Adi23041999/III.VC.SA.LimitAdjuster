/*
* Phone List Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"
#include "OLACommon.h"

#ifdef GTA3
class Phones : public SimpleAdjuster
{
public:
    static int32 NumPhones;
    static std::vector<char> gPhoneInfoNew;

    virtual const char* GetLimitName();
    virtual void ChangeLimit(int, const std::string& value) override;
} Phones;
#endif // GTA3

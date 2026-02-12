/*
* 2dEffectsInfo Adjuster
* Copyright (c) 2014 ThirteenAG <thirteenag@gmail.com>
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "StoreAdjuster.hpp"
#include "utility/dummy_object.hpp"

typedef dummy_object<0x34, 0x50BE60, 0x50BE30> C2dEffectsInfo_III;
typedef dummy_object_vmt<0x34, 0x5600B0> C2dEffectsInfo_VC;

struct _2dEffectsInfoIII : public StoreAdjuster<C2dEffectsInfo_III, 0x9434F8, 2000>    // T, pDefaultStore, dwDefaultCapacity
{
    const char* GetLimitName()
    {
        return IsIII() ? "2dEffects" : nullptr;
    }

    _2dEffectsInfoIII()
    {
        this->SetGrower(0x47817A);
        this->AddPointer(0x50B37C);
        this->AddPointer(0x50B582);
        this->AddPointer(0x50B791);
        this->AddPointer(0x50B799);
        this->AddPointer(0x50B7B6);
        this->AddPointer(0x50B7BE);
        this->AddPointer(0x50BB31);
        if (GetLimitName()) injector::MakeNOP(0x478164, 5, true);
    }

} _2dEffectsInfoIII;

struct _2dEffectsInfoVC : public StoreAdjuster<C2dEffectsInfo_VC, 0x75EF10, 1210>    // T, pDefaultStore, dwDefaultCapacity
{
    const char* GetLimitName()
    {
        return IsVC() ? "2dEffects" : nullptr;
    }

    _2dEffectsInfoVC()
    {
        if (*(DWORD *)0x560034 != 1210) //exe modified by another adjuster
            return;

        this->SetGrower(0x48BAEE);
        this->SetGrower(0x53F22A);
        this->SetGrower(0x53F26A);
        this->AddPointer(0x55F571, 0x0);
        this->AddPointer(0x55F989, 0x0);
        this->AddPointer(0x55F991, 0x0);
        this->AddPointer(0x55F9A8, 0x0);
        this->AddPointer(0x55F9B0, 0x0);
        this->AddPointer(0x55FB38, 0x0);
        //this->AddPointer(0x560054, 0x0);
        //this->AddPointer(0x560067, 0x0);
    }

} _2dEffectsInfoVC;
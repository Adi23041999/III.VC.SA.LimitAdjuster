/*
* Simple Models Adjuster
* Copyright (c) 2025 Adi <adriank@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "StoreAdjuster.hpp"
#include "utility/dummy_object.hpp"

typedef dummy_object_vmt<0x4C, 0x50C150> CSimpleModelInfo_III;

struct SimpleModelInfoIII : public StoreAdjuster<CSimpleModelInfo_III, 0x885BB4, 5000>    // T, pDefaultStore, dwDefaultCapacity
{
    const char* GetLimitName()
    {
        return IsIII() ? "SimpleModels" : nullptr;
    }

    SimpleModelInfoIII()
    {
        this->SetGrower(0x477198);
        this->SetGrower(0x50B400);
        this->SetGrower(0x50B42F);
        this->SetGrower(0x50B45E);
        this->SetGrower(0x50B48D);
        this->SetGrower(0x50B4BC);
        this->SetGrower(0x50B4EB);
        this->SetGrower(0x50B51A);
        this->SetGrower(0x50B549);

        this->AddPointer(0x50B3DA, 0x0);
        this->AddPointer(0x50B5CD, 0x0);
        this->AddPointer(0x50B5D5, 0x0);
        this->AddPointer(0x50B5F2, 0x0);
        this->AddPointer(0x50B7C8, 0x0);
        this->AddPointer(0x50B922, 0x0);
        this->AddPointer(0x50B945, 0x0);
        this->AddPointer(0x50B94B, 0x0);
        this->AddPointer(0x50B954, 0x0);
        if (GetLimitName()) injector::MakeNOP(0x50B93C, 5, true);
    }

} SimpleModelInfoIII;

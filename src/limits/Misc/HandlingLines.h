/*
* Handling Lines List Adjuster
* Copyright (c) 2026 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"
#include "OLACommon.h"
#include "cHandlingDataMgr.h"
#include <string>

#ifdef GTA3

class cNewHandlingDataMgr : public cHandlingDataMgr {
public:
	int32 GetHandlingId(const char* name);
	int32 FindExactWord(const char* word, const char* words, int wordLen, int numWords);
};



class HandlingLines : public SimpleAdjuster
{
public:
	static int32 NumHandlingLines;
	static std::vector<char> HandlingManager;
	static std::vector<std::string> VehicleNames;

    virtual const char* GetLimitName();
    virtual void ChangeLimit(int, const std::string& value) override;
	static void AddDefaultVehicleNames();
	static void CopyAircraftHandlingData();

} HandlingLines;
#endif // GTA3

/*
* Boat Bounds Limit Adjuster
* Copyright (c) 2026 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "LimitAdjuster.h"
#include "OLACommon.h"

using namespace injector;

#ifdef GTA3
class BoatBounds : public SimpleAdjuster
{
public:
	static float BoundsP;
	static float BoundsN;

	virtual const char* GetLimitName() override { return "BoatBounds"; }
	virtual void ChangeLimit(int, const std::string& value) override
	{
		BoundsP = std::stof(value);
		BoundsN = -BoundsP;

		WriteMemory(0x540BB7 + 2, &BoatBounds::BoundsP, true);
		WriteMemory(0x540BF0 + 2, &BoatBounds::BoundsN, true);
		WriteMemory(0x540C21 + 2, &BoatBounds::BoundsP, true);
		WriteMemory(0x540C51 + 2, &BoatBounds::BoundsN, true);
	}
} BoatBounds;
#endif // GTA3

float BoatBounds::BoundsP = 1900.0f;
float BoatBounds::BoundsN = -1900.0f;

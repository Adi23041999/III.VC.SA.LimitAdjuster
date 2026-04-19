/*
* Flying Height Limit Adjuster
* Copyright (c) 2026 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "LimitAdjuster.h"
#include "OLACommon.h"

using namespace injector;

#ifdef GTA3
class FlyingHeight : public SimpleAdjuster
{
public:
	static float HeightLimit;

	virtual const char* GetLimitName() override { return "FlyingHeight"; }
	virtual void ChangeLimit(int, const std::string& value) override
	{
		HeightLimit = std::stof(value);
		const float* Og = ReadMemory<float*>(0x553016 + 2, true);
		if (NearlyEqual(*Og, 100.0f))
		{
			WriteMemory(0x553016 + 2, &FlyingHeight::HeightLimit, true);
		}
	}
} FlyingHeight;

float FlyingHeight::HeightLimit = 0.0f;
#endif // GTA3


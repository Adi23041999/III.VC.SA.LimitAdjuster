/*
* Cars In Use Limit Adjuster
* Copyright (c) 2026 Adi
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "LimitAdjuster.h"

using namespace injector;
float NumDefaultCars = 12.0f;

#ifdef GTA3
class CarsInUse : public SimpleAdjuster
{
public:
	virtual const char* GetLimitName() override { return "CarsInUse"; }
	virtual void ChangeLimit(int, const std::string& value) override
	{
		NumDefaultCars = std::stof(value);
		injector::WriteMemory<float*>(0x59BF68 + 2, &NumDefaultCars, true);
	}
} CarsInUse;
#endif // GTA3

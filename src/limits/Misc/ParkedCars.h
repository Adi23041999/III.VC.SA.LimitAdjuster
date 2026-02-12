/*
* Parked Cars Limit Adjuster
* Copyright (c) 2026 5d0
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "LimitAdjuster.h"

using namespace injector;

#ifdef GTA3
class ParkedCars : public SimpleAdjuster
{
public:
	virtual const char* GetLimitName() override { "ParkedCars"; }
	virtual void ChangeLimit(int, const std::string& value) override
	{
		int n = std::stoi(value);
		injector::WriteMemory<uint8_t>(0x542706, n, true);
	}

} ParkedCars;
#endif // GTA3

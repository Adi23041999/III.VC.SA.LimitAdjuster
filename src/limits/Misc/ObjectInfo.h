/*
* Object Info Limit Adjuster
* Copyright (c) 2026 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "LimitAdjuster.h"

#ifdef GTA3
class ObjectInfo : public SimpleAdjuster
{
public:
	virtual const char* GetLimitName() override { return "ObjectInfo"; }
	virtual void ChangeLimit(int, const std::string& value) override;
} ObjectInfo;
#endif // GTA3

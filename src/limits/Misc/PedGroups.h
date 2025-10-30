/*
* Ped Groups Limit Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "LimitAdjuster.h"

#ifdef GTA3
class PedGroup : public Adjuster
{
public:
    enum
    {
        PedGroups,
        PedGroupModels,
    };

    virtual const Limit* GetLimits() override;
    virtual void ChangeLimit(int id, const std::string& value) override;
    virtual void Process() override;

    static int ChooseCivilianOccupation(int group);
    static void LoadPedGroups();
} PedGroup;
#endif // GTA3

/*
* Adjuster for work buffer and save files
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"

using namespace injector;

std::vector<char> work_buff;

class GameStorageIII : public SimpleAdjuster
{
public:
    const char* GetLimitName()
    {
        return IsIII() ? "GameStorage" : nullptr;
    }

    void ChangeLimit(int, const std::string& value)
    {
        int multiplier = std::stoi(value);
		if (multiplier <= 1)
            return;

        size_t work_buff_t = 55000 * multiplier;
        int SIZE_OF_ONE_GAME_IN_BYTES = 0x31401 * multiplier;
		work_buff.resize(work_buff_t);
        std::fill(work_buff.begin(), work_buff.end(), 0);

        // work_buff (used to store read data)
        WriteMemory(0x478B60, &work_buff[0] + 0x18, true);
        WriteMemory(0x478B6A, &work_buff[0] + 0x0, true);
        WriteMemory(0x478B79, &work_buff[0] + 0x0, true);
        WriteMemory(0x4AB917, &work_buff[0] + 0x0, true);
        WriteMemory(0x4AB925, &work_buff[0] + 0x0, true);
        WriteMemory(0x4ABB0B, &work_buff[0] + 0x0, true);
        WriteMemory(0x4ABB43, &work_buff[0] + 0x0, true);
        WriteMemory(0x4ABB4D, &work_buff[0] + 0x0, true);
        WriteMemory(0x4ABB58, &work_buff[0] + 0x0, true);
        WriteMemory(0x4ABB67, &work_buff[0] + 0x0, true);
        WriteMemory(0x4BC107, &work_buff[0] + 0x0, true);
        WriteMemory(0x4BC119, &work_buff[0] + 0x0, true);
        WriteMemory(0x4E9887, &work_buff[0] + 0x0, true);
        WriteMemory(0x4E98B2, &work_buff[0] + 0x0, true);
        WriteMemory(0x4E98BE, &work_buff[0] + 0x0, true);
        WriteMemory(0x50FE19, &work_buff[0] + 0x0, true);
        WriteMemory(0x50FE34, &work_buff[0] + 0x0, true);
        WriteMemory(0x546DD9, &work_buff[0] + 0x0, true);
        WriteMemory(0x546DF4, &work_buff[0] + 0x0, true);
        WriteMemory(0x54BD66, &work_buff[0] + 0x0, true);
        WriteMemory(0x54BD8A, &work_buff[0] + 0x0, true);
        WriteMemory(0x54BD98, &work_buff[0] + 0x0, true);
        WriteMemory(0x54BDE6, &work_buff[0] + 0x0, true);
        WriteMemory(0x54BDF4, &work_buff[0] + 0x0, true);
        WriteMemory(0x54EAF4, &work_buff[0] + 0x0, true);
        WriteMemory(0x54EB12, &work_buff[0] + 0x0, true);
        WriteMemory(0x54EB20, &work_buff[0] + 0x0, true);
        WriteMemory(0x54EB66, &work_buff[0] + 0x0, true);
        WriteMemory(0x54EB74, &work_buff[0] + 0x0, true);
        WriteMemory(0x565002, &work_buff[0] + 0x0, true);
        WriteMemory(0x56504A, &work_buff[0] + 0x0, true);
        WriteMemory(0x565056, &work_buff[0] + 0x0, true);
        WriteMemory(0x58F8FA, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FC0C, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FC17, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FC48, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FC4D, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FCB5, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FCC0, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FCEE, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FCF3, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FD5B, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FD66, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FD98, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FD9D, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FE05, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FE10, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FE3E, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FE43, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FEAB, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FEB6, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FEE8, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FEED, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FF64, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FF6F, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FF9D, &work_buff[0] + 0x0, true);
        WriteMemory(0x58FFA2, &work_buff[0] + 0x0, true);
        WriteMemory(0x59000A, &work_buff[0] + 0x0, true);
        WriteMemory(0x590015, &work_buff[0] + 0x0, true);
        WriteMemory(0x590048, &work_buff[0] + 0x0, true);
        WriteMemory(0x59004D, &work_buff[0] + 0x0, true);
        WriteMemory(0x5900B5, &work_buff[0] + 0x0, true);
        WriteMemory(0x5900C0, &work_buff[0] + 0x0, true);
        WriteMemory(0x5900EE, &work_buff[0] + 0x0, true);
        WriteMemory(0x5900F3, &work_buff[0] + 0x0, true);
        WriteMemory(0x59015E, &work_buff[0] + 0x0, true);
        WriteMemory(0x590169, &work_buff[0] + 0x0, true);
        WriteMemory(0x590198, &work_buff[0] + 0x0, true);
        WriteMemory(0x59019D, &work_buff[0] + 0x0, true);
        WriteMemory(0x590205, &work_buff[0] + 0x0, true);
        WriteMemory(0x590210, &work_buff[0] + 0x0, true);
        WriteMemory(0x59023E, &work_buff[0] + 0x0, true);
        WriteMemory(0x590243, &work_buff[0] + 0x0, true);
        WriteMemory(0x5902AB, &work_buff[0] + 0x0, true);
        WriteMemory(0x5902B6, &work_buff[0] + 0x0, true);
        WriteMemory(0x5902E8, &work_buff[0] + 0x0, true);
        WriteMemory(0x5902ED, &work_buff[0] + 0x0, true);
        WriteMemory(0x590355, &work_buff[0] + 0x0, true);
        WriteMemory(0x590360, &work_buff[0] + 0x0, true);
        WriteMemory(0x59038E, &work_buff[0] + 0x0, true);
        WriteMemory(0x590393, &work_buff[0] + 0x0, true);
        WriteMemory(0x5903FB, &work_buff[0] + 0x0, true);
        WriteMemory(0x590406, &work_buff[0] + 0x0, true);
        WriteMemory(0x590438, &work_buff[0] + 0x0, true);
        WriteMemory(0x59043D, &work_buff[0] + 0x0, true);
        WriteMemory(0x5904A5, &work_buff[0] + 0x0, true);
        WriteMemory(0x5904B0, &work_buff[0] + 0x0, true);
        WriteMemory(0x5904DE, &work_buff[0] + 0x0, true);
        WriteMemory(0x5904E3, &work_buff[0] + 0x0, true);
        WriteMemory(0x59054B, &work_buff[0] + 0x0, true);
        WriteMemory(0x590556, &work_buff[0] + 0x0, true);
        WriteMemory(0x590588, &work_buff[0] + 0x0, true);
        WriteMemory(0x59058D, &work_buff[0] + 0x0, true);
        WriteMemory(0x5905F5, &work_buff[0] + 0x0, true);
        WriteMemory(0x590600, &work_buff[0] + 0x0, true);
        WriteMemory(0x59062E, &work_buff[0] + 0x0, true);
        WriteMemory(0x590633, &work_buff[0] + 0x0, true);
        WriteMemory(0x5906AC, &work_buff[0] + 0x0, true);
        WriteMemory(0x5906B7, &work_buff[0] + 0x0, true);
        WriteMemory(0x5906E8, &work_buff[0] + 0x0, true);
        WriteMemory(0x5906ED, &work_buff[0] + 0x0, true);
        WriteMemory(0x590761, &work_buff[0] + 0x0, true);
        WriteMemory(0x59076C, &work_buff[0] + 0x0, true);
        WriteMemory(0x59079A, &work_buff[0] + 0x0, true);
        WriteMemory(0x59079F, &work_buff[0] + 0x0, true);
        WriteMemory(0x590807, &work_buff[0] + 0x0, true);
        WriteMemory(0x590812, &work_buff[0] + 0x0, true);
        WriteMemory(0x590840, &work_buff[0] + 0x0, true);
        WriteMemory(0x590845, &work_buff[0] + 0x0, true);
        WriteMemory(0x5908AD, &work_buff[0] + 0x0, true);
        WriteMemory(0x5908B8, &work_buff[0] + 0x0, true);
        WriteMemory(0x5908E8, &work_buff[0] + 0x0, true);
        WriteMemory(0x5908ED, &work_buff[0] + 0x0, true);
        WriteMemory(0x590931, &work_buff[0] + 0x0, true);
        WriteMemory(0x590B16, &work_buff[0] + 0x0, true);
        WriteMemory(0x590B2C, &work_buff[0] + 0x0, true);
        WriteMemory(0x590E02, &work_buff[0] + 0x0, true);
        WriteMemory(0x590E25, &work_buff[0] + 0x0, true);
        WriteMemory(0x590E91, &work_buff[0] + 0x0, true);
        WriteMemory(0x590EB4, &work_buff[0] + 0x0, true);
        WriteMemory(0x590F20, &work_buff[0] + 0x0, true);
        WriteMemory(0x590F43, &work_buff[0] + 0x0, true);
        WriteMemory(0x590FAF, &work_buff[0] + 0x0, true);
        WriteMemory(0x590FD2, &work_buff[0] + 0x0, true);
        WriteMemory(0x591048, &work_buff[0] + 0x0, true);
        WriteMemory(0x59106B, &work_buff[0] + 0x0, true);
        WriteMemory(0x5910E5, &work_buff[0] + 0x0, true);
        WriteMemory(0x591108, &work_buff[0] + 0x0, true);
        WriteMemory(0x591169, &work_buff[0] + 0x0, true);
        WriteMemory(0x59118C, &work_buff[0] + 0x0, true);
        WriteMemory(0x5911F8, &work_buff[0] + 0x0, true);
        WriteMemory(0x59121B, &work_buff[0] + 0x0, true);
        WriteMemory(0x59128A, &work_buff[0] + 0x0, true);
        WriteMemory(0x5912AD, &work_buff[0] + 0x0, true);
        WriteMemory(0x591319, &work_buff[0] + 0x0, true);
        WriteMemory(0x59133C, &work_buff[0] + 0x0, true);
        WriteMemory(0x5913A8, &work_buff[0] + 0x0, true);
        WriteMemory(0x5913CB, &work_buff[0] + 0x0, true);
        WriteMemory(0x591437, &work_buff[0] + 0x0, true);
        WriteMemory(0x59145A, &work_buff[0] + 0x0, true);
        WriteMemory(0x5914C6, &work_buff[0] + 0x0, true);
        WriteMemory(0x5914E9, &work_buff[0] + 0x0, true);
        WriteMemory(0x59155A, &work_buff[0] + 0x0, true);
        WriteMemory(0x59157D, &work_buff[0] + 0x0, true);
        WriteMemory(0x5915E9, &work_buff[0] + 0x0, true);
        WriteMemory(0x59160C, &work_buff[0] + 0x0, true);
        WriteMemory(0x591678, &work_buff[0] + 0x0, true);
        WriteMemory(0x59169B, &work_buff[0] + 0x0, true);
        WriteMemory(0x591718, &work_buff[0] + 0x0, true);
        WriteMemory(0x59173B, &work_buff[0] + 0x0, true);
        WriteMemory(0x5917A7, &work_buff[0] + 0x0, true);
        WriteMemory(0x5917CA, &work_buff[0] + 0x0, true);
        WriteMemory(0x591836, &work_buff[0] + 0x0, true);
        WriteMemory(0x591859, &work_buff[0] + 0x0, true);
        WriteMemory(0x591C46, &work_buff[0] + 0x0, true);
        WriteMemory(0x591C89, &work_buff[0] + 0x0, true);
        WriteMemory(0x591CBA, &work_buff[0] + 0x0, true);
        WriteMemory(0x591CCB, &work_buff[0] + 0x0, true);

        WriteMemory(0x4AB912, work_buff_t, true);
        WriteMemory(0x4ABB06, work_buff_t, true);
        WriteMemory(0x4BC102, work_buff_t, true);
        WriteMemory(0x4E9882, work_buff_t, true);
        WriteMemory(0x50FE14, work_buff_t, true);
        WriteMemory(0x546DD4, work_buff_t, true);
        WriteMemory(0x54BD61, work_buff_t, true);
        WriteMemory(0x54EAEF, work_buff_t, true);
        WriteMemory(0x564FFD, work_buff_t, true);
        WriteMemory(0x59091A, work_buff_t, true);
        WriteMemory(0x590921, work_buff_t, true);
        WriteMemory(0x591C21, work_buff_t, true);
        WriteMemory(0x591C35, work_buff_t - 4, true);

        // save file size
        WriteMemory(0x590909, SIZE_OF_ONE_GAME_IN_BYTES - 4, true);
        WriteMemory(0x591CD2, SIZE_OF_ONE_GAME_IN_BYTES, true);
        WriteMemory(0x611570, SIZE_OF_ONE_GAME_IN_BYTES, true);
       
    };
} GameStorageIII;

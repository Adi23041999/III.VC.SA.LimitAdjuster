/*
* Car Generators Limit Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "LimitAdjuster.h"

using namespace injector;

int numCarGenerators;
std::vector<char> carGeneratorArray;

DWORD ext_5431DD = 0x5431DD;
DWORD ext_5430C4 = 0x5430C4;
void __declspec(naked) SaveAllCarGeneratorsHook()
{
    __asm
    {
		cmp eax, numCarGenerators
        fstp dword ptr [ebx]
        jb loc_5430C4
        jmp ext_5431DD
	loc_5430C4:
		jmp ext_5430C4
    }
}

DWORD ext_543326 = 0x543326;
DWORD ext_543215 = 0x543215;
void __declspec(naked) LoadAllCarGeneratorsHook()
{
    __asm
    {
        cmp eax, numCarGenerators
        jb loc_543215
        jmp ext_543326
    loc_543215:
        jmp ext_543215
    }
}

class ZoneLimits : public SimpleAdjuster
{
public:

    const char* GetLimitName()
    {
        return IsIII() ? "CarGenerators" : nullptr;
    }

    void ChangeLimit(int id, const std::string& value)
    {
		numCarGenerators = std::stoi(value);
		carGeneratorArray.resize(0x48 * numCarGenerators);

		WriteMemory(0x43F0F2, &carGeneratorArray[0] + 0x0, true);
        WriteMemory(0x542F83, &carGeneratorArray[0] + 0x0, true);
        WriteMemory(0x543003, &carGeneratorArray[0] + 0x0, true);
        WriteMemory(0x5430C6, &carGeneratorArray[0] + 0x0, true);
        WriteMemory(0x5430D2, &carGeneratorArray[0] + 0x4, true);
        WriteMemory(0x5430DA, &carGeneratorArray[0] + 0x4 + 0x4, true);
        WriteMemory(0x5430E5, &carGeneratorArray[0] + 0x4 + 0x8, true);
        WriteMemory(0x5430F0, &carGeneratorArray[0] + 0x10, true);
        WriteMemory(0x5430FC, &carGeneratorArray[0] + 0x14, true);
        WriteMemory(0x54310C, &carGeneratorArray[0] + 0x16, true);
        WriteMemory(0x543115, &carGeneratorArray[0] + 0x18, true);
        WriteMemory(0x54311E, &carGeneratorArray[0] + 0x19, true);
        WriteMemory(0x543127, &carGeneratorArray[0] + 0x1A, true);
        WriteMemory(0x543135, &carGeneratorArray[0] + 0x1C, true);
        WriteMemory(0x543145, &carGeneratorArray[0] + 0x1E, true);
        WriteMemory(0x543151, &carGeneratorArray[0] + 0x20, true);
        WriteMemory(0x54315C, &carGeneratorArray[0] + 0x24, true);
        WriteMemory(0x543168, &carGeneratorArray[0] + 0x28, true);
        WriteMemory(0x543171, &carGeneratorArray[0] + 0x2A, true);
        WriteMemory(0x54317E, &carGeneratorArray[0] + 0x2C, true);
        WriteMemory(0x543189, &carGeneratorArray[0] + 0x2C + 0x4, true);
        WriteMemory(0x543195, &carGeneratorArray[0] + 0x2C + 0x8, true);
        WriteMemory(0x5431A1, &carGeneratorArray[0] + 0x38, true);
        WriteMemory(0x5431AC, &carGeneratorArray[0] + 0x38 + 0x4, true);
        WriteMemory(0x5431B8, &carGeneratorArray[0] + 0x38 + 0x8, true);
        WriteMemory(0x5431C4, &carGeneratorArray[0] + 0x44, true);
        WriteMemory(0x54321A, &carGeneratorArray[0] + 0x0, true);
        WriteMemory(0x543225, &carGeneratorArray[0] + 0x4, true);
        WriteMemory(0x543230, &carGeneratorArray[0] + 0x4 + 0x4, true);
        WriteMemory(0x54323B, &carGeneratorArray[0] + 0x4 + 0x8, true);
        WriteMemory(0x543246, &carGeneratorArray[0] + 0x10, true);
        WriteMemory(0x543253, &carGeneratorArray[0] + 0x14, true);
        WriteMemory(0x543260, &carGeneratorArray[0] + 0x16, true);
        WriteMemory(0x543269, &carGeneratorArray[0] + 0x18, true);
        WriteMemory(0x543272, &carGeneratorArray[0] + 0x19, true);
        WriteMemory(0x54327B, &carGeneratorArray[0] + 0x1A, true);
        WriteMemory(0x543288, &carGeneratorArray[0] + 0x1C, true);
        WriteMemory(0x543295, &carGeneratorArray[0] + 0x1E, true);
        WriteMemory(0x5432A0, &carGeneratorArray[0] + 0x20, true);
        WriteMemory(0x5432AB, &carGeneratorArray[0] + 0x24, true);
        WriteMemory(0x5432B8, &carGeneratorArray[0] + 0x28, true);
        WriteMemory(0x5432C1, &carGeneratorArray[0] + 0x2A, true);
        WriteMemory(0x5432CC, &carGeneratorArray[0] + 0x2C, true);
        WriteMemory(0x5432D8, &carGeneratorArray[0] + 0x2C + 0x4, true);
        WriteMemory(0x5432E4, &carGeneratorArray[0] + 0x2C + 0x8, true);
        WriteMemory(0x5432EF, &carGeneratorArray[0] + 0x38, true);
        WriteMemory(0x5432FB, &carGeneratorArray[0] + 0x38 + 0x4, true);
        WriteMemory(0x543307, &carGeneratorArray[0] + 0x38 + 0x8, true);
        WriteMemory(0x543315, &carGeneratorArray[0] + 0x44, true);

        MakeJMP(0x5431D1, SaveAllCarGeneratorsHook);
        MakeJMP(0x54331C, LoadAllCarGeneratorsHook);

		int newCarGenSize = 0x48 * numCarGenerators;
        int saveSize = 0x2D1C;
        saveSize -= 0x48 * 160;
		saveSize += newCarGenSize;
        WriteMemory(0x54305C, saveSize, true);
        WriteMemory(0x5430BE, newCarGenSize, true);
    }
} CarGenerators;

/*
* Phone List Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"

using namespace injector;

int numPhones;
std::vector<char> gPhoneInfo;

DWORD _phoneTemp;
DWORD ext_430110 = 0x430110;
DWORD ext_430097 = 0x430097;
void __declspec(naked) SaveHook()
{
    __asm
    {
        inc dword ptr[esp + 4]
        add ebx, 0x34
        add ebp, 0x34
        mov _phoneTemp, eax
        mov eax, numPhones
        cmp dword ptr[esp + 4], eax
        mov eax, _phoneTemp
        jl loc_430097
        jmp ext_430110
    loc_430097:
        jmp ext_430097
    }
}

DWORD ext_4301D1 = 0x4301D1;
DWORD ext_430147 = 0x430147;
void __declspec(naked) LoadHook()
{
    __asm
    {
        inc dword ptr[esp + 4]
        add eax, 0x34
        mov _phoneTemp, eax
        mov eax, numPhones
        cmp dword ptr [esp+4], eax
        mov eax, _phoneTemp
        jl loc_430147
        jmp ext_4301D1
    loc_430147:
        jmp ext_430147
    }
}

class PhonesIII : public SimpleAdjuster
{
public:
    const char* GetLimitName()
    {
        return IsIII() ? "Phones" : nullptr;
    }

    void ChangeLimit(int, const std::string& value)
    {        
        numPhones = std::stoi(value); 
        size_t gPhoneInfo_t = 0x8 + (numPhones * 0x34);
        gPhoneInfo.resize(gPhoneInfo_t);
        std::fill(gPhoneInfo.begin(), gPhoneInfo.end(), 0U);
        
        WriteMemory(0x42F743, &gPhoneInfo[0] + 0x8 + 0x2C, true);
        WriteMemory(0x444674, &gPhoneInfo[0], true);
        WriteMemory(0x4446E8, &gPhoneInfo[0], true);
        WriteMemory(0x44474F, &gPhoneInfo[0], true);
        WriteMemory(0x44478A, &gPhoneInfo[0], true);
        WriteMemory(0x4447C5, &gPhoneInfo[0], true);
        WriteMemory(0x44C386, &gPhoneInfo[0], true);
        WriteMemory(0x44C442, &gPhoneInfo[0], true);
        WriteMemory(0x44C539, &gPhoneInfo[0], true);
        WriteMemory(0x44C62F, &gPhoneInfo[0], true);
        WriteMemory(0x44C760, &gPhoneInfo[0], true);
        WriteMemory(0x44C890, &gPhoneInfo[0], true);
        WriteMemory(0x44CD4A, &gPhoneInfo[0], true);
        WriteMemory(0x44CE9D, &gPhoneInfo[0], true);
        WriteMemory(0x44D02F, &gPhoneInfo[0], true);
        WriteMemory(0x44D1BB, &gPhoneInfo[0], true);
        WriteMemory(0x44EBCA, &gPhoneInfo[0], true);
        WriteMemory(0x48C249, &gPhoneInfo[0], true);
        WriteMemory(0x48C3C3, &gPhoneInfo[0], true);
        WriteMemory(0x48C56C, &gPhoneInfo[0], true);
        WriteMemory(0x48C9E7, &gPhoneInfo[0], true);
        WriteMemory(0x4C04DB, &gPhoneInfo[0] + 0x8 + 0x2C, true);
        WriteMemory(0x4C04E4, &gPhoneInfo[0] + 0x8 + 0x2C, true);
        WriteMemory(0x4C10D9, &gPhoneInfo[0], true);
        WriteMemory(0x4C1109, &gPhoneInfo[0] + 0x8 + 0x2C, true);
        WriteMemory(0x4C112A, &gPhoneInfo[0] + 0x8 + 0x8, true);
        WriteMemory(0x4C1130, &gPhoneInfo[0] + 0x8 + 0x4, true);
        WriteMemory(0x4C1136, &gPhoneInfo[0] + 0x8, true);
        WriteMemory(0x4D0504, &gPhoneInfo[0], true);
        WriteMemory(0x4D3CF0, &gPhoneInfo[0] + 0x8 + 0x4, true);
        WriteMemory(0x4D3CF6, &gPhoneInfo[0] + 0x8, true);
        WriteMemory(0x4D3E4E, &gPhoneInfo[0] + 0x8 + 0x2C, true);
        WriteMemory(0x588A8D, &gPhoneInfo[0] + 0x8 + 0x2C, true);
        WriteMemory(0x590127, &gPhoneInfo[0], true);
        WriteMemory(0x591246, &gPhoneInfo[0], true);

        WriteMemory(0x430074, gPhoneInfo_t, true);
        MakeJMP(0x4300FF, SaveHook);
        MakeJMP(0x4301BF, LoadHook);
    };
} PhonesIII;

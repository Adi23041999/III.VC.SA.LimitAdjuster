/*
* Phone List Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"

using namespace injector;

int numPhones;

DWORD _phoneTemp;
DWORD ext_4301D1 = 0x4301D1;
DWORD ext_430147 = 0x430147;
void __declspec(naked) patch_4301C6()
{
    __asm
    {
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

DWORD ext_430110 = 0x430110;
DWORD ext_430097 = 0x430097;
void __declspec(naked) patch_430109()
{
    __asm
    {
        mov _phoneTemp, eax
        mov eax, numPhones
        cmp dword ptr [esp+4], eax
        mov eax, _phoneTemp
        jl loc_430097
        jmp ext_430110
loc_430097:
        jmp ext_430097
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
        char* gPhoneInfo = new char[0x8 + (numPhones * 0x34)];
        
        WriteMemory(0x42F743, gPhoneInfo + 0x8 + 0x2C, true);
        WriteMemory(0x444674, gPhoneInfo, true);
        WriteMemory(0x4446E8, gPhoneInfo, true);
        WriteMemory(0x44474F, gPhoneInfo, true);
        WriteMemory(0x44478A, gPhoneInfo, true);
        WriteMemory(0x4447C5, gPhoneInfo, true);
        WriteMemory(0x44C386, gPhoneInfo, true);
        WriteMemory(0x44C442, gPhoneInfo, true);
        WriteMemory(0x44C539, gPhoneInfo, true);
        WriteMemory(0x44C62F, gPhoneInfo, true);
        WriteMemory(0x44C760, gPhoneInfo, true);
        WriteMemory(0x44C890, gPhoneInfo, true);
        WriteMemory(0x44CD4A, gPhoneInfo, true);
        WriteMemory(0x44CE9D, gPhoneInfo, true);
        WriteMemory(0x44D02F, gPhoneInfo, true);
        WriteMemory(0x44D1BB, gPhoneInfo, true);
        WriteMemory(0x44EBCA, gPhoneInfo, true);
        WriteMemory(0x48C249, gPhoneInfo, true);
        WriteMemory(0x48C3C3, gPhoneInfo, true);
        WriteMemory(0x48C56C, gPhoneInfo, true);
        WriteMemory(0x48C9E7, gPhoneInfo, true);
        WriteMemory(0x4C04DB, gPhoneInfo + 0x8 + 0x2C, true);
        WriteMemory(0x4C04E4, gPhoneInfo + 0x8 + 0x2C, true);
        WriteMemory(0x4C10D9, gPhoneInfo, true);
        WriteMemory(0x4C1109, gPhoneInfo + 0x8 + 0x2C, true);
        WriteMemory(0x4C112A, gPhoneInfo + 0x8 + 0x8, true);
        WriteMemory(0x4C1130, gPhoneInfo + 0x8 + 0x4, true);
        WriteMemory(0x4C1136, gPhoneInfo + 0x8, true);
        WriteMemory(0x4D0504, gPhoneInfo, true);
        WriteMemory(0x4D3CF0, gPhoneInfo + 0x8 + 0x8, true);
        WriteMemory(0x4D3CF6, gPhoneInfo + 0x8, true);
        WriteMemory(0x4D3E4E, gPhoneInfo + 0x8 + 0x2C, true);
        WriteMemory(0x588A8D, gPhoneInfo + 0x8 + 0x2C, true);
        WriteMemory(0x590127, gPhoneInfo, true);
        WriteMemory(0x591246, gPhoneInfo, true);

        MakeJMP(0x4301C6, patch_4301C6);
        MakeJMP(0x430109, patch_430109);
    };
} PhonesIII;

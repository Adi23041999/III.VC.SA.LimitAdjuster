/*
* Particle Info List Adjuster
* Copyright (c) 2025 Adi <adriank@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"
#include "utility/StaticArrayAdjuster.hpp"
#include "utility/dummy_object.hpp"
#include "CPatch.h"

using namespace injector;

int ParticleObjectNum;
int ParticleObjectLastIndex;
std::vector<char> PObjectArray;


DWORD ext_4BC48B = 0x4BC48B;
DWORD ext_4BC497 = 0x4BC497;
void __declspec(naked) patch_4BC486()
{
    __asm
    {
        cmp ecx, ParticleObjectLastIndex
        jnz loc_4BC497
        jmp ext_4BC48B
loc_4BC497:
        jmp ext_4BC497
    }
}

DWORD ext_4BC462 = 0x4BC462;
void __declspec(naked) patch_4BC4BB()
{
    __asm
    {
        cmp ecx, ParticleObjectNum
        jl loc_4BC462
        retn
loc_4BC462:
        jmp ext_4BC462
    }
}

DWORD ext_4BFCCB = 0x4BFCCB;
DWORD ext_4BFCD7 = 0x4BFCD7;
void __declspec(naked) patch_4BFCC6()
{
    __asm
    {
        cmp ecx, ParticleObjectLastIndex
        jnz loc_4BFCD7
        jmp ext_4BFCCB
loc_4BFCD7:
        jmp ext_4BFCD7
    }
}

DWORD ext_4BFCA2 = 0x4BFCA2;
void __declspec(naked) patch_4BFCFB()
{
    __asm
    {
        cmp ecx, ParticleObjectNum
        jl loc_4BFCA2
        retn
loc_4BFCA2:
        jmp ext_4BFCA2
    }
}

class ParticleObjectsIII : public SimpleAdjuster
{
public:
    const char* GetLimitName()
    {
        return IsIII() ? "ParticleObjects" : nullptr;
    }

    void ChangeLimit(int, const std::string& value)
    {
        ParticleObjectNum = std::stoi(value);
        ParticleObjectLastIndex = ParticleObjectNum - 1;
        PObjectArray.resize(ParticleObjectNum * 0x88);

        // init loop
        CPatch::RedirectJump(0x4BC486, patch_4BC486);
        CPatch::RedirectJump(0x4BC4BB, patch_4BC4BB);

        // deinit loop
        CPatch::RedirectJump(0x4BFCC6, patch_4BFCC6);
        CPatch::RedirectJump(0x4BFCFB, patch_4BFCFB);

        WriteMemory(0x4BC45E, &PObjectArray[0] + 0x0, true);
        WriteMemory(0x4BC482, &PObjectArray[0] + 0x50, true);
        WriteMemory(0x4BC47C, &PObjectArray[0] + 0x0, true);
        WriteMemory(0x4BC468, &PObjectArray[0] + 0x50, true);
        WriteMemory(0x4BC48D, &PObjectArray[0] + 0x4C, true);
        WriteMemory(0x4BC4A7, &PObjectArray[0] + 0x4C, true);
        WriteMemory(0x4BC4A1, &PObjectArray[0] + 0x0, true);
        WriteMemory(0x4BC4AF, &PObjectArray[0] + 0x68, true);

        WriteMemory(0x4BFC88, &PObjectArray[0] + 0x0, true);
        WriteMemory(0x4BFCC2, &PObjectArray[0] + 0x50, true);
        WriteMemory(0x4BFCBC, &PObjectArray[0] + 0x0, true);
        WriteMemory(0x4BFCA8, &PObjectArray[0] + 0x50, true);
        WriteMemory(0x4BFCCD, &PObjectArray[0] + 0x4C, true);
        WriteMemory(0x4BFCE7, &PObjectArray[0] + 0x4C, true);
        WriteMemory(0x4BFCE1, &PObjectArray[0] + 0x0, true);
        WriteMemory(0x4BFCEF, &PObjectArray[0] + 0x68, true);

        //this->AddPointer(0x4BFDC2, 0x0);
        //this->AddPointer(0x4BFE1D, 0x0);
    };
} ParticleObjectsIII;

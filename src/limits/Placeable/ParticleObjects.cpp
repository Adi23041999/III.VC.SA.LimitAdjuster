/*
* Particle Object List Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"

using namespace injector;

int numParticleObjects;
int particleObjectLastIndex;
std::vector<char> gPObjectArray;

DWORD ext_4BC48B = 0x4BC48B;
DWORD ext_4BC497 = 0x4BC497;
void __declspec(naked) InitializeHook1()
{
    __asm
    {
        cmp ecx, particleObjectLastIndex
        jnz loc_4BC497
        jmp ext_4BC48B
    loc_4BC497:
        jmp ext_4BC497
    }
}

DWORD ext_4BC462 = 0x4BC462;
void __declspec(naked) InitializeHook2()
{
    __asm
    {
        add edx, 0x88
        cmp ecx, numParticleObjects
        jl loc_4BC462
        retn
    loc_4BC462:
        jmp ext_4BC462
    }
}

DWORD ext_4BFCCB = 0x4BFCCB;
DWORD ext_4BFCD7 = 0x4BFCD7;
void __declspec(naked) RemoveAllParticleObjectsHook1()
{
    __asm
    {
        cmp ecx, particleObjectLastIndex
        jnz loc_4BFCD7
        jmp ext_4BFCCB
    loc_4BFCD7:
        jmp ext_4BFCD7
    }
}

DWORD ext_4BFCA2 = 0x4BFCA2;
void __declspec(naked) RemoveAllParticleObjectsHook2()
{
    __asm
    {
        add edx, 0x88
        cmp ecx, numParticleObjects
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
        numParticleObjects = std::stoi(value);
        particleObjectLastIndex = numParticleObjects - 1;
        gPObjectArray.resize(0x88 * numParticleObjects);
        
        WriteMemory(0x4BC45E, &gPObjectArray[0] + 0x0, true);
        WriteMemory(0x4BC468, &gPObjectArray[0] + 0x50, true);
        WriteMemory(0x4BC47C, &gPObjectArray[0] + 0x0, true);
        WriteMemory(0x4BC482, &gPObjectArray[0] + 0x50, true);
        WriteMemory(0x4BC48D, &gPObjectArray[0] + 0x4C, true);
        WriteMemory(0x4BC4A1, &gPObjectArray[0] + 0x0, true);
        WriteMemory(0x4BC4A7, &gPObjectArray[0] + 0x4C, true);
        WriteMemory(0x4BC4AF, &gPObjectArray[0] + 0x68, true);

        WriteMemory(0x4BFC88, &gPObjectArray[0] + 0x0, true);
        WriteMemory(0x4BFCA8, &gPObjectArray[0] + 0x50, true);
        WriteMemory(0x4BFCBC, &gPObjectArray[0] + 0x0, true);
        WriteMemory(0x4BFCC2, &gPObjectArray[0] + 0x50, true);
        WriteMemory(0x4BFCCD, &gPObjectArray[0] + 0x4C, true);
        WriteMemory(0x4BFCE1, &gPObjectArray[0] + 0x0, true);
        WriteMemory(0x4BFCE7, &gPObjectArray[0] + 0x4C, true);
        WriteMemory(0x4BFCEF, &gPObjectArray[0] + 0x68, true);

        // init loop
        MakeJMP(0x4BC486, InitializeHook1);
        MakeJMP(0x4BC4B5, InitializeHook2);

        // deinit loop
        MakeJMP(0x4BFCC6, RemoveAllParticleObjectsHook1);
        MakeJMP(0x4BFCF5, RemoveAllParticleObjectsHook2);
    };
} ParticleObjectsIII;

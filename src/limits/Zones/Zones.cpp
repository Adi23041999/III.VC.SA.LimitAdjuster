/*
* Zones Limits Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/
#include "LimitAdjuster.h"

using namespace injector;

char numAudioZones = 36;
int numZones = 50;
int numZonesInfos = numZones * 2;
int numMapZones = 25;
char numZoneSfxes = 36;

std::vector<short> AudioZoneArray;
std::vector<char> ZoneSfx;
std::vector<char> ZoneArray;
std::vector<char> ZoneInfoArray;
std::vector<char> MapZoneArray;

struct tPoliceRadioZone {
    char m_aName[8];
    unsigned int m_nSampleIndex;
    int field_12;
};

#pragma region asm

DWORD _temp;
//DWORD ext_4B5E2A = 0x4B5E2A;
//DWORD ext_4B5DE8 = 0x4B5DE8;
//void __declspec(naked) InitHook()
//{
//    __asm
//    {
//        cmp eax, numAudioZones
//        jb loc_4B5DE8
//        jmp ext_4B5E2A
//    loc_4B5DE8 :
//        jmp ext_4B5DE8
//    }
//}
//
//DWORD ext_4B8933 = 0x4B8933;
//DWORD ext_4B88D0 = 0x4B88D0;
//void __declspec(naked) SaveAllZonesHook1()
//{
//    __asm
//    {
//        cmp ecx, numAudioZones
//        mov[esi], edx
//        jb loc_4B88D0
//        jmp ext_4B8933
//    loc_4B88D0 :
//        jmp ext_4B88D0
//    }
//}
//
//DWORD ext_4B8D51 = 0x4B8D51;
//void __declspec(naked) LoadAllZonesHook1()
//{
//    __asm
//    {
//        mov edi, [esi]
//        cmp ecx, numAudioZones
//        mov[eax * 2 + AudioZoneArray], edi
//        jmp ext_4B8D51
//    }
//}

//DWORD ext_57FC90 = 0x57FC90;
//DWORD ext_57F65B = 0x57F65B;
//void __declspec(naked) SetupCrimeReportHook1()
//{
//    __asm
//    {
//        jl loc_57FC90
//        cmp eax, numAudioZones
//        jmp ext_57F65B
//    loc_57FC90:
//        jmp ext_57FC90
//    }
//}
//
//DWORD ext_57F6AF = 0x57F6AF;
//void __declspec(naked) SetupCrimeReportHook2()
//{
//    __asm
//    {
//        inc dl
//        add ecx, 0x10
//        cmp dl, numAudioZones
//        jmp ext_57F6AF
//    }
//}
//
//DWORD ext_57F6BA = 0x57F6BA;
//void __declspec(naked) SetupCrimeReportHook3()
//{
//    __asm
//    {
//        cmp dl, numAudioZones
//        jnb ext_57FC90
//        jmp ext_57F6BA
//    }
//}

//DWORD ext_4B5ECF = 0x4B5ECF;
//DWORD ext_4B5E37 = 0x4B5E37;
//void __declspec(naked) TheZonesInitHook1()
//{
//    __asm
//    {
//        add eax, 0x38
//        cmp esi, numZones
//        jb loc_4B5E37
//        jmp ext_4B5ECF
//    loc_4B5E37:
//		jmp ext_4B5E37
//    }
//}

DWORD ext_4B8365 = 0x4B8365;
DWORD ext_4B8355 = 0x4B8355;
void __declspec(naked) AddZoneToAudioZoneArrayHook()
{
    __asm
    {
        inc ecx
        add ebx, 0x38
        cmp ecx, numZones
        jb loc_4B8355
        jmp ext_4B8365
    loc_4B8355:
        jmp ext_4B8355
    }
}

DWORD ext_4B8662 = 0x4B8662;
void __declspec(naked) SaveAllZonesHook2()
{
    __asm
    {
        mov _temp, ecx
        mov ecx, numZones
        cmp dword ptr[esp], ecx
        mov ecx, _temp
        jmp ext_4B8662
    }
}

DWORD ext_4B8A7D = 0x4B8A7D;
void __declspec(naked) LoadAllZonesHook2()
{
    __asm
    {
        add edi, 0x38
		cmp esi, numZones
        pop ecx
		jmp ext_4B8A7D
    }
}

DWORD ext_4F3B85 = 0x4F3B85;
DWORD ext_4F3AD6 = 0x4F3AD6;
void __declspec(naked) GeneratePedsAtStartOfGameHook()
{
    __asm
    {
        cmp ebx, numZones
        jl loc_4F3AD6
        jmp ext_4F3B85
    loc_4F3AD6:
        jmp ext_4F3AD6
    }
}

DWORD ext_4B6049 = 0x4B6049;
DWORD ext_4B5ED3 = 0x4B5ED3;
void __declspec(naked) InitHook2()
{
    __asm
    {
        add eax, 0x3A
		cmp ecx, numZonesInfos
		jb loc_4B5ED3
		jmp ext_4B6049
    loc_4B5ED3:
        jmp ext_4B5ED3
    }
}

DWORD ext_4B87C2 = 0x4B87C2;
DWORD ext_4B8670 = 0x4B8670;
void __declspec(naked) SaveAllZonesHook3()
{
    __asm
    {
		cmp edx, numZonesInfos
		jb loc_4B8670
		jmp ext_4B87C2
    loc_4B8670:
        jmp ext_4B8670
    }
}

DWORD ext_4B8BD9 = 0x4B8BD9;
DWORD ext_4B8A87 = 0x4B8A87;
void __declspec(naked) LoadAllZonesHook3()
{
    __asm
    {
		cmp edx, numZonesInfos
        jb loc_4B8A87
        jmp ext_4B8BD9
    loc_4B8A87:
		jmp ext_4B8A87
    }
}

DWORD ext_4B6169 = 0x4B6169;
DWORD ext_4B60D1 = 0x4B60D1;
void __declspec(naked) InitHook3()
{
    __asm
    {
        add eax, 0x38
		cmp edi, numMapZones
		jb loc_4B60D1
		jmp ext_4B6169
	loc_4B60D1 :
		jmp ext_4B60D1
    }
}

DWORD ext_4B88CE = 0x4B88CE;
DWORD ext_4B87E7 = 0x4B87E7;
void __declspec(naked) SaveAllZonesHook4()
{
    __asm
    {
		mov _temp, eax
		mov eax, numMapZones
        cmp dword ptr[esp + 8], eax
		mov eax, _temp
        pop ecx
        jb loc_4B87E7
        jmp ext_4B88CE
    loc_4B87E7:
		jmp ext_4B87E7
    }
}

DWORD ext_4B8CEB = 0x4B8CEB;
DWORD ext_4B8BF8 = 0x4B8BF8;
void __declspec(naked) LoadAllZonesHook4()
{
    __asm
    {
        cmp esi, numMapZones
        pop ecx
        jb loc_4B8BF8
        jmp ext_4B8CEB
	loc_4B8BF8:
		jmp ext_4B8BF8
    }
}

#pragma endregion

void PatchAudioZonesIII()
{
    AudioZoneArray.resize(numAudioZones);
    //MakeRangedNOP(0x4B5DEE, 0x4B5E24);
    std::fill(AudioZoneArray.begin(), AudioZoneArray.end(), -1);
    
    //WriteMemory(0x4B5DF2, &AudioZoneArray[0] + 0x0, true);
    //WriteMemory(0x4B5DFB, &AudioZoneArray[0] + 0x2, true);
    //WriteMemory(0x4B5E04, &AudioZoneArray[0] + 0x4, true);
    //WriteMemory(0x4B5E0D, &AudioZoneArray[0] + 0x6, true);
    //WriteMemory(0x4B5E16, &AudioZoneArray[0] + 0x8, true);
    //WriteMemory(0x4B5E1F, &AudioZoneArray[0] + 0xA, true);
    WriteMemory(0x4B8377, &AudioZoneArray[0] + 0x0, true);
    WriteMemory(0x4B83F9, &AudioZoneArray[0] + 0x0, true);
    WriteMemory(0x4B88DD, &AudioZoneArray[0] + 0x0, true);
    WriteMemory(0x4B88EB, &AudioZoneArray[0] + 0x2, true);
    WriteMemory(0x4B88F9, &AudioZoneArray[0] + 0x4, true);
    WriteMemory(0x4B8907, &AudioZoneArray[0] + 0x6, true);
    WriteMemory(0x4B8915, &AudioZoneArray[0] + 0x8, true);
    WriteMemory(0x4B8926, &AudioZoneArray[0] + 0xA, true);
    WriteMemory(0x4B8D00, &AudioZoneArray[0] + 0x0, true);
    WriteMemory(0x4B8D0E, &AudioZoneArray[0] + 0x2, true);
    WriteMemory(0x4B8D1C, &AudioZoneArray[0] + 0x4, true);
    WriteMemory(0x4B8D2A, &AudioZoneArray[0] + 0x6, true);
    WriteMemory(0x4B8D38, &AudioZoneArray[0] + 0x8, true);
    WriteMemory(0x4B8D4D, &AudioZoneArray[0] + 0xA, true);
    WriteMemory(0x57F66A, &AudioZoneArray[0], true);
    WriteMemory(0x580586, &AudioZoneArray[0], true);

    //MakeJMP(0x4B5E24, InitHook);

    //MakeJMP(0x4B892A, SaveAllZonesHook1);
    WriteMemory(0x4B892D, numAudioZones, true);
    //MakeJMP(0x4B8D42, LoadAllZonesHook1);
    WriteMemory(0x4B8D48, numAudioZones, true);
}

void PatchZoneSfxIII()
{
    ZoneSfx.resize(sizeof(tPoliceRadioZone) * numZoneSfxes);

    // init loop
    WriteMemory(0x57EAD5, &ZoneSfx[0] + 0x0, true);
    WriteMemory(0x57EADF, &ZoneSfx[0] + 0x4, true);
    WriteMemory(0x57EAE9, &ZoneSfx[0] + 0x10, true);
    WriteMemory(0x57EAF3, &ZoneSfx[0] + 0x14, true);
    WriteMemory(0x57EAFD, &ZoneSfx[0] + 0x20, true);
    WriteMemory(0x57EB07, &ZoneSfx[0] + 0x24, true);
    WriteMemory(0x57EB11, &ZoneSfx[0] + 0x30, true);
    WriteMemory(0x57EB1B, &ZoneSfx[0] + 0x34, true);
    WriteMemory(0x57EB25, &ZoneSfx[0] + 0x40, true);
    WriteMemory(0x57EB2F, &ZoneSfx[0] + 0x44, true);
    WriteMemory(0x57EB39, &ZoneSfx[0] + 0x50, true);
    WriteMemory(0x57EB43, &ZoneSfx[0] + 0x54, true);

    WriteMemory(0x57EB59, &ZoneSfx[0] + 0x0, true);
    WriteMemory(0x57EB65, &ZoneSfx[0] + 0x10, true);
    WriteMemory(0x57EB70, &ZoneSfx[0] + 0x8, true);
    WriteMemory(0x57EB7B, &ZoneSfx[0] + 0x20, true);
    WriteMemory(0x57EB86, &ZoneSfx[0] + 0x8 + 0x10, true);
    WriteMemory(0x57EB91, &ZoneSfx[0] + 0x30, true);
    WriteMemory(0x57EB9C, &ZoneSfx[0] + 0x8 + 0x20, true);
    WriteMemory(0x57EBA9, &ZoneSfx[0] + 0x40, true);
    WriteMemory(0x57EBB4, &ZoneSfx[0] + 0x8 + 0x30, true);
    WriteMemory(0x57EBBF, &ZoneSfx[0] + 0x50, true);
    WriteMemory(0x57EBCA, &ZoneSfx[0] + 0x8 + 0x40, true);
    WriteMemory(0x57EBD5, &ZoneSfx[0] + 0x60, true);
    WriteMemory(0x57EBE0, &ZoneSfx[0] + 0x8 + 0x50, true);
    WriteMemory(0x57EBEB, &ZoneSfx[0] + 0x70, true);
    WriteMemory(0x57EBF6, &ZoneSfx[0] + 0x8 + 0x60, true);
    WriteMemory(0x57EC01, &ZoneSfx[0] + 0x80, true);
    WriteMemory(0x57EC0C, &ZoneSfx[0] + 0x8 + 0x70, true);
    WriteMemory(0x57EC17, &ZoneSfx[0] + 0x90, true);
    WriteMemory(0x57EC22, &ZoneSfx[0] + 0x8 + 0x80, true);
    WriteMemory(0x57EC2D, &ZoneSfx[0] + 0xA0, true);
    WriteMemory(0x57EC38, &ZoneSfx[0] + 0x8 + 0x90, true);
    WriteMemory(0x57EC45, &ZoneSfx[0] + 0xB0, true);
    WriteMemory(0x57EC50, &ZoneSfx[0] + 0x8 + 0xA0, true);
    WriteMemory(0x57EC5B, &ZoneSfx[0] + 0xC0, true);
    WriteMemory(0x57EC66, &ZoneSfx[0] + 0x8 + 0xB0, true);
    WriteMemory(0x57EC71, &ZoneSfx[0] + 0xD0, true);
    WriteMemory(0x57EC7C, &ZoneSfx[0] + 0x8 + 0xC0, true);
    WriteMemory(0x57EC89, &ZoneSfx[0] + 0xE0, true);
    WriteMemory(0x57EC94, &ZoneSfx[0] + 0x8 + 0xD0, true);
    WriteMemory(0x57ECA1, &ZoneSfx[0] + 0xF0, true);
    WriteMemory(0x57ECAC, &ZoneSfx[0] + 0x8 + 0xE0, true);
    WriteMemory(0x57ECB9, &ZoneSfx[0] + 0x100, true);
    WriteMemory(0x57ECC4, &ZoneSfx[0] + 0x8 + 0xF0, true);
    WriteMemory(0x57ECD1, &ZoneSfx[0] + 0x110, true);
    WriteMemory(0x57ECDC, &ZoneSfx[0] + 0x8 + 0x100, true);
    WriteMemory(0x57ECE8, &ZoneSfx[0] + 0x120, true);
    WriteMemory(0x57ECF3, &ZoneSfx[0] + 0x8 + 0x110, true);
    WriteMemory(0x57ECFE, &ZoneSfx[0] + 0x130, true);
    WriteMemory(0x57ED09, &ZoneSfx[0] + 0x8 + 0x120, true);
    WriteMemory(0x57ED16, &ZoneSfx[0] + 0x140, true);
    WriteMemory(0x57ED21, &ZoneSfx[0] + 0x8 + 0x130, true);
    WriteMemory(0x57ED2C, &ZoneSfx[0] + 0x150, true);
    WriteMemory(0x57ED37, &ZoneSfx[0] + 0x8 + 0x140, true);
    WriteMemory(0x57ED42, &ZoneSfx[0] + 0x160, true);
    WriteMemory(0x57ED4D, &ZoneSfx[0] + 0x8 + 0x150, true);
    WriteMemory(0x57ED58, &ZoneSfx[0] + 0x170, true);
    WriteMemory(0x57ED63, &ZoneSfx[0] + 0x8 + 0x160, true);
    WriteMemory(0x57ED70, &ZoneSfx[0] + 0x180, true);
    WriteMemory(0x57ED7B, &ZoneSfx[0] + 0x8 + 0x170, true);
    WriteMemory(0x57ED86, &ZoneSfx[0] + 0x190, true);
    WriteMemory(0x57ED91, &ZoneSfx[0] + 0x8 + 0x180, true);
    WriteMemory(0x57ED9C, &ZoneSfx[0] + 0x1A0, true);
    WriteMemory(0x57EDA7, &ZoneSfx[0] + 0x8 + 0x190, true);
    WriteMemory(0x57EDB2, &ZoneSfx[0] + 0x1B0, true);
    WriteMemory(0x57EDBD, &ZoneSfx[0] + 0x8 + 0x1A0, true);
    WriteMemory(0x57EDC8, &ZoneSfx[0] + 0x1C0, true);
    WriteMemory(0x57EDD3, &ZoneSfx[0] + 0x8 + 0x1B0, true);
    WriteMemory(0x57EDDE, &ZoneSfx[0] + 0x1D0, true);
    WriteMemory(0x57EDE9, &ZoneSfx[0] + 0x8 + 0x1C0, true);
    WriteMemory(0x57EDF4, &ZoneSfx[0] + 0x1E0, true);
    WriteMemory(0x57EDFF, &ZoneSfx[0] + 0x8 + 0x1D0, true);
    WriteMemory(0x57EE0A, &ZoneSfx[0] + 0x1F0, true);
    WriteMemory(0x57EE15, &ZoneSfx[0] + 0x8 + 0x1E0, true);
    WriteMemory(0x57EE20, &ZoneSfx[0] + 0x200, true);
    WriteMemory(0x57EE2B, &ZoneSfx[0] + 0x8 + 0x1F0, true);
    WriteMemory(0x57EE36, &ZoneSfx[0] + 0x210, true);
    WriteMemory(0x57EE41, &ZoneSfx[0] + 0x8 + 0x200, true);
    WriteMemory(0x57EE4C, &ZoneSfx[0] + 0x220, true);
    WriteMemory(0x57EE57, &ZoneSfx[0] + 0x8 + 0x210, true);
    WriteMemory(0x57EE77, &ZoneSfx[0] + 0x8 + 0x220, true);

    WriteMemory(0x57F687, &ZoneSfx[0] + 0x4, true);
    WriteMemory(0x57F68F, &ZoneSfx[0] + 0x0, true);
    WriteMemory(0x57F69D, &ZoneSfx[0] + 0x8, true);
    WriteMemory(0x58059C, &ZoneSfx[0] + 0x4, true);
    WriteMemory(0x5805A4, &ZoneSfx[0] + 0x0, true);
    WriteMemory(0x5805B2, &ZoneSfx[0] + 0x8, true);

    WriteMemory(0x57F65A, numZoneSfxes, true);
    //MakeJMP(0x57F651, SetupCrimeReportHook1);
    WriteMemory(0x57F6AE, numZoneSfxes, true);
    //MakeJMP(0x57F6A7, SetupCrimeReportHook2);
    WriteMemory(0x57F6B3, numZoneSfxes, true);
    //MakeJMP(0x57F6B1, SetupCrimeReportHook3);
    WriteMemory(0x57EB51, numZoneSfxes, true); // init
    WriteMemory(0x580576, numZoneSfxes, true);
    WriteMemory(0x5805CC, numZoneSfxes, true);
    WriteMemory(0x5805C7, numZoneSfxes, true);

    // ul test
    tPoliceRadioZone* sfx = (tPoliceRadioZone*)ZoneSfx.data();
    tPoliceRadioZone& ultest = sfx[numZoneSfxes - 1];
    strcpy(ultest.m_aName, "UL_ZON0");
    ultest.m_nSampleIndex = 236; // chinatown
}

void PatchZoneArrayIII()
{
    ZoneArray.resize(0x38 * numZones);

    // init loop
    //MakeRangedNOP(0x4B5E38, 0x4B5EC2);
    std::fill(ZoneArray.begin(), ZoneArray.end(), 0);
    
    //WriteMemory(0x4B5E3A, &ZoneArray[0] + 0x0 + 0x0, true);
    //WriteMemory(0x4B5E44, &ZoneArray[0] + 0x4 + 0x0, true);
    //WriteMemory(0x4B5E4E, &ZoneArray[0] + 0x8 + 0x0, true);
    //WriteMemory(0x4B5E58, &ZoneArray[0] + 0x8 + 0x4, true);
    //WriteMemory(0x4B5E62, &ZoneArray[0] + 0x8 + 0x8, true);
    //WriteMemory(0x4B5E6C, &ZoneArray[0] + 0x14 + 0x0, true);
    //WriteMemory(0x4B5E76, &ZoneArray[0] + 0x14 + 0x4, true);
    //WriteMemory(0x4B5E80, &ZoneArray[0] + 0x14 + 0x8, true);
    //WriteMemory(0x4B5E8A, &ZoneArray[0] + 0x20 + 0x0, true);
    //WriteMemory(0x4B5E95, &ZoneArray[0] + 0x28 + 0x0, true);
    //WriteMemory(0x4B5E9E, &ZoneArray[0] + 0x2A + 0x0, true);
    //WriteMemory(0x4B5EA6, &ZoneArray[0] + 0x2C + 0x0, true);
    //WriteMemory(0x4B5EB0, &ZoneArray[0] + 0x30 + 0x0, true);
    //WriteMemory(0x4B5EBA, &ZoneArray[0] + 0x34 + 0x0, true);

    WriteMemory(0x4B604A, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B6081, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B6089, &ZoneArray[0] + 0x8 + 0x0, true);
    WriteMemory(0x4B6091, &ZoneArray[0] + 0x8 + 0x4, true);
    WriteMemory(0x4B60A1, &ZoneArray[0] + 0x8 + 0x8, true);
    WriteMemory(0x4B60A9, &ZoneArray[0] + 0x14 + 0x0, true);
    WriteMemory(0x4B60B5, &ZoneArray[0] + 0x14 + 0x4, true);
    WriteMemory(0x4B60BF, &ZoneArray[0] + 0x14 + 0x8, true);
    WriteMemory(0x4B60C9, &ZoneArray[0] + 0x24 + 0x0, true);
    WriteMemory(0x4B62DE, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B6301, &ZoneArray[0] + 0x20 + 0x0, true);
    WriteMemory(0x4B6307, &ZoneArray[0] + 0x8 + 0x0, true);
    WriteMemory(0x4B6311, &ZoneArray[0] + 0x8 + 0x4, true);
    WriteMemory(0x4B631B, &ZoneArray[0] + 0x8 + 0x8, true);
    WriteMemory(0x4B6325, &ZoneArray[0] + 0x14 + 0x0, true);
    WriteMemory(0x4B632F, &ZoneArray[0] + 0x14 + 0x4, true);
    WriteMemory(0x4B6339, &ZoneArray[0] + 0x14 + 0x8, true);
    WriteMemory(0x4B633F, &ZoneArray[0] + 0x24 + 0x0, true);
    WriteMemory(0x4B635A, &ZoneArray[0] + 0x28 + 0x0, true);
    WriteMemory(0x4B636E, &ZoneArray[0] + 0x2A + 0x0, true);
    WriteMemory(0x4B64D2, &ZoneArray[0] + 0x38 + 0x0, true);
    WriteMemory(0x4B6505, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B6795, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B67AA, &ZoneArray[0] + 0x20 + 0x0, true);
    WriteMemory(0x4B67B3, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B67BB, &ZoneArray[0] + 0x2C + 0x0, true);
    WriteMemory(0x4B689B, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B68A6, &ZoneArray[0] + 0x20 + 0x0, true);
    WriteMemory(0x4B68BB, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B68C3, &ZoneArray[0] + 0x2C + 0x0, true);
    WriteMemory(0x4B69B9, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B69C8, &ZoneArray[0] + 0x2C + 0x0, true);
    WriteMemory(0x4B69CE, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B6FA9, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B8351, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B8381, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B838C, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B84D7, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B8503, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B8586, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B85AE, &ZoneArray[0] + 0x8 + 0x0, true);
    WriteMemory(0x4B85B6, &ZoneArray[0] + 0x8 + 0x4, true);
    WriteMemory(0x4B85C1, &ZoneArray[0] + 0x8 + 0x8, true);
    WriteMemory(0x4B85CC, &ZoneArray[0] + 0x14 + 0x0, true);
    WriteMemory(0x4B85D7, &ZoneArray[0] + 0x14 + 0x4, true);
    WriteMemory(0x4B85E2, &ZoneArray[0] + 0x14 + 0x8, true);
    WriteMemory(0x4B85ED, &ZoneArray[0] + 0x20 + 0x0, true);
    WriteMemory(0x4B85FB, &ZoneArray[0] + 0x24 + 0x0, true);
    WriteMemory(0x4B8607, &ZoneArray[0] + 0x28 + 0x0, true);
    WriteMemory(0x4B8614, &ZoneArray[0] + 0x2A + 0x0, true);
    WriteMemory(0x4B861D, &ZoneArray[0] + 0x2C + 0x0, true);
    WriteMemory(0x4B862F, &ZoneArray[0] + 0x30 + 0x0, true);
    WriteMemory(0x4B8641, &ZoneArray[0] + 0x34 + 0x0, true);
    WriteMemory(0x4B899B, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B89A1, &ZoneArray[0] + 0x4 + 0x0, true);
    WriteMemory(0x4B89A7, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B89AF, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B89B5, &ZoneArray[0] + 0x4 + 0x0, true);
    WriteMemory(0x4B89BD, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B89C3, &ZoneArray[0] + 0x4 + 0x0, true);
    WriteMemory(0x4B89CE, &ZoneArray[0] + 0x8 + 0x0, true);
    WriteMemory(0x4B89D9, &ZoneArray[0] + 0x8 + 0x4, true);
    WriteMemory(0x4B89E4, &ZoneArray[0] + 0x8 + 0x8, true);
    WriteMemory(0x4B89EF, &ZoneArray[0] + 0x14 + 0x0, true);
    WriteMemory(0x4B89FA, &ZoneArray[0] + 0x14 + 0x4, true);
    WriteMemory(0x4B8A05, &ZoneArray[0] + 0x14 + 0x8, true);
    WriteMemory(0x4B8A10, &ZoneArray[0] + 0x20 + 0x0, true);
    WriteMemory(0x4B8A1B, &ZoneArray[0] + 0x24 + 0x0, true);
    WriteMemory(0x4B8A28, &ZoneArray[0] + 0x28 + 0x0, true);
    WriteMemory(0x4B8A35, &ZoneArray[0] + 0x2A + 0x0, true);
    WriteMemory(0x4B8A46, &ZoneArray[0] + 0x2C + 0x0, true);
    WriteMemory(0x4B8A58, &ZoneArray[0] + 0x30 + 0x0, true);
    WriteMemory(0x4B8A71, &ZoneArray[0] + 0x34 + 0x0, true);
    WriteMemory(0x57F673, &ZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x58058F, &ZoneArray[0] + 0x0 + 0x0, true);

    //0x4B5EC5
    MakeJMP(0x4B835B, AddZoneToAudioZoneArrayHook);
    MakeJMP(0x4B865D, SaveAllZonesHook2);
    MakeJMP(0x4B8A75, LoadAllZonesHook2);
    MakeJMP(0x4F3B7B, GeneratePedsAtStartOfGameHook);
}

void PatchZoneInfoArrayIII()
{
    ZoneInfoArray.resize(0x3A * numZonesInfos);
    std::fill(ZoneInfoArray.begin(), ZoneInfoArray.end(), 0);

    WriteMemory(0x4B5ED6, &ZoneInfoArray[0] + 0x0, true);
    WriteMemory(0x4B5EDF, &ZoneInfoArray[0] + 0x2, true);
    WriteMemory(0x4B5EE8, &ZoneInfoArray[0] + 0x2, true);
    WriteMemory(0x4B5EF6, &ZoneInfoArray[0] + 0x4, true);
    WriteMemory(0x4B5EFD, &ZoneInfoArray[0] + 0x4, true);
    WriteMemory(0x4B5F0A, &ZoneInfoArray[0] + 0x6, true);
    WriteMemory(0x4B5F11, &ZoneInfoArray[0] + 0x6, true);
    WriteMemory(0x4B5F1E, &ZoneInfoArray[0] + 0x8, true);
    WriteMemory(0x4B5F25, &ZoneInfoArray[0] + 0x8, true);
    WriteMemory(0x4B5F2C, &ZoneInfoArray[0] + 0xA, true);
    WriteMemory(0x4B5F33, &ZoneInfoArray[0] + 0xA, true);
    WriteMemory(0x4B5F3A, &ZoneInfoArray[0] + 0xC, true);
    WriteMemory(0x4B5F41, &ZoneInfoArray[0] + 0xC, true);
    WriteMemory(0x4B5F4E, &ZoneInfoArray[0] + 0xE, true);
    WriteMemory(0x4B5F55, &ZoneInfoArray[0] + 0xE, true);
    WriteMemory(0x4B5F5C, &ZoneInfoArray[0] + 0x10, true);
    WriteMemory(0x4B5F63, &ZoneInfoArray[0] + 0x10, true);
    WriteMemory(0x4B5F6A, &ZoneInfoArray[0] + 0x12, true);
    WriteMemory(0x4B5F71, &ZoneInfoArray[0] + 0x12, true);
    WriteMemory(0x4B5F78, &ZoneInfoArray[0] + 0x14, true);
    WriteMemory(0x4B5F7F, &ZoneInfoArray[0] + 0x14, true);
    WriteMemory(0x4B5F86, &ZoneInfoArray[0] + 0x16, true);
    WriteMemory(0x4B5F8D, &ZoneInfoArray[0] + 0x16, true);
    WriteMemory(0x4B5F94, &ZoneInfoArray[0] + 0x18, true);
    WriteMemory(0x4B5F9B, &ZoneInfoArray[0] + 0x18, true);
    WriteMemory(0x4B5FA2, &ZoneInfoArray[0] + 0x1A, true);
    WriteMemory(0x4B5FA9, &ZoneInfoArray[0] + 0x1A, true);
    WriteMemory(0x4B5FB0, &ZoneInfoArray[0] + 0x1C, true);
    WriteMemory(0x4B5FB7, &ZoneInfoArray[0] + 0x1C, true);
    WriteMemory(0x4B5FBE, &ZoneInfoArray[0] + 0x1E, true);
    WriteMemory(0x4B5FC5, &ZoneInfoArray[0] + 0x1E, true);
    WriteMemory(0x4B5FCC, &ZoneInfoArray[0] + 0x20, true);
    WriteMemory(0x4B5FD3, &ZoneInfoArray[0] + 0x22, true);
    WriteMemory(0x4B5FDC, &ZoneInfoArray[0] + 0x24, true);
    WriteMemory(0x4B5FE5, &ZoneInfoArray[0] + 0x26, true);
    WriteMemory(0x4B5FEE, &ZoneInfoArray[0] + 0x28, true);
    WriteMemory(0x4B5FF7, &ZoneInfoArray[0] + 0x2A, true);
    WriteMemory(0x4B6000, &ZoneInfoArray[0] + 0x2C, true);
    WriteMemory(0x4B6009, &ZoneInfoArray[0] + 0x2E, true);
    WriteMemory(0x4B6012, &ZoneInfoArray[0] + 0x30, true);
    WriteMemory(0x4B601B, &ZoneInfoArray[0] + 0x32, true);
    WriteMemory(0x4B6024, &ZoneInfoArray[0] + 0x34, true);
    WriteMemory(0x4B602D, &ZoneInfoArray[0] + 0x36, true);
    WriteMemory(0x4B6036, &ZoneInfoArray[0] + 0x38, true);
    WriteMemory(0x4B6A2E, &ZoneInfoArray[0] + 0x0, true);
    WriteMemory(0x4B6A3B, &ZoneInfoArray[0] + 0x0, true);
    WriteMemory(0x4B6A41, &ZoneInfoArray[0] + 0x0, true);
    WriteMemory(0x4B6A7F, &ZoneInfoArray[0] + 0x0, true);
    WriteMemory(0x4B6DFC, &ZoneInfoArray[0] + 0x0, true);
    WriteMemory(0x4B6EF9, &ZoneInfoArray[0] + 0x0, true);
    WriteMemory(0x4B6F49, &ZoneInfoArray[0] + 0x22, true);
    WriteMemory(0x4B6F99, &ZoneInfoArray[0] + 0x38, true);
    WriteMemory(0x4B8673, &ZoneInfoArray[0] + 0x0, true);
    WriteMemory(0x4B867E, &ZoneInfoArray[0] + 0x2, true);
    WriteMemory(0x4B8689, &ZoneInfoArray[0] + 0x4, true);
    WriteMemory(0x4B8694, &ZoneInfoArray[0] + 0x6, true);
    WriteMemory(0x4B869F, &ZoneInfoArray[0] + 0x8, true);
    WriteMemory(0x4B86AA, &ZoneInfoArray[0] + 0xA, true);
    WriteMemory(0x4B86B5, &ZoneInfoArray[0] + 0xC, true);
    WriteMemory(0x4B86C0, &ZoneInfoArray[0] + 0xE, true);
    WriteMemory(0x4B86CB, &ZoneInfoArray[0] + 0x10, true);
    WriteMemory(0x4B86D6, &ZoneInfoArray[0] + 0x12, true);
    WriteMemory(0x4B86E1, &ZoneInfoArray[0] + 0x14, true);
    WriteMemory(0x4B86EC, &ZoneInfoArray[0] + 0x16, true);
    WriteMemory(0x4B86F7, &ZoneInfoArray[0] + 0x18, true);
    WriteMemory(0x4B8702, &ZoneInfoArray[0] + 0x1A, true);
    WriteMemory(0x4B870D, &ZoneInfoArray[0] + 0x1C, true);
    WriteMemory(0x4B8718, &ZoneInfoArray[0] + 0x1E, true);
    WriteMemory(0x4B8723, &ZoneInfoArray[0] + 0x20, true);
    WriteMemory(0x4B872E, &ZoneInfoArray[0] + 0x22, true);
    WriteMemory(0x4B8739, &ZoneInfoArray[0] + 0x24, true);
    WriteMemory(0x4B8744, &ZoneInfoArray[0] + 0x26, true);
    WriteMemory(0x4B874F, &ZoneInfoArray[0] + 0x28, true);
    WriteMemory(0x4B875A, &ZoneInfoArray[0] + 0x2A, true);
    WriteMemory(0x4B8765, &ZoneInfoArray[0] + 0x2C, true);
    WriteMemory(0x4B8770, &ZoneInfoArray[0] + 0x2E, true);
    WriteMemory(0x4B877B, &ZoneInfoArray[0] + 0x30, true);
    WriteMemory(0x4B8786, &ZoneInfoArray[0] + 0x32, true);
    WriteMemory(0x4B8791, &ZoneInfoArray[0] + 0x34, true);
    WriteMemory(0x4B879C, &ZoneInfoArray[0] + 0x36, true);
    WriteMemory(0x4B87A7, &ZoneInfoArray[0] + 0x38, true);
    WriteMemory(0x4B8A8E, &ZoneInfoArray[0] + 0x0, true);
    WriteMemory(0x4B8A99, &ZoneInfoArray[0] + 0x2, true);
    WriteMemory(0x4B8AA4, &ZoneInfoArray[0] + 0x4, true);
    WriteMemory(0x4B8AAF, &ZoneInfoArray[0] + 0x6, true);
    WriteMemory(0x4B8ABA, &ZoneInfoArray[0] + 0x8, true);
    WriteMemory(0x4B8AC5, &ZoneInfoArray[0] + 0xA, true);
    WriteMemory(0x4B8AD0, &ZoneInfoArray[0] + 0xC, true);
    WriteMemory(0x4B8ADB, &ZoneInfoArray[0] + 0xE, true);
    WriteMemory(0x4B8AE6, &ZoneInfoArray[0] + 0x10, true);
    WriteMemory(0x4B8AF1, &ZoneInfoArray[0] + 0x12, true);
    WriteMemory(0x4B8AFC, &ZoneInfoArray[0] + 0x14, true);
    WriteMemory(0x4B8B07, &ZoneInfoArray[0] + 0x16, true);
    WriteMemory(0x4B8B12, &ZoneInfoArray[0] + 0x18, true);
    WriteMemory(0x4B8B1D, &ZoneInfoArray[0] + 0x1A, true);
    WriteMemory(0x4B8B28, &ZoneInfoArray[0] + 0x1C, true);
    WriteMemory(0x4B8B33, &ZoneInfoArray[0] + 0x1E, true);
    WriteMemory(0x4B8B3E, &ZoneInfoArray[0] + 0x20, true);
    WriteMemory(0x4B8B49, &ZoneInfoArray[0] + 0x22, true);
    WriteMemory(0x4B8B54, &ZoneInfoArray[0] + 0x24, true);
    WriteMemory(0x4B8B5F, &ZoneInfoArray[0] + 0x26, true);
    WriteMemory(0x4B8B6A, &ZoneInfoArray[0] + 0x28, true);
    WriteMemory(0x4B8B75, &ZoneInfoArray[0] + 0x2A, true);
    WriteMemory(0x4B8B80, &ZoneInfoArray[0] + 0x2C, true);
    WriteMemory(0x4B8B8B, &ZoneInfoArray[0] + 0x2E, true);
    WriteMemory(0x4B8B96, &ZoneInfoArray[0] + 0x30, true);
    WriteMemory(0x4B8BA1, &ZoneInfoArray[0] + 0x32, true);
    WriteMemory(0x4B8BAC, &ZoneInfoArray[0] + 0x34, true);
    WriteMemory(0x4B8BB7, &ZoneInfoArray[0] + 0x36, true);
    WriteMemory(0x4B8BC5, &ZoneInfoArray[0] + 0x38, true);

    MakeJMP(0x4B603C, InitHook2);
    MakeJMP(0x4B87B8, SaveAllZonesHook3);
    MakeJMP(0x4B8BCF, LoadAllZonesHook3);
}

void PatchMapZoneArrayIII()
{
    MapZoneArray.resize(0x38 * numMapZones);
    std::fill(MapZoneArray.begin(), MapZoneArray.end(), 0);

    WriteMemory(0x4B60D4, &MapZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B60DE, &MapZoneArray[0] + 0x4 + 0x0, true);
    WriteMemory(0x4B60E8, &MapZoneArray[0] + 0x8 + 0x0, true);
    WriteMemory(0x4B60F2, &MapZoneArray[0] + 0x8 + 0x4, true);
    WriteMemory(0x4B60FC, &MapZoneArray[0] + 0x8 + 0x8, true);
    WriteMemory(0x4B6106, &MapZoneArray[0] + 0x14 + 0x0, true);
    WriteMemory(0x4B6110, &MapZoneArray[0] + 0x14 + 0x4, true);
    WriteMemory(0x4B611A, &MapZoneArray[0] + 0x14 + 0x8, true);
    WriteMemory(0x4B6124, &MapZoneArray[0] + 0x20 + 0x0, true);
    WriteMemory(0x4B612F, &MapZoneArray[0] + 0x28 + 0x0, true);
    WriteMemory(0x4B6138, &MapZoneArray[0] + 0x2A + 0x0, true);
    WriteMemory(0x4B6140, &MapZoneArray[0] + 0x2C + 0x0, true);
    WriteMemory(0x4B614A, &MapZoneArray[0] + 0x30 + 0x0, true);
    WriteMemory(0x4B6154, &MapZoneArray[0] + 0x34 + 0x0, true);
    WriteMemory(0x4B616A, &MapZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B6184, &MapZoneArray[0] + 0x8 + 0x0, true);
    WriteMemory(0x4B618C, &MapZoneArray[0] + 0x8 + 0x4, true);
    WriteMemory(0x4B6192, &MapZoneArray[0] + 0x8 + 0x8, true);
    WriteMemory(0x4B619A, &MapZoneArray[0] + 0x14 + 0x0, true);
    WriteMemory(0x4B61A4, &MapZoneArray[0] + 0x14 + 0x4, true);
    WriteMemory(0x4B61AE, &MapZoneArray[0] + 0x14 + 0x8, true);
    WriteMemory(0x4B61B8, &MapZoneArray[0] + 0x24 + 0x0, true);
    WriteMemory(0x4B6445, &MapZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B646C, &MapZoneArray[0] + 0x20 + 0x0, true);
    WriteMemory(0x4B6476, &MapZoneArray[0] + 0x8 + 0x0, true);
    WriteMemory(0x4B6480, &MapZoneArray[0] + 0x8 + 0x4, true);
    WriteMemory(0x4B648A, &MapZoneArray[0] + 0x8 + 0x8, true);
    WriteMemory(0x4B6494, &MapZoneArray[0] + 0x14 + 0x0, true);
    WriteMemory(0x4B649E, &MapZoneArray[0] + 0x14 + 0x4, true);
    WriteMemory(0x4B64A8, &MapZoneArray[0] + 0x14 + 0x8, true);
    WriteMemory(0x4B64AE, &MapZoneArray[0] + 0x24 + 0x0, true);
    WriteMemory(0x4B691C, &MapZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B695E, &MapZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B696A, &MapZoneArray[0] + 0x38 + 0x0, true);
    WriteMemory(0x4B6985, &MapZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B87EA, &MapZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B8812, &MapZoneArray[0] + 0x8 + 0x0, true);
    WriteMemory(0x4B881A, &MapZoneArray[0] + 0x8 + 0x4, true);
    WriteMemory(0x4B8825, &MapZoneArray[0] + 0x8 + 0x8, true);
    WriteMemory(0x4B8830, &MapZoneArray[0] + 0x14 + 0x0, true);
    WriteMemory(0x4B883B, &MapZoneArray[0] + 0x14 + 0x4, true);
    WriteMemory(0x4B8846, &MapZoneArray[0] + 0x14 + 0x8, true);
    WriteMemory(0x4B8851, &MapZoneArray[0] + 0x20 + 0x0, true);
    WriteMemory(0x4B885F, &MapZoneArray[0] + 0x24 + 0x0, true);
    WriteMemory(0x4B886B, &MapZoneArray[0] + 0x28 + 0x0, true);
    WriteMemory(0x4B8878, &MapZoneArray[0] + 0x2A + 0x0, true);
    WriteMemory(0x4B8881, &MapZoneArray[0] + 0x2C + 0x0, true);
    WriteMemory(0x4B8893, &MapZoneArray[0] + 0x30 + 0x0, true);
    WriteMemory(0x4B88A5, &MapZoneArray[0] + 0x34 + 0x0, true);
    WriteMemory(0x4B8C03, &MapZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B8C09, &MapZoneArray[0] + 0x4 + 0x0, true);
    WriteMemory(0x4B8C0F, &MapZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B8C17, &MapZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B8C1D, &MapZoneArray[0] + 0x4 + 0x0, true);
    WriteMemory(0x4B8C25, &MapZoneArray[0] + 0x0 + 0x0, true);
    WriteMemory(0x4B8C2B, &MapZoneArray[0] + 0x4 + 0x0, true);
    WriteMemory(0x4B8C36, &MapZoneArray[0] + 0x8 + 0x0, true);
    WriteMemory(0x4B8C41, &MapZoneArray[0] + 0x8 + 0x4, true);
    WriteMemory(0x4B8C4C, &MapZoneArray[0] + 0x8 + 0x8, true);
    WriteMemory(0x4B8C57, &MapZoneArray[0] + 0x14 + 0x0, true);
    WriteMemory(0x4B8C62, &MapZoneArray[0] + 0x14 + 0x4, true);
    WriteMemory(0x4B8C6D, &MapZoneArray[0] + 0x14 + 0x8, true);
    WriteMemory(0x4B8C78, &MapZoneArray[0] + 0x20 + 0x0, true);
    WriteMemory(0x4B8C83, &MapZoneArray[0] + 0x24 + 0x0, true);
    WriteMemory(0x4B8C90, &MapZoneArray[0] + 0x28 + 0x0, true);
    WriteMemory(0x4B8C9D, &MapZoneArray[0] + 0x2A + 0x0, true);
    WriteMemory(0x4B8CAE, &MapZoneArray[0] + 0x2C + 0x0, true);
    WriteMemory(0x4B8CC0, &MapZoneArray[0] + 0x30 + 0x0, true);
    WriteMemory(0x4B8CD9, &MapZoneArray[0] + 0x34 + 0x0, true);

    MakeJMP(0x4B615C, InitHook3);
    MakeJMP(0x4B88C1, SaveAllZonesHook4);
    MakeJMP(0x4B8CE0, LoadAllZonesHook4);
}

void ZonesReloadIII()
{
    WriteMemory<unsigned short>(0x95CC84, 0, true);
    //std::fill(AudioZoneArray.begin(), AudioZoneArray.end(), -1);
    std::fill(ZoneArray.begin(), ZoneArray.end(), 0);
    //std::fill(ZoneInfoArray.begin(), ZoneInfoArray.end(), 0);
    //std::fill(MapZoneArray.begin(), MapZoneArray.end(), 0);
}

class GameZones : public Adjuster
{
public:
    enum
    {
        AudioZones,
        Zones,
        MapZones,
    };

    const Limit* GetLimits()
    {
        if (GetGVM().IsIII())
        {
            static Limit limits[] =
            {
                DEFINE_LIMIT(AudioZones),
                DEFINE_LIMIT(Zones),
                DEFINE_LIMIT(MapZones),
                FINISH_LIMITS()
            };
            return limits;
        }
        return nullptr;
    }

    void ChangeLimit(int id, const std::string& value)
    {
        if (GetGVM().IsIII())
        {
            switch (id)
            {
            case AudioZones:
                //numAudioZones = std::stoi(value);
                numAudioZones = (char)min(std::stoi(value), 127); // currently limited to 127
                numZoneSfxes = (char)min(numAudioZones, 127); // currently limited to 127
                PatchAudioZonesIII();
                PatchZoneSfxIII();
                break;
            case Zones:
                numZones = std::stoi(value);
			    numZonesInfos = numZones * 2;
                PatchZoneArrayIII();
                PatchZoneInfoArrayIII();
                break;
            case MapZones:
                numMapZones = std::stoi(value);
                PatchMapZoneArrayIII();
                break;
            }
        }
    }

    void Process()
    {
        if (GetGVM().IsIII())
        {
            MakeRangedNOP(0x4B5E2C, 0x4B5E35);
            MakeCALL(0x4B5E2C, ZonesReloadIII);

            // patch save size
            int zoneSize = 10100;
            // audio zones
            zoneSize -= 36 * sizeof(short);
            zoneSize += numAudioZones * sizeof(short);
            // zone array
            zoneSize -= 0x38 * 50;
            zoneSize += 0x38 * numZones;
            // zone info array
            zoneSize -= 0x3A * 50 * 2;
            zoneSize += 0x3A * numZonesInfos;
            // map zone array
            zoneSize -= 0x38 * 25;
            zoneSize += 0x38 * numMapZones;
            WriteMemory(0x4B8526, zoneSize, true);
        }
    }

} GameZones;

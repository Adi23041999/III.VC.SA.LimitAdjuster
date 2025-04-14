/*
* Streaming Adjuster
* Copyright (c) 2016 aap <aap@papnet.eu>
* Copyright (c) 2025 Adi <adriank@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#include "LimitAdjuster.h"

using namespace injector;

size_t modelInfoPtrs_t;
size_t infoForModel_t;
std::vector<char> modelInfoPtrs;
std::vector<char> aInfoForModel;

short numDefaultModelInfoPtrs = 0;
int numDefaultTxdStore = 0;
short numModelInfoPtrs;
int numTxdStore;


// convenience functions as the infoForModel patch relies on the other two but they could be disabled in the ini
bool ShouldPatchModelInfoPtrs()
{ return numModelInfoPtrs > 0 && numModelInfoPtrs != numDefaultModelInfoPtrs; }

bool ShouldPatchTxdStore()
{ return numTxdStore > 0 && numTxdStore != numDefaultTxdStore; }

bool ShouldPatchInfoForModel()
{ return ShouldPatchModelInfoPtrs() || ShouldPatchTxdStore(); }

short GetNumModelInfoPtrs()
{ return ShouldPatchModelInfoPtrs() ? numModelInfoPtrs : numDefaultModelInfoPtrs; }

int GetNumTxdStore()
{ return ShouldPatchTxdStore() ? numTxdStore : numDefaultTxdStore; }

int GetNumInfoForModel()
{ return GetNumModelInfoPtrs() + GetNumTxdStore(); }


void PatchStreamingIII()
{
    if (ShouldPatchModelInfoPtrs())
    {
        short numModelInfoPtrs = GetNumModelInfoPtrs();
        // 4 more from unrolled loop
        modelInfoPtrs.resize(((int)numModelInfoPtrs + 4) * modelInfoPtrs_t);
        // modelinfo init loop
        WriteMemory(0x50B36E + 1, numModelInfoPtrs - 8, true);
        // patch default limit
        WriteMemory(0x401121 + 2, numModelInfoPtrs, true);
        WriteMemory(0x406919 + 2, numModelInfoPtrs, true);
        WriteMemory(0x406FC0 + 2, numModelInfoPtrs, true);
        WriteMemory(0x40701A + 2, numModelInfoPtrs, true);
        WriteMemory(0x40702B + 2, numModelInfoPtrs, true);
        WriteMemory(0x407F06 + 2, numModelInfoPtrs, true);
        WriteMemory(0x407F74 + 2, numModelInfoPtrs, true);
        WriteMemory(0x407F88 + 1, numModelInfoPtrs, true);
        WriteMemory(0x408856 + 2, numModelInfoPtrs, true);
        WriteMemory(0x408870 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x408911 + 2, numModelInfoPtrs, true);
        WriteMemory(0x408920 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x408995 + 2, numModelInfoPtrs, true);
        WriteMemory(0x4089D9 + 2, numModelInfoPtrs, true);
        WriteMemory(0x408A00 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x408A11 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x409481 + 2, numModelInfoPtrs, true);
        WriteMemory(0x409489 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x4094ED + 2, numModelInfoPtrs, true);
        WriteMemory(0x40952C + 2, numModelInfoPtrs, true);
        WriteMemory(0x409554 + 2, numModelInfoPtrs, true);
        WriteMemory(0x4095BE + 2, numModelInfoPtrs, true);
        WriteMemory(0x409607 + 2, numModelInfoPtrs, true);
        WriteMemory(0x409654 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x409660 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x409676 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x4096F5 + 2, numModelInfoPtrs, true);
        WriteMemory(0x409711 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x4097AA + 2, numModelInfoPtrs, true);
        WriteMemory(0x40990F + 1, numModelInfoPtrs, true);
        WriteMemory(0x409951 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x409996 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x4099B4 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x4099D1 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x409A42 + 2, numModelInfoPtrs, true);
        WriteMemory(0x409A60 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x409A84 + 2, numModelInfoPtrs, true);
        WriteMemory(0x409B18 + 2, numModelInfoPtrs, true);
        WriteMemory(0x409B45 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x409CA8 + 2, numModelInfoPtrs, true);
        WriteMemory(0x409D2E + 2, numModelInfoPtrs, true);
        WriteMemory(0x409EBD + 2, numModelInfoPtrs, true);
        WriteMemory(0x409EEA + 2, numModelInfoPtrs, true);
        WriteMemory(0x40A0D1 + 2, numModelInfoPtrs, true);
        WriteMemory(0x40A0F2 + 2, -numModelInfoPtrs, true);
        WriteMemory(0x40A1D4 + 2, numModelInfoPtrs, true);
        WriteMemory(0x40A209 + 1, numModelInfoPtrs, true);
        WriteMemory(0x40A273 + 2, numModelInfoPtrs, true);
        WriteMemory(0x40A58C + 2, numModelInfoPtrs, true);
        WriteMemory(0x40A7A8 + 2, numModelInfoPtrs, true);
        WriteMemory(0x40A80F + 1, numModelInfoPtrs, true);
        WriteMemory(0x40A838 + 2, numModelInfoPtrs, true);
        WriteMemory(0x454B68 + 3, numModelInfoPtrs, true);
        WriteMemory(0x476D9C + 2, numModelInfoPtrs, true); 
        WriteMemory(0x4A6087 + 1, numModelInfoPtrs, true);
        WriteMemory(0x4A60D0 + 1, numModelInfoPtrs, true);
        WriteMemory(0x50B5A1 + 2, numModelInfoPtrs, true);
        WriteMemory(0x50B901 + 2, numModelInfoPtrs, true);
        WriteMemory(0x50BBEB + 2, numModelInfoPtrs, true);
        WriteMemory(0x517C51 + 2, numModelInfoPtrs, true);
        WriteMemory(0x517D43 + 2, numModelInfoPtrs, true);
        WriteMemory(0x517D4B + 2, numModelInfoPtrs, true);
        WriteMemory(0x5279A5 + 2, numModelInfoPtrs, true);
        WriteMemory(0x585066 + 2, numModelInfoPtrs, true);
        WriteMemory(0x592D7E + 2, numModelInfoPtrs, true);
        WriteMemory(0x592D93 + 2, numModelInfoPtrs, true);
        WriteMemory(0x592E71 + 2, numModelInfoPtrs, true);
        WriteMemory(0x592F0A + 2, numModelInfoPtrs, true);

        // patch array refs
        WriteMemory(0x4010E3, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40394D, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x404C0A, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x404C20, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x405865, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4068E3, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x407CBF, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x407E2B, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x407F11, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x407F7F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x408440, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4084D1, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40856B, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x408601, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4086FA, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x408861, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x408978, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4089E4, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40938C, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x409417, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4094F8, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x409537, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40955F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4095C9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x409616, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x409701, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4097BD, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x409847, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40989B, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x409B24, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x409CB9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x409CF6, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x409EC8, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40A1E4, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40A27E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40A597, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40A7B3, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40A807, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40A843, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40A89E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40B031, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40B0D7, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40B1D2, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x40B4F9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x416C6E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x416DE3, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x416FA5, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x417C03, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x417C6F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x417CCD, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x417E6D, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41931F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41952C, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41A05D, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41A084, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41ADC0, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41ADD2, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41AE76, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41AEC9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41AF0B, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41AF46, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41AF8D, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41AFC8, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41B00D, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41B35F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41B88D, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41DE25, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x41DE39, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x42287B, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4228A4, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4253FF, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4255DF, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4257BF, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x425A54, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x425B48, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x425D32, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x425EC2, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x426047, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x427C17, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x427E61, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x42F1C9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x435487, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x437176, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x437208, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x43744A, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x43780A, &modelInfoPtrs[0] + 0x1D0, true);
        WriteMemory(0x437819, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x437819, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x449A88, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x449FED, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x44A2EB, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x44A84D, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x44C076, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x44C086, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x44C0A6, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x44C0B4, &modelInfoPtrs[0] + 0x1C, true);
        WriteMemory(0x44EDA1, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x44EDF0, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x454153, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4541A5, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4541B9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4541DB, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4541F2, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x454B16, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x455868, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x457B09, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x45A8BA, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x45C173, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x45C17A, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x467AC0, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x467AC7, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x467BF0, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x467BF7, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x467D27, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x467D2E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4689F2, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4689F9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x473EAC, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x473F47, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x473F70, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x473FDA, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x47401D, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x47429A, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4742D2, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x474317, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x47454C, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x474BB2, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x474E82, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4755C7, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4755EC, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x47695D, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4769BD, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x476A3F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x476A78, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x476A9E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x476D83, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4773B2, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4777DC, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x478147, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x478727, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x477EB1, &modelInfoPtrs[0] + 0x31C, true);
        WriteMemory(0x479AEE, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x491152, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x49B8FD, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x49BAB5, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x49DCD8, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x49DE76, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x49F7AD, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x49F7BC, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4A2B1B, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4A4D4B, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4A4E9C, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4A9367, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4A9390, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4A93B9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4A9856, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4A9932, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4A9948, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4A9A61, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4AD642, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4B0D59, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4B0D70, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4B10EA, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4B21CB, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4B4537, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4B460A, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4B4CB4, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4B58DC, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4BAE32, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4BB227, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4BBD8E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4BC27B, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4C52D3, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4C8F6F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4C8F91, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4C977E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4CBEDD, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4CBF53, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4CC2B4, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4CC2CC, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4CCEDD, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4CF907, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D01A0, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D106A, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D107F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D1732, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D4346, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D4AE5, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D5243, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D5338, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D5438, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D5537, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D6B0E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4D752A, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4E1A45, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4E1F53, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4E2D87, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4E2E73, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4E3405, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4E475E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4E4C9E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4E523B, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4E58A3, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4E9013, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4EC695, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4F46CA, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4F4717, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4F4910, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4F498E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4F4D44, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4F4EA1, &modelInfoPtrs[0] + 0x4, true);
        WriteMemory(0x4F4EC7, &modelInfoPtrs[0] + 0xC, true);
        WriteMemory(0x4F4EE7, &modelInfoPtrs[0] + 0x8, true);
        WriteMemory(0x4F4F07, &modelInfoPtrs[0] + 0x10, true);
        WriteMemory(0x4F4F23, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4F5945, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4F5975, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4F5991, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4F59A5, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4F59B9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x4FA58D, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x5034F6, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x503F4F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50B1F9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50B316, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50B321, &modelInfoPtrs[0] + 0x4, true);
        WriteMemory(0x50B32C, &modelInfoPtrs[0] + 0x8, true);
        WriteMemory(0x50B337, &modelInfoPtrs[0] + 0xC, true);
        WriteMemory(0x50B342, &modelInfoPtrs[0] + 0x10, true);
        WriteMemory(0x50B34D, &modelInfoPtrs[0] + 0x14, true);
        WriteMemory(0x50B358, &modelInfoPtrs[0] + 0x18, true);
        WriteMemory(0x50B363, &modelInfoPtrs[0] + 0x1C, true);
        WriteMemory(0x50B387, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50B39C, &modelInfoPtrs[0] + 0x4, true);
        WriteMemory(0x50B3B1, &modelInfoPtrs[0] + 0x8, true);
        WriteMemory(0x50B3C6, &modelInfoPtrs[0] + 0xC, true);
        WriteMemory(0x50B593, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50B873, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50B967, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50B9BA, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50BA01, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50BA4C, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50BAC5, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50BB0C, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50BB97, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50BBCB, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x50CE5C, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x5127EE, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x51392F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x514D72, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x514EC7, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x517415, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x517C13, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x517D05, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x518D9D, &modelInfoPtrs[0] + 0x2B0, true);
        WriteMemory(0x5203E9, &modelInfoPtrs[0] + 0x1E8, true);
        WriteMemory(0x520792, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x521042, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x5219A1, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x5219F3, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x529094, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x52C75F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x52D222, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x52D500, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53014A, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53022A, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53085E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x530874, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x5314BE, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x534369, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x535507, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x536DF7, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x5370E4, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53833F, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x538CC0, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x539831, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x539EC9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53B2C7, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53B323, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53BF84, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53C5F0, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53CBBB, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53CCB9, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53D10E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53D132, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53D14E, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53D168, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53E0A3, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53E423, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x53E966, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x540597, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x5411F3, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x5429BC, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x542D14, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x542D34, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x543D78, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x543DDE, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x5443F4, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x546394, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x547244, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x549971, &modelInfoPtrs[0] + 0x24C, true);
        WriteMemory(0x5499D3, &modelInfoPtrs[0] + 0x1F4, true);
        WriteMemory(0x54B194, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x54B3D0, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x54B76D, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x54DD58, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x54DDEE, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x54E2E1, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x54E5B0, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x54E94A, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x54FFD0, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x552666, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x552BDA, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x56250B, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x562568, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x562708, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x5747A4, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x585075, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x596DED, &modelInfoPtrs[0] + 0x0, true);
        WriteMemory(0x596E33, &modelInfoPtrs[0] + 0x0, true);
    }
    if (ShouldPatchTxdStore())
    {
        int numTxdStore = GetNumTxdStore();
        WriteMemory(0x406977 + 2, numTxdStore, true);
        WriteMemory(0x527457 + 1, numTxdStore, true);
        WriteMemory(0x5274CF + 2, numTxdStore, true);
        WriteMemory(0x592C98 + 1, numTxdStore, true);
        WriteMemory(0x592CE4 + 1, numTxdStore, true);
        WriteMemory(0x592D3D + 1, numTxdStore, true);
        WriteMemory(0x592E32 + 1, numTxdStore, true);
        WriteMemory(0x592F22 + 2, numTxdStore, true);
        WriteMemory(0x592F59 + 1, numTxdStore, true);
    }
    if (ShouldPatchInfoForModel())
    {
        int numInfoForModel = GetNumInfoForModel();
	    // The unrolled loop in CStreaming::Init inits 6 more elements
	    // after looping in 8 element increments because the default
	    // size 6350 % 8 == 6. We'll just allocate 6 more elements.
	    aInfoForModel.resize((numInfoForModel + 6) * infoForModel_t);
	    // fix loop limit
	    WriteMemory(0x40664A + 1, numInfoForModel - 8, true);

	    // move array references
        // special handling for these two as they are aInfoForModels but offset by numModelInfoPtrs, 0x8 is LoadState member
        int infoOffset = (GetNumModelInfoPtrs() * infoForModel_t) + 0x8;
        WriteMemory(0x40696B, &aInfoForModel[0] + infoOffset, true);
        WriteMemory(0x409ED9, &aInfoForModel[0] + infoOffset, true);

	    WriteMemory(0x40644C, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x406493, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x4064D8, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40651C, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x406560, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x4065A4, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x4065E8, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x406630, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x406688, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x4066DD, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40673F, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x4067A1, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x4067FC, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40684E, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x406EAB, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x406EF2, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x406FD3, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x4077AF, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x407E8A, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x407F28, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x407F30, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x407F96, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40887E, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x408894, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x4088C4, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x4089C9, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40937D, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x409406, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40946E, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x4094DD, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40958E, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40975B, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x409C93, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x409E8E, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x409F16, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40A0AC, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40A123, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40A1A4, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40A4AD, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40A699, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40A709, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40A7D4, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40A7DC, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40A864, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40A86C, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x40A9D7, &aInfoForModel[0] + 0x0, true);
	    WriteMemory(0x406456, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x40649D, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x4064E2, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x406526, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x40656A, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x4065AE, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x4065F2, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x40663A, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x406692, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x4066E7, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x406749, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x4067AB, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x406806, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x406858, &aInfoForModel[0] + 0x4, true);
	    WriteMemory(0x406444, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40648C, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4064D1, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x406515, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x406559, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40659D, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4065E1, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x406629, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x406681, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4066D6, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x406738, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40679A, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4067F5, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x406847, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4068FA, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x407EB9, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x407EF2, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x407FBB, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4082A4, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4082B6, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4082D1, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4082E3, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x408300, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x408312, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x408376, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x408846, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40889D, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4088D3, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40890A, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x408934, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x408962, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x409698, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x409D68, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40A198, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40A214, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40A7CB, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40A85B, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40B01B, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40B1DF, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40B225, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x40B262, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4180F7, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4276A7, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4355A8, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4371F2, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x43790D, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x43A77A, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x444609, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x4A9ED3, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x542729, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x54A5FD, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x54DD66, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x585C2A, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x5860E1, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x5872D3, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x587404, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x5953B1, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x5955B8, &aInfoForModel[0] + 0x8, true);
	    WriteMemory(0x406901, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x407ECB, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x407EDC, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x407EEC, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x407EFD, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x407F40, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x407FC2, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x4088A7, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x4088B8, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40896C, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40898B, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x4096BA, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x4098B8, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40991D, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x409948, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x4099F4, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x409A37, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x409AB3, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x409CDE, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x409D07, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x409EF4, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x409F69, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x409F7A, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40A0E9, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40A1C7, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40A2B4, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40A2C5, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40A4C9, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40A4DC, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40A7A3, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40A7C0, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40A833, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40A850, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40B0CB, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40B1C6, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40B22E, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x40B272, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x491175, &aInfoForModel[0] + 0x9, true);
	    WriteMemory(0x406461, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x4064A8, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x4064ED, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x406531, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x406575, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x4065B9, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x4065FD, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x406645, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x40669D, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x4066F2, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x406754, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x4067B6, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x406811, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x406863, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x406F0D, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x407027, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x40A2D3, &aInfoForModel[0] + 0xA, true);
	    WriteMemory(0x406472, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x4064B9, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x4064FE, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x406542, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x406586, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x4065CA, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x40660E, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x40665B, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x4066AE, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x406703, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x406765, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x4067C7, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x406822, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x406874, &aInfoForModel[0] + 0xC, true);
	    WriteMemory(0x406468, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x4064AF, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x4064F4, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x406538, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x40657C, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x4065C0, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x406604, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x406651, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x4066A4, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x4066F9, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x40675B, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x4067BD, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x406818, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x40686A, &aInfoForModel[0] + 0x10, true);
	    WriteMemory(0x41820F, &aInfoForModel[0] + 0x30, true);
	    WriteMemory(0x418255, &aInfoForModel[0] + 0x44, true);
	    WriteMemory(0x41828A, &aInfoForModel[0] + 0x58, true);
	    WriteMemory(0x41FD35, &aInfoForModel[0] + 0x6C, true);
	    WriteMemory(0x41FE02, &aInfoForModel[0] + 0x80, true);
	    WriteMemory(0x4182CB, &aInfoForModel[0] + 0xD0, true);
	    WriteMemory(0x4182D4, &aInfoForModel[0] + 0xE4, true);
	    WriteMemory(0x40ADCA, &aInfoForModel[0] + 0x210, true);
	    WriteMemory(0x41FDF7, &aInfoForModel[0] + 0x79C, true);
	    WriteMemory(0x41FE32, &aInfoForModel[0] + 0x79C, true);
	    WriteMemory(0x41FD2A, &aInfoForModel[0] + 0x850, true);
	    WriteMemory(0x41FD65, &aInfoForModel[0] + 0x850, true);
	    WriteMemory(0x40AF2D, &aInfoForModel[0] + 0x864, true);
	    WriteMemory(0x41824C, &aInfoForModel[0] + 0x864, true);
	    WriteMemory(0x40AEE9, &aInfoForModel[0] + 0x92C, true);
	    WriteMemory(0x418206, &aInfoForModel[0] + 0x92C, true);
	    WriteMemory(0x40AF8E, &aInfoForModel[0] + 0x990, true);
	    WriteMemory(0x418278, &aInfoForModel[0] + 0x990, true);
	    WriteMemory(0x490F13, &aInfoForModel[0] + 0x990, true);
	    WriteMemory(0x40AF84, &aInfoForModel[0] + 0x9A4, true);
	    WriteMemory(0x418281, &aInfoForModel[0] + 0x9A4, true);
	    WriteMemory(0x54FF19, &aInfoForModel[0] + 0x9B8, true);
    }
}

class StreamingInfo : public Adjuster
{
public:
	enum
	{
		ModelInfoPtrs,
		TxdStore,
	};
    
	const Limit* GetLimits()
	{
        if (GetGVM().IsIII())
        {
            static Limit limits[] =
            {
                DEFINE_LIMIT(ModelInfoPtrs),
                DEFINE_LIMIT(TxdStore),
                FINISH_LIMITS()
            };
            return limits;
        }
		return nullptr;
	}

	void ChangeLimit(int id, const std::string& value)
	{
        switch (id)
        {
        case ModelInfoPtrs:
            numModelInfoPtrs = std::stoi(value);
            break;
        case TxdStore:
            numTxdStore = std::stoi(value);
            break;
        }

		if (GetGVM().IsIII())
        {
            modelInfoPtrs_t = 0x30;
            infoForModel_t = 0x14;
            numDefaultModelInfoPtrs = 5500;
            numDefaultTxdStore = 850;
            PatchStreamingIII();
        }

	}

} StreamingInfo;

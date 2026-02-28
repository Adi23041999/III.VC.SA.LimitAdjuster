#ifdef GTA3
#include "Phones.h"
#include "CPhoneInfo.h"

using namespace injector;

int32 Phones::NumPhones;
std::vector<char> Phones::gPhoneInfoNew;

const char* Phones::GetLimitName()
{
    return "Phones";
}

void Phones::ChangeLimit(int, const std::string& value)
{        
    NumPhones = std::stoi(value); 
    size_t gPhoneInfo_t = 0x8 + (NumPhones * sizeof(CPhone));
    gPhoneInfoNew.resize(gPhoneInfo_t);
    std::fill(gPhoneInfoNew.begin(), gPhoneInfoNew.end(), 0U);
        
    WriteMemory(0x42F743, &gPhoneInfoNew[0] + 0x8 + 0x2C, true);
    WriteMemory(0x444674, &gPhoneInfoNew[0], true);
    WriteMemory(0x4446E8, &gPhoneInfoNew[0], true);
    WriteMemory(0x44474F, &gPhoneInfoNew[0], true);
    WriteMemory(0x44478A, &gPhoneInfoNew[0], true);
    WriteMemory(0x4447C5, &gPhoneInfoNew[0], true);
    WriteMemory(0x44C386, &gPhoneInfoNew[0], true);
    WriteMemory(0x44C442, &gPhoneInfoNew[0], true);
    WriteMemory(0x44C539, &gPhoneInfoNew[0], true);
    WriteMemory(0x44C62F, &gPhoneInfoNew[0], true);
    WriteMemory(0x44C760, &gPhoneInfoNew[0], true);
    WriteMemory(0x44C890, &gPhoneInfoNew[0], true);
    WriteMemory(0x44CD4A, &gPhoneInfoNew[0], true);
    WriteMemory(0x44CE9D, &gPhoneInfoNew[0], true);
    WriteMemory(0x44D02F, &gPhoneInfoNew[0], true);
    WriteMemory(0x44D1BB, &gPhoneInfoNew[0], true);
    WriteMemory(0x44EBCA, &gPhoneInfoNew[0], true);
    WriteMemory(0x48C249, &gPhoneInfoNew[0], true);
    WriteMemory(0x48C3C3, &gPhoneInfoNew[0], true);
    WriteMemory(0x48C56C, &gPhoneInfoNew[0], true);
    WriteMemory(0x48C9E7, &gPhoneInfoNew[0], true);
    WriteMemory(0x4C04DB, &gPhoneInfoNew[0] + 0x8 + 0x2C, true);
    WriteMemory(0x4C04E4, &gPhoneInfoNew[0] + 0x8 + 0x2C, true);
    WriteMemory(0x4C10D9, &gPhoneInfoNew[0], true);
    WriteMemory(0x4C1109, &gPhoneInfoNew[0] + 0x8 + 0x2C, true);
    WriteMemory(0x4C112A, &gPhoneInfoNew[0] + 0x8 + 0x8, true);
    WriteMemory(0x4C1130, &gPhoneInfoNew[0] + 0x8 + 0x4, true);
    WriteMemory(0x4C1136, &gPhoneInfoNew[0] + 0x8, true);
    WriteMemory(0x4D0504, &gPhoneInfoNew[0], true);
    WriteMemory(0x4D3CF0, &gPhoneInfoNew[0] + 0x8 + 0x4, true);
    WriteMemory(0x4D3CF6, &gPhoneInfoNew[0] + 0x8, true);
    WriteMemory(0x4D3E4E, &gPhoneInfoNew[0] + 0x8 + 0x2C, true);
    WriteMemory(0x588A8D, &gPhoneInfoNew[0] + 0x8 + 0x2C, true);
    WriteMemory(0x590127, &gPhoneInfoNew[0], true);
    WriteMemory(0x591246, &gPhoneInfoNew[0], true);

    WriteMemory(0x430074, gPhoneInfo_t, true);

    // save
    injector::MakeInline<0x430109, 0x430110>([](injector::reg_pack& regs)
        {
			int32& i = *(int32*)(regs.esp + 4);
			regs.eip = (i < NumPhones) ? 0x430097 : 0x430110;
        });

    // load
    injector::MakeInline<0x4301C6, 0x4301D1>([](injector::reg_pack& regs)
        {
            int32& i = *(int32*)(regs.esp + 4);
            regs.eip = (i < NumPhones) ? 0x430147 : 0x4301D1;
        });
};
#endif // GTA3

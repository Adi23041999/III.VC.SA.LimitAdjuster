#ifdef GTA3
#include "ParticleObjects.h"
#include "CParticleObject.h"

using namespace injector;

int32 ParticleObjects::NumParticleObjects = 100;
std::vector<CParticleObject> ParticleObjects::gPObjectArray;

const char* ParticleObjects::GetLimitName()
{
    return "ParticleObjects";
}

void ParticleObjects::ChangeLimit(int, const std::string& value)
{
    NumParticleObjects = std::stoi(value);
    gPObjectArray.resize(NumParticleObjects);
        
    WriteMemory(0x4BC45E, &gPObjectArray[0], true);
    WriteMemory(0x4BC468, &gPObjectArray[0].m_pPrev, true);
    WriteMemory(0x4BC47C, &gPObjectArray[0], true);
    WriteMemory(0x4BC482, &gPObjectArray[0].m_pPrev, true);
    WriteMemory(0x4BC48D, &gPObjectArray[0].m_pNext, true);
    WriteMemory(0x4BC4A1, &gPObjectArray[0], true);
    WriteMemory(0x4BC4A7, &gPObjectArray[0].m_pNext, true);
    WriteMemory(0x4BC4AF, &gPObjectArray[0].m_nState, true);

    WriteMemory(0x4BFC88, &gPObjectArray[0], true);
    WriteMemory(0x4BFCA8, &gPObjectArray[0].m_pPrev, true);
    WriteMemory(0x4BFCBC, &gPObjectArray[0], true);
    WriteMemory(0x4BFCC2, &gPObjectArray[0].m_pPrev, true);
    WriteMemory(0x4BFCCD, &gPObjectArray[0].m_pNext, true);
    WriteMemory(0x4BFCE1, &gPObjectArray[0], true);
    WriteMemory(0x4BFCE7, &gPObjectArray[0].m_pNext, true);
    WriteMemory(0x4BFCEF, &gPObjectArray[0].m_nState, true);

    // init loop
    injector::MakeInline<0x4BC486>([](injector::reg_pack& regs)
        {
			regs.eip = ((int32)regs.ecx == NumParticleObjects - 1) ? 0x4BC48B : 0x4BC497;
        });
    injector::MakeInline<0x4BC4BB>([](injector::reg_pack& regs)
        {
            regs.eip = ((int32)regs.ecx < NumParticleObjects) ? 0x4BC462 : 0x4BC4C0;
        });

    // deinit loop
    injector::MakeInline<0x4BFCC6>([](injector::reg_pack& regs)
        {
            regs.eip = ((int32)regs.ecx == NumParticleObjects - 1) ? 0x4BFCCB : 0x4BFCD7;
        });
    injector::MakeInline<0x4BFCFB>([](injector::reg_pack& regs)
        {
            regs.eip = ((int32)regs.ecx < NumParticleObjects) ? 0x4BFCA2 : 0x4BFD00;
        });
};
#endif // GTA3

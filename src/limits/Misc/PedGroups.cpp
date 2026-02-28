#ifdef GTA3
#include "PedGroups.h"
#include "CPopulation.h"
#include "CTheZones.h"
#include "CStreaming.h"
#include "CGeneral.h"
#include "CFileMgr.h"


std::vector<std::vector<int>> PedGroup::ms_pPedGroups;
int PedGroup::NumPedGroups = 31;
int PedGroup::NumPedGroupModels = 8;

const Adjuster::Limit* PedGroup::GetLimits()
{
    static Limit limits[] =
    {
        DEFINE_LIMIT(PedGroups),
        DEFINE_LIMIT(PedGroupModels),
        FINISH_LIMITS()
    };
    return limits;
}

void PedGroup::ChangeLimit(int id, const std::string& value)
{
    switch (id)
    {
    case PedGroups:
		NumPedGroups = std::stoi(value);
        break;
	case PedGroupModels:
		NumPedGroupModels = std::stoi(value);
		break;
    }
}

void PedGroup::Process()
{
    if (NumPedGroups != 31 || NumPedGroupModels != 8)
    {
        ms_pPedGroups = std::vector<std::vector<int>>(NumPedGroups, std::vector<int>(NumPedGroupModels, -1));

        // CStreaming::StreamZoneModels
        injector::MakeInline<0x40AA55, 0x40AACA>([](injector::reg_pack& regs)
            {
                CZoneInfo& info = *(CZoneInfo*)(regs.esp + 0xC);
                int& ms_currentPedGrp = CStreaming::ms_currentPedGrp;

           	    // unload pevious group
		        if(ms_currentPedGrp != -1)
			        for(int i = 0; i < NumPedGroupModels; i++){
				        if(ms_pPedGroups[ms_currentPedGrp][i] != -1){
					        CStreaming::SetModelIsDeletable(ms_pPedGroups[ms_currentPedGrp][i]);
                            CStreaming::SetModelTxdIsDeletable(ms_pPedGroups[ms_currentPedGrp][i]);
				        }
			        }
            
                ms_currentPedGrp = info.pedgrp;

		        for(int i = 0; i < NumPedGroupModels; i++){
			        if(ms_pPedGroups[ms_currentPedGrp][i] != -1)
                        CStreaming::RequestModel(ms_pPedGroups[ms_currentPedGrp][i], /*STREAMFLAGS_DONT_REMOVE*/1);
		        }

                regs.eip = 0x40AACA;
		    });

		// CStreaming::RemoveCurrentZonesModels
        injector::MakeInline<0x40AD0D, 0x40AD3C>([](injector::reg_pack& regs)
            {
                int& ms_currentPedGrp = CStreaming::ms_currentPedGrp;
                for (int i = 0; i < NumPedGroupModels; i++) {
                    if (ms_pPedGroups[ms_currentPedGrp][i] == -1)
                        break;
                    if (ms_pPedGroups[ms_currentPedGrp][i] != /*MI_MALE01*/7)
                        CStreaming::SetModelIsDeletable(ms_pPedGroups[ms_currentPedGrp][i]);
                }
                regs.eip = 0x40AD3C;
	        });
        // CPopulation::LoadPedGroups
        injector::MakeJMP(0x4F3870, LoadPedGroups);
        // CPopulation::ChooseCivilianOccupation
        injector::MakeJMP(0x4F5720, ChooseCivilianOccupation);
    }
}

int PedGroup::ChooseCivilianOccupation(int group)
{
    return ms_pPedGroups[group][CGeneral::GetRandomNumberInRange(0, NumPedGroupModels)];
}

void PedGroup::LoadPedGroups()
{
	int fd;
	char line[1024];
	int nextPedGroup = 0;
	// char unused[16]; // non-existence of that in mobile kinda verifies that
	char modelName[256];

	CFileMgr::ChangeDir("\\DATA\\");
	fd = CFileMgr::OpenFile("PEDGRP.DAT", "r");
	CFileMgr::ChangeDir("\\");
	while (CFileMgr::ReadLine(fd, line, sizeof(line))) {
		int end;
		// find end of line
		for (end = 0; ; end++) {
			if (line[end] == '\n')
				break;
			if (line[end] == ',' || line[end] == '\r')
				line[end] = ' ';
		}
		line[end] = '\0';
		int cursor = 0;
		int i;
		for (i = 0; i < NumPedGroupModels; i++) {
			while (line[cursor] <= ' ' && line[cursor] != '\0')
				++cursor;

			if (line[cursor] == '#')
				break;

			// find next whitespace
			int nextWhitespace;
			for (nextWhitespace = cursor; line[nextWhitespace] > ' '; ++nextWhitespace)
				;

			if (cursor == nextWhitespace)
				break;

			// read until next whitespace
			strncpy(modelName, &line[cursor], nextWhitespace - cursor);
			modelName[nextWhitespace - cursor] = '\0';
			CModelInfo::GetModelInfo(modelName, &ms_pPedGroups[nextPedGroup][i]);
			cursor = nextWhitespace;
		}
		if (i == NumPedGroupModels)
			nextPedGroup++;
	}
	CFileMgr::CloseFile(fd);
}
#endif // GTA3

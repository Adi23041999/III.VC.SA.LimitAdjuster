/*
* Paths Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#if GTA3
#include "LimitAdjuster.h"
#include "PathFindIII.h"
#include "OLACommon.h"
#ifdef FIX_BUGS
#include "PathFindingFixes.h"
#endif

using namespace injector;

class PathsIII : public SimpleAdjuster
{
public:
    const char* GetLimitName()
    {
        return IsIII() ? "Paths" : nullptr;
    }

    void ChangeLimit(int, const std::string& value)
    {
        // limits are currently fixed to max possible values
        // would be nice to expose to the ini but probably too much hassle
        if (std::stoi(value) <= 0)
            return;

#ifdef FIX_BUGS
        MakeJMP(0x41BAE0, PathFindingFixes::PickNextNodeRandomly);
        MakeJMP(0x477FF0, PathFindingFixes::LoadCarPathNode);
#endif

        WriteMemory(0x4788B0, &NewInfoForTileCars, true);
        WriteMemory(0x4788C2, &NewInfoForTilePeds, true);

        WriteMemory(0x4788A5, PATHNODESIZE, true);

        const int carPathLinksOffset = NUM_PATHNODES * sizeof(CPathNodeRe);
        WriteMemory(0x417266, carPathLinksOffset, true);
        WriteMemory(0x41733F, carPathLinksOffset, true);
        WriteMemory(0x4189C8, carPathLinksOffset, true);
        WriteMemory(0x418A5F, carPathLinksOffset, true);
        WriteMemory(0x41C10A, carPathLinksOffset, true);
        WriteMemory(0x41C187, carPathLinksOffset, true);
        WriteMemory(0x41CABA, carPathLinksOffset, true);
        WriteMemory(0x41CB37, carPathLinksOffset, true);
        WriteMemory(0x41D036, carPathLinksOffset, true);
        WriteMemory(0x41D0B7, carPathLinksOffset, true);
        WriteMemory(0x41E3C5, carPathLinksOffset, true);
        WriteMemory(0x41E47C, carPathLinksOffset, true);
        WriteMemory(0x41E6A9, carPathLinksOffset, true);
        WriteMemory(0x41EAA3, carPathLinksOffset, true);

        WriteMemory(0x413834, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x413878, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x413880, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41388C, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x413894, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x4138D6, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x4138E2, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x4138EA, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x413916, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41392B, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x413951, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x413966, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x413A82, &TheNewPaths, true);
        WriteMemory(0x413CEB, &TheNewPaths, true);
        WriteMemory(0x416B27, &TheNewPaths, true);
        WriteMemory(0x416B99, &TheNewPaths, true);
        WriteMemory(0x416BE5, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x416BFB, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x416C05, &TheNewPaths.m_connections, true);
        WriteMemory(0x416C15, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x416C1F, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x416C36, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x416C46, &TheNewPaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x416C53, &TheNewPaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x416FDC, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x416FE2, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x416FEE, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x416FF4, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4170BB, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x417109, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41711B, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41712A, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x41714C, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x417159, &TheNewPaths.m_connections, true);
        WriteMemory(0x41718D, &TheNewPaths, true);
        WriteMemory(0x417192, &TheNewPaths, true);
        WriteMemory(0x4171F2, &TheNewPaths, true);
        WriteMemory(0x41725E, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x417277, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x4172B2, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4172C3, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x417330, &TheNewPaths, true);
        WriteMemory(0x4173EE, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x417404, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41743B, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x417457, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41749C, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x4174B7, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4174E8, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x417503, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x417671, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41767F, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x4176B2, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x4176C3, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x417721, &TheNewPaths, true);
        WriteMemory(0x417729, &TheNewPaths, true);
        WriteMemory(0x4177D5, &TheNewPaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4177EC, &TheNewPaths.m_pathNodes->pos.z, true);
        WriteMemory(0x41895A, &TheNewPaths, true);
        WriteMemory(0x4189A0, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4189CE, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x4189E9, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4189F5, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x418A54, &TheNewPaths, true);
        WriteMemory(0x418B27, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x418B33, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x418B58, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x418B65, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41BB13, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41BB2E, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x41BB3B, &TheNewPaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41BB44, &TheNewPaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41BBCD, &TheNewPaths, true);
        WriteMemory(0x41BBF6, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BC03, &TheNewPaths.m_connections, true);
        WriteMemory(0x41BC30, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BC3D, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x41BC4E, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x41BC5A, &TheNewPaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41BC63, &TheNewPaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41BCAD, &TheNewPaths, true);
        WriteMemory(0x41BD3B, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BD4F, &TheNewPaths.m_connections, true);
        WriteMemory(0x41BD61, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BD6B, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x41BD7C, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x41BD88, &TheNewPaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41BD92, &TheNewPaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41BDC7, &TheNewPaths, true);
        WriteMemory(0x41BE33, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BE40, &TheNewPaths.m_connections, true);
        WriteMemory(0x41BE52, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BE5C, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x41BE6D, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x41BE79, &TheNewPaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41BE82, &TheNewPaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41BEA0, &TheNewPaths, true);
        WriteMemory(0x41BF74, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BF81, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x41BFAB, &TheNewPaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41BFC5, &TheNewPaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41BFE7, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C00A, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C049, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C04F, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C059, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C05F, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C105, &TheNewPaths, true);
        WriteMemory(0x41C175, &TheNewPaths, true);
        WriteMemory(0x41C203, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41C215, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41C235, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41C23D, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41C26F, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41C284, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C2AF, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41C2C4, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C37A, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C387, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C38F, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C399, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C3A8, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C3B2, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C524, &TheNewPaths.m_pathNodes->pos.z, true);
        WriteMemory(0x41C52F, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C53A, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C5DB, &TheNewPaths, true);
        WriteMemory(0x41C5EE, &TheNewPaths.m_pathNodes->pos.z, true);
        WriteMemory(0x41C5F4, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C5FA, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C645, &TheNewPaths, true);
        WriteMemory(0x41C65E, &TheNewPaths.m_pathNodes->pos.z, true);
        WriteMemory(0x41C664, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C66A, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C682, &TheNewPaths, true);
        WriteMemory(0x41C69E, &TheNewPaths, true);
        WriteMemory(0x41C6AB, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41C6C1, &TheNewPaths.m_connections, true);
        WriteMemory(0x41C707, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41C737, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41C744, &TheNewPaths.m_connections, true);
        WriteMemory(0x41C762, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C768, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C771, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C777, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C8D5, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41C8E6, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x41C910, &TheNewPaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41C92A, &TheNewPaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41C954, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C969, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41C994, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C9A9, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41C9C6, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41C9CC, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41C9D6, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41C9DC, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41CAB5, &TheNewPaths, true);
        WriteMemory(0x41CB25, &TheNewPaths, true);
        WriteMemory(0x41CBB9, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41CBC9, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41CBE9, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41CBF7, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41CC27, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41CC3C, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41CC67, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41CC7C, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41CD85, &TheNewPaths, true);
        WriteMemory(0x41CDE5, &TheNewPaths, true);
        WriteMemory(0x41CE65, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41CE76, &TheNewPaths.m_connections, true);
        WriteMemory(0x41CE87, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x41CEAD, &TheNewPaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41CEC7, &TheNewPaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41CEF1, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41CF06, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41CF31, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41CF46, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41CF63, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41CF69, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41CF73, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41CF79, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41D031, &TheNewPaths, true);
        WriteMemory(0x41D0A5, &TheNewPaths, true);
        WriteMemory(0x41D139, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41D149, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41D169, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41D177, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41D1A7, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41D1BC, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41D1E7, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41D1FC, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41E391, &TheNewPaths, true);
        WriteMemory(0x41E3B2, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41E3CF, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41E401, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41E40F, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41E470, &TheNewPaths, true);
        WriteMemory(0x41E4FD, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41E50D, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41E51B, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41E529, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41E697, &TheNewPaths, true);
        WriteMemory(0x41E71D, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41E72F, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41E775, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41E78A, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41E7B5, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41E7CA, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41E7F0, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41E804, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41EA91, &TheNewPaths, true);
        WriteMemory(0x41EB1A, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41EB2C, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41F85E, &TheNewPaths, true);
        WriteMemory(0x41F8A2, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41F8CA, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41F8D7, &TheNewPaths.m_connections, true);
        WriteMemory(0x41F8E2, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41F8E8, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41F8F2, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41F8F8, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41F970, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41F979, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41F981, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41F987, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41FA1F, &TheNewPaths, true);
        WriteMemory(0x41FA71, &TheNewPaths, true);
        WriteMemory(0x41FA9F, &TheNewPaths, true);
        WriteMemory(0x41FAC4, &TheNewPaths, true);
        WriteMemory(0x41FB53, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41FB60, &TheNewPaths.m_connections, true);
        WriteMemory(0x41FB78, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41FB85, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x41FBBA, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41FBC4, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41FBCE, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x41FBF4, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41FBFE, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41FC08, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x41FC28, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41FC32, &TheNewPaths.m_connections, true);
        WriteMemory(0x41FEAA, &TheNewPaths, true);
        WriteMemory(0x420096, &TheNewPaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4200AC, &TheNewPaths.m_pathNodes->pos.z, true);
        //0x42D3E9                                                                                       
        //0x42D3F6                                                                                       
        //0x42D404                                                                                       
        //0x42D411                                                                                       
        //0x42D452                                                                                       
        //0x42D466                                                                                       
        //0x42D476                                                                                       
        //0x42D498                                                                                       
        //0x42D4A2                                                                                       
        //0x42D4B6                                                                                       
        //0x42D4D4                                                                                       
        //0x42D4DB                                                                                       
        //0x42D4E4                                                                                       
        //0x42D4F1                                                                                       
        //0x42D4F9                                                                                       
        WriteMemory(0x42E264, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x42E27B, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x42E285, &TheNewPaths.m_connections, true);
        WriteMemory(0x42E296, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x42E2A0, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x42E2AB, &TheNewPaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x42E2D9, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x42E2EC, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x42E2F6, &TheNewPaths.m_connections, true);
        WriteMemory(0x42E305, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x42E30F, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x42E31A, &TheNewPaths.m_carPathLinks->trafficLightType, true);
        //0x42E63E                                                                                       
        //0x42E659                                                                                       
        WriteMemory(0x436344, &TheNewPaths, true);
        WriteMemory(0x43636B, &TheNewPaths, true);
        WriteMemory(0x4365FD, &TheNewPaths, true);
        WriteMemory(0x436622, &TheNewPaths, true);
        WriteMemory(0x436F53, &TheNewPaths.m_numMapObjects, true);
        WriteMemory(0x436F67, &TheNewPaths.m_objectFlags, true);
        WriteMemory(0x437044, &TheNewPaths.m_mapObjects, true);
        WriteMemory(0x437358, &TheNewPaths.m_objectFlags, true);
        WriteMemory(0x442554, &TheNewPaths, true);
        WriteMemory(0x44262F, &TheNewPaths, true);
        WriteMemory(0x443C12, &TheNewPaths, true);
        WriteMemory(0x443CD6, &TheNewPaths, true);
        WriteMemory(0x4459CD, &TheNewPaths, true);
        WriteMemory(0x4459FD, &TheNewPaths, true);
        WriteMemory(0x445AC3, &TheNewPaths, true);
        WriteMemory(0x445AF3, &TheNewPaths, true);
        WriteMemory(0x44D99A, &TheNewPaths, true);
        WriteMemory(0x44D9F4, &TheNewPaths, true);
        WriteMemory(0x44DA4E, &TheNewPaths, true);
        WriteMemory(0x44DAA8, &TheNewPaths, true);
        WriteMemory(0x44F393, &TheNewPaths, true);
        WriteMemory(0x44F3AB, &TheNewPaths, true);
        WriteMemory(0x44F3C0, &TheNewPaths, true);
        WriteMemory(0x454FCE, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x454FDC, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x45505A, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x455063, &TheNewPaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4550AF, &TheNewPaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x4550B4, &TheNewPaths.m_numPathNodes, true);
        WriteMemory(0x4550D3, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x4550E9, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x4550F4, &TheNewPaths.m_carPathConnections, true);
        WriteMemory(0x45512F, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x455135, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x455144, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x45514E, &TheNewPaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455160, &TheNewPaths.m_numCarPathLinks, true);
        WriteMemory(0x455171, &TheNewPaths.m_numCarPathNodes, true);
        WriteMemory(0x45518D, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4551B6, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x455206, &TheNewPaths.m_pathNodes->firstLink, true);
        WriteMemory(0x455210, &TheNewPaths.m_connectionFlags, true);
        WriteMemory(0x455224, &TheNewPaths.m_connections, true);
        WriteMemory(0x455231, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x45525C, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4552A5, &TheNewPaths.m_connectionFlags, true);
        WriteMemory(0x4552AE, &TheNewPaths.m_pathNodes->numLinks, true);
        WriteMemory(0x4552C7, &TheNewPaths.m_numPathNodes, true);
        WriteMemory(0x45536D, &TheNewPaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455389, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x4553A0, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x4553D2, &TheNewPaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455410, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x455416, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x45541E, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x455424, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4554A2, &TheNewPaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x4554BE, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x4554D5, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x455507, &TheNewPaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455545, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x45554B, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x455553, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x455559, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4555E4, &TheNewPaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455600, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x455617, &TheNewPaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x455649, &TheNewPaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455687, &TheNewPaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x45568D, &TheNewPaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x455695, &TheNewPaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x45569B, &TheNewPaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x456470, &TheNewPaths.m_carPathLinks->trafficLightType + 0x1, true); // flags
        WriteMemory(0x456484, &TheNewPaths.m_carPathLinks->trafficLightType + 0x1, true); // flags
        WriteMemory(0x476E2F, &TheNewPaths, true);
        WriteMemory(0x477FD6, &TheNewPaths, true);
        WriteMemory(0x4780C4, &TheNewPaths, true);
        WriteMemory(0x4788FD, &TheNewPaths, true);
        WriteMemory(0x48BFB6, &TheNewPaths, true);
        WriteMemory(0x48BFC0, &TheNewPaths, true);
        WriteMemory(0x48C06F, &TheNewPaths, true);
        WriteMemory(0x48C62B, &TheNewPaths, true);
        WriteMemory(0x48C671, &TheNewPaths, true);
        WriteMemory(0x490F50, &TheNewPaths, true);
        WriteMemory(0x490FA4, &TheNewPaths.m_pathNodes->pos.z, true);
        WriteMemory(0x490FAC, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x490FB4, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x49FE6B, &TheNewPaths, true);
        WriteMemory(0x4B40E7, &TheNewPaths, true);
        WriteMemory(0x4B410B, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4B4115, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4B4125, &TheNewPaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4B41FF, &TheNewPaths, true);
        WriteMemory(0x4B4223, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4B422D, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4B423D, &TheNewPaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4C22F8, &TheNewPaths.m_mapObjects, true);
        WriteMemory(0x4C7361, &TheNewPaths, true);
        WriteMemory(0x4C9B3B, &TheNewPaths, true);
        WriteMemory(0x4C9C07, &TheNewPaths, true);
        WriteMemory(0x4C9E49, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4C9E53, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4C9F26, &TheNewPaths, true);
        WriteMemory(0x4C9F3E, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4C9F44, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4C9F67, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4C9F81, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4D2154, &TheNewPaths, true);
        WriteMemory(0x4D280A, &TheNewPaths, true);
        WriteMemory(0x4D2874, &TheNewPaths, true);
        WriteMemory(0x4D29FF, &TheNewPaths, true);
        WriteMemory(0x4D2ABB, &TheNewPaths, true);
        WriteMemory(0x4D2B1F, &TheNewPaths, true);
        WriteMemory(0x4D2B4D, &TheNewPaths, true);
        WriteMemory(0x4DAF13, &TheNewPaths, true);
        WriteMemory(0x4DAF4E, &TheNewPaths, true);
        WriteMemory(0x4DAFED, &TheNewPaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4DAFF7, &TheNewPaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4DAFFF, &TheNewPaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4E3ACA, &TheNewPaths, true);
        WriteMemory(0x4E3B70, &TheNewPaths, true);
        WriteMemory(0x4E3BBC, &TheNewPaths.m_connections, true);
        WriteMemory(0x4E3BC5, &TheNewPaths, true);
        WriteMemory(0x4E3C81, &TheNewPaths.m_connections, true);
        WriteMemory(0x4E3C8A, &TheNewPaths, true);
        WriteMemory(0x4E3D4A, &TheNewPaths.m_connections, true);
        WriteMemory(0x4E3D53, &TheNewPaths, true);
        WriteMemory(0x4F4E02, &TheNewPaths, true);
        WriteMemory(0x589268, &TheNewPaths, true);
        WriteMemory(0x589327, &TheNewPaths, true);
        WriteMemory(0x58A95E, &TheNewPaths, true);
        WriteMemory(0x58A995, &TheNewPaths, true);
        WriteMemory(0x58A9AA, &TheNewPaths, true);
        WriteMemory(0x58AAA4, &TheNewPaths, true);
        WriteMemory(0x58AABB, &TheNewPaths, true);
        WriteMemory(0x58AAD0, &TheNewPaths, true);
        WriteMemory(0x58FF21, &TheNewPaths, true);
        WriteMemory(0x591096, &TheNewPaths, true);

        MakeJMP(0x4294A0, &CPathFindRe::Init);
        MakeJMP(0x429540, &CPathFindRe::RegisterMapObject);
        MakeJMP(0x429610, &CPathFindRe::PreparePathData);
        MakeJMP(0x42B040, &CPathFindRe::DoPathSearch);
        MakeJMP(0x42B790, &CPathFindRe::RemoveBadStartNode);
        MakeJMP(0x42B9F0, &CPathFindRe::FindNextNodeWandering);
        MakeJMP(0x42BF10, &CPathFindRe::NewGenerateCarCreationCoors);
        MakeJMP(0x42C1E0, &CPathFindRe::GeneratePedCreationCoors);
        MakeJMP(0x42C8C0, &CPathFindRe::TestCoorsCloseness);
        MakeJMP(0x42C990, &CPathFindRe::CalcRoadDensity);
        MakeJMP(0x42CC30, &CPathFindRe::FindNodeClosestToCoors);
        MakeJMP(0x42CDC0, &CPathFindRe::FindNodeClosestToCoorsFavourDirection);
        MakeJMP(0x42CFC0, &CPathFindRe::FindNodeOrientationForCarPlacement);
        MakeJMP(0x42D060, &CPathFindRe::FindNodeOrientationForCarPlacementFacingDestination);
        MakeJMP(0x42D580, &CPathFindRe::AllocatePathFindInfoMem);
#ifndef FIX_BUGS
        MakeJMP(0x42D690, &CPathFindRe::StoreNodeInfoCar);
#endif
        MakeJMP(0x42D7E0, &CPathFindRe::StoreNodeInfoPed);
        MakeJMP(0x42D960, &CPathFindRe::SwitchRoadsOffInArea);
        MakeJMP(0x42DA50, &CPathFindRe::SwitchPedRoadsOffInArea);
        MakeJMP(0x42DB50, &CPathFindRe::SwitchRoadsInAngledArea);
        MakeJMP(0x42DED0, &CPathFindRe::SwitchOffNodeAndNeighbours);
        MakeJMP(0x42DF50, &CPathFindRe::MarkRoadsBetweenLevelsInArea);
        MakeJMP(0x42E040, &CPathFindRe::PedMarkRoadsBetweenLevelsInArea);
        MakeJMP(0x42E1B0, &CPathFindRe::TestForPedTrafficLight);
        MakeJMP(0x42E340, &CPathFindRe::TestCrossesRoad);
        MakeJMP(0x42E3B0, &CPathFindRe::SetLinksBridgeLights);
        MakeJMP(0x42E450, &CPathFindRe::Save);
        MakeJMP(0x42E550, &CPathFindRe::Load);
    };
} PathsIII;

#endif // GTA3

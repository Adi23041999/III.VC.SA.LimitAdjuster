/*
* Paths Adjuster
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "LimitAdjuster.h"
#include "PathFindIII.h"
#include "Types/General.h"
#ifdef FIX_BUGS
#include "PathFindingFixes.h"
#endif

using namespace injector;

namespace PathFindWrappers
{
    static void __fastcall Init(void* ECX, void* EDX)
    {
        ThePaths.Init();
    }
    static void __fastcall AllocatePathFindInfoMem(void* ECX, void* EDX, int16 numPathGroups)
    {
        ThePaths.AllocatePathFindInfoMem(numPathGroups);
    }
    static void __fastcall RegisterMapObject(void* ECX, void* EDX, CTreadable* mapObject)
    {
        ThePaths.RegisterMapObject(mapObject);
    }
    static void __fastcall StoreNodeInfoPed(void* ECX, void* EDX, int16 id, int16 node, int8 type, int8 next, int16 x, int16 y, int16 z, int16 width, bool crossing)
    {
        ThePaths.StoreNodeInfoPed(id, node, type, next, x, y, z, width, crossing);
    }
#ifndef FIX_BUGS
    static void __fastcall StoreNodeInfoCar(void* ECX, void* EDX, int16 id, int16 node, int8 type, int8 next, int16 x, int16 y, int16 z, int16 width, int8 numLeft, int8 numRight)
    {
        ThePaths.StoreNodeInfoCar(id, node, type, next, x, y, z, width, numLeft, numRight);
    }
#endif
    static void __fastcall PreparePathData(void* ECX, void* EDX)
    {
        ThePaths.PreparePathData();
    }
    static float __fastcall CalcRoadDensity(void* ECX, void* EDX, float x, float y)
    {
        return ThePaths.CalcRoadDensity(x, y);
    }
    static bool __fastcall TestForPedTrafficLight(void* ECX, void* EDX, CPathNode* n1, CPathNode* n2)
    {
        return ThePaths.TestForPedTrafficLight(n1, n2);
    }
    static bool __fastcall TestCrossesRoad(void* ECX, void* EDX, CPathNode* n1, CPathNode* n2)
    {
        return ThePaths.TestCrossesRoad(n1, n2);
    }
    static void __fastcall RemoveBadStartNode(void* ECX, void* EDX, CVector pos, CPathNode** nodes, int16* n)
    {
        ThePaths.RemoveBadStartNode(pos, nodes, n);
    }
    static void __fastcall SetLinksBridgeLights(void* ECX, void* EDX, float x1, float x2, float y1, float y2, bool enable)
    {
        ThePaths.SetLinksBridgeLights(x1, x2, y1, y2, enable);
    }
    static void __fastcall SwitchOffNodeAndNeighbours(void* ECX, void* EDX, int32 nodeId, bool disable)
    {
        ThePaths.SwitchOffNodeAndNeighbours(nodeId, disable);
    }
    static void __fastcall SwitchRoadsOffInArea(void* ECX, void* EDX, float x1, float x2, float y1, float y2, float z1, float z2, bool disable)
    {
        ThePaths.SwitchRoadsOffInArea(x1, x2, y1, y2, z1, z2, disable);
    }
    static void __fastcall SwitchPedRoadsOffInArea(void* ECX, void* EDX, float x1, float x2, float y1, float y2, float z1, float z2, bool disable)
    {
        ThePaths.SwitchPedRoadsOffInArea(x1, x2, y1, y2, z1, z2, disable);
    }
    static void __fastcall SwitchRoadsInAngledArea(void* ECX, void* EDX, float x1, float y1, float z1, float x2, float y2, float z2, float length, uint8 type, uint8 enable)
    {
        ThePaths.SwitchRoadsInAngledArea(x1, x2, y1, y2, z1, z2, length, type, enable);
    }
    static void __fastcall MarkRoadsBetweenLevelsInArea(void* ECX, void* EDX, float x1, float x2, float y1, float y2, float z1, float z2)
    {
        ThePaths.PedMarkRoadsBetweenLevelsInArea(x1, x2, y1, y2, z1, z2);
    }
    static void __fastcall PedMarkRoadsBetweenLevelsInArea(void* ECX, void* EDX, float x1, float x2, float y1, float y2, float z1, float z2)
    {
        ThePaths.PedMarkRoadsBetweenLevelsInArea(x1, x2, y1, y2, z1, z2);
    }
    static int32 __fastcall FindNodeClosestToCoors(void* ECX, void* EDX, CVector coors, uint8 type, float distLimit, bool ignoreDisabled = false, bool ignoreBetweenLevels = false)
    {
        return ThePaths.FindNodeClosestToCoors(coors, type, distLimit, ignoreDisabled, ignoreBetweenLevels);
    }
    static int32 __fastcall FindNodeClosestToCoorsFavourDirection(void* ECX, void* EDX, CVector coors, uint8 type, float dirX, float dirY)
    {
        return ThePaths.FindNodeClosestToCoorsFavourDirection(coors, type, dirX, dirY);
    }
    static float __fastcall FindNodeOrientationForCarPlacement(void* ECX, void* EDX, int32 nodeId)
    {
        return ThePaths.FindNodeOrientationForCarPlacement(nodeId);
    }
    static float __fastcall FindNodeOrientationForCarPlacementFacingDestination(void* ECX, void* EDX, int32 nodeId, float x, float y, bool towards)
    {
        return ThePaths.FindNodeOrientationForCarPlacementFacingDestination(nodeId, x, y, towards);
    }
    static bool __fastcall NewGenerateCarCreationCoors(void* ECX, void* EDX, float x, float y, float dirX, float dirY, float spawnDist, float angleLimit, bool forward, CVector* pPosition, int32* pNode1, int32* pNode2, float* pPositionBetweenNodes, bool ignoreDisabled = false)
    {
        return ThePaths.NewGenerateCarCreationCoors(x, y, dirX, dirY, spawnDist, angleLimit, forward, pPosition, pNode1, pNode2, pPositionBetweenNodes, ignoreDisabled);
    }
    static bool __fastcall GeneratePedCreationCoors(void* ECX, void* EDX, float x, float y, float minDist, float maxDist, float minDistOffScreen, float maxDistOffScreen, CVector* pPosition, int32* pNode1, int32* pNode2, float* pPositionBetweenNodes, CMatrix* camMatrix)
    {
        return ThePaths.GeneratePedCreationCoors(x, y, minDist, maxDist, minDistOffScreen, maxDistOffScreen, pPosition, pNode1, pNode2, pPositionBetweenNodes, camMatrix);
    }
    static void __fastcall FindNextNodeWandering(void* ECX, void* EDX, uint8 type, CVector coors, CPathNode** lastNode, CPathNode** nextNode, uint8 curDir, uint8* nextDir)
    {
        ThePaths.FindNextNodeWandering(type, coors, lastNode, nextNode, curDir, nextDir);
    }
    static void __fastcall DoPathSearch(void* ECX, void* EDX, uint8 type, CVector start, int32 startNodeId, CVector target, CPathNode** nodes, int16* numNodes, int16 maxNumNodes, CPhysical* vehicle, float* dist, float distLimit, int32 forcedTargetNode)
    {
        ThePaths.DoPathSearch(type, start, startNodeId, target, nodes, numNodes, maxNumNodes, vehicle, dist, distLimit, forcedTargetNode);
    }
    static bool __fastcall TestCoorsCloseness(void* ECX, void* EDX, CVector target, uint8 type, CVector start)
    {
        return ThePaths.TestCoorsCloseness(target, type, start);
    }
    static void __fastcall Save(void* ECX, void* EDX, uint8* buf, uint32* size)
    {
        ThePaths.Save(buf, size);
    }
    static void __fastcall Load(void* ECX, void* EDX, uint8* buf, uint32 size)
    {
        ThePaths.Load(buf, size);
    }
}


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
        MakeCALL(0x41BAD1, PathFindingFixes::PickNextNodeRandomly);
        MakeCALL(0x476D41, PathFindingFixes::LoadCarPathNode);
        MakeCALL(0x476EF0, PathFindingFixes::LoadCarPathNode);
#endif

        WriteMemory(0x4788B0, &InfoForTileCars, true);
        WriteMemory(0x4788C2, &InfoForTilePeds, true);

        WriteMemory(0x4788A5, PATHNODESIZE, true);

        const int carPathLinksOffset = NUM_PATHNODES * sizeof(CPathNode);
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

        WriteMemory(0x413834, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x413878, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x413880, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41388C, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x413894, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x4138D6, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x4138E2, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x4138EA, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x413916, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41392B, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x413951, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x413966, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x413A82, &ThePaths, true);
        WriteMemory(0x413CEB, &ThePaths, true);
        WriteMemory(0x416B27, &ThePaths, true);
        WriteMemory(0x416B99, &ThePaths, true);
        WriteMemory(0x416BE5, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x416BFB, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x416C05, &ThePaths.m_connections, true);
        WriteMemory(0x416C15, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x416C1F, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x416C36, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x416C46, &ThePaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x416C53, &ThePaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x416FDC, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x416FE2, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x416FEE, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x416FF4, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4170BB, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x417109, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41711B, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41712A, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x41714C, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x417159, &ThePaths.m_connections, true);
        WriteMemory(0x41718D, &ThePaths, true);
        WriteMemory(0x417192, &ThePaths, true);
        WriteMemory(0x4171F2, &ThePaths, true);
        WriteMemory(0x41725E, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x417277, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x4172B2, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4172C3, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x417330, &ThePaths, true);
        WriteMemory(0x4173EE, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x417404, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41743B, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x417457, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41749C, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x4174B7, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4174E8, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x417503, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x417671, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41767F, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x4176B2, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x4176C3, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x417721, &ThePaths, true);
        WriteMemory(0x417729, &ThePaths, true);
        WriteMemory(0x4177D5, &ThePaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4177EC, &ThePaths.m_pathNodes->pos.z, true);
        WriteMemory(0x41895A, &ThePaths, true);
        WriteMemory(0x4189A0, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4189CE, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x4189E9, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4189F5, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x418A54, &ThePaths, true);
        WriteMemory(0x418B27, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x418B33, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x418B58, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x418B65, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41BB13, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41BB2E, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x41BB3B, &ThePaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41BB44, &ThePaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41BBCD, &ThePaths, true);
        WriteMemory(0x41BBF6, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BC03, &ThePaths.m_connections, true);
        WriteMemory(0x41BC30, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BC3D, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x41BC4E, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x41BC5A, &ThePaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41BC63, &ThePaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41BCAD, &ThePaths, true);
        WriteMemory(0x41BD3B, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BD4F, &ThePaths.m_connections, true);
        WriteMemory(0x41BD61, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BD6B, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x41BD7C, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x41BD88, &ThePaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41BD92, &ThePaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41BDC7, &ThePaths, true);
        WriteMemory(0x41BE33, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BE40, &ThePaths.m_connections, true);
        WriteMemory(0x41BE52, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BE5C, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x41BE6D, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x41BE79, &ThePaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41BE82, &ThePaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41BEA0, &ThePaths, true);
        WriteMemory(0x41BF74, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41BF81, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x41BFAB, &ThePaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41BFC5, &ThePaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41BFE7, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C00A, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C049, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C04F, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C059, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C05F, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C105, &ThePaths, true);
        WriteMemory(0x41C175, &ThePaths, true);
        WriteMemory(0x41C203, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41C215, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41C235, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41C23D, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41C26F, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41C284, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C2AF, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41C2C4, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C37A, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C387, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C38F, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C399, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C3A8, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C3B2, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C524, &ThePaths.m_pathNodes->pos.z, true);
        WriteMemory(0x41C52F, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C53A, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C5DB, &ThePaths, true);
        WriteMemory(0x41C5EE, &ThePaths.m_pathNodes->pos.z, true);
        WriteMemory(0x41C5F4, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C5FA, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C645, &ThePaths, true);
        WriteMemory(0x41C65E, &ThePaths.m_pathNodes->pos.z, true);
        WriteMemory(0x41C664, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C66A, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C682, &ThePaths, true);
        WriteMemory(0x41C69E, &ThePaths, true);
        WriteMemory(0x41C6AB, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41C6C1, &ThePaths.m_connections, true);
        WriteMemory(0x41C707, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41C737, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41C744, &ThePaths.m_connections, true);
        WriteMemory(0x41C762, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C768, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41C771, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C777, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41C8D5, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41C8E6, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x41C910, &ThePaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41C92A, &ThePaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41C954, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C969, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41C994, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41C9A9, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41C9C6, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41C9CC, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41C9D6, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41C9DC, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41CAB5, &ThePaths, true);
        WriteMemory(0x41CB25, &ThePaths, true);
        WriteMemory(0x41CBB9, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41CBC9, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41CBE9, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41CBF7, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41CC27, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41CC3C, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41CC67, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41CC7C, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41CD85, &ThePaths, true);
        WriteMemory(0x41CDE5, &ThePaths, true);
        WriteMemory(0x41CE65, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41CE76, &ThePaths.m_connections, true);
        WriteMemory(0x41CE87, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x41CEAD, &ThePaths.m_carPathLinks->numLeftLanes, true);
        WriteMemory(0x41CEC7, &ThePaths.m_carPathLinks->numRightLanes, true);
        WriteMemory(0x41CEF1, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41CF06, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41CF31, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41CF46, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41CF63, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41CF69, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41CF73, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41CF79, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41D031, &ThePaths, true);
        WriteMemory(0x41D0A5, &ThePaths, true);
        WriteMemory(0x41D139, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41D149, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41D169, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41D177, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41D1A7, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41D1BC, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41D1E7, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41D1FC, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41E391, &ThePaths, true);
        WriteMemory(0x41E3B2, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41E3CF, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41E401, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41E40F, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41E470, &ThePaths, true);
        WriteMemory(0x41E4FD, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41E50D, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41E51B, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41E529, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41E697, &ThePaths, true);
        WriteMemory(0x41E71D, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41E72F, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41E775, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41E78A, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41E7B5, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x41E7CA, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x41E7F0, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41E804, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41EA91, &ThePaths, true);
        WriteMemory(0x41EB1A, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x41EB2C, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x41F85E, &ThePaths, true);
        WriteMemory(0x41F8A2, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41F8CA, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41F8D7, &ThePaths.m_connections, true);
        WriteMemory(0x41F8E2, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41F8E8, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41F8F2, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41F8F8, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41F970, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41F979, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x41F981, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41F987, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x41FA1F, &ThePaths, true);
        WriteMemory(0x41FA71, &ThePaths, true);
        WriteMemory(0x41FA9F, &ThePaths, true);
        WriteMemory(0x41FAC4, &ThePaths, true);
        WriteMemory(0x41FB53, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41FB60, &ThePaths.m_connections, true);
        WriteMemory(0x41FB78, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41FB85, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x41FBBA, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41FBC4, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41FBCE, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x41FBF4, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x41FBFE, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41FC08, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x41FC28, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x41FC32, &ThePaths.m_connections, true);
        WriteMemory(0x41FEAA, &ThePaths, true);
        WriteMemory(0x420096, &ThePaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4200AC, &ThePaths.m_pathNodes->pos.z, true);
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
        WriteMemory(0x42E264, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x42E27B, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x42E285, &ThePaths.m_connections, true);
        WriteMemory(0x42E296, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x42E2A0, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x42E2AB, &ThePaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x42E2D9, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x42E2EC, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x42E2F6, &ThePaths.m_connections, true);
        WriteMemory(0x42E305, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x42E30F, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x42E31A, &ThePaths.m_carPathLinks->trafficLightType, true);
        //0x42E63E                                                                                       
        //0x42E659                                                                                       
        WriteMemory(0x436344, &ThePaths, true);
        WriteMemory(0x43636B, &ThePaths, true);
        WriteMemory(0x4365FD, &ThePaths, true);
        WriteMemory(0x436622, &ThePaths, true);
        WriteMemory(0x436F53, &ThePaths.m_numMapObjects, true);
        WriteMemory(0x436F67, &ThePaths.m_objectFlags, true);
        WriteMemory(0x437044, &ThePaths.m_mapObjects, true);
        WriteMemory(0x437358, &ThePaths.m_objectFlags, true);
        WriteMemory(0x442554, &ThePaths, true);
        WriteMemory(0x44262F, &ThePaths, true);
        WriteMemory(0x443C12, &ThePaths, true);
        WriteMemory(0x443CD6, &ThePaths, true);
        WriteMemory(0x4459CD, &ThePaths, true);
        WriteMemory(0x4459FD, &ThePaths, true);
        WriteMemory(0x445AC3, &ThePaths, true);
        WriteMemory(0x445AF3, &ThePaths, true);
        WriteMemory(0x44D99A, &ThePaths, true);
        WriteMemory(0x44D9F4, &ThePaths, true);
        WriteMemory(0x44DA4E, &ThePaths, true);
        WriteMemory(0x44DAA8, &ThePaths, true);
        WriteMemory(0x44F393, &ThePaths, true);
        WriteMemory(0x44F3AB, &ThePaths, true);
        WriteMemory(0x44F3C0, &ThePaths, true);
        WriteMemory(0x454FCE, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x454FDC, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x45505A, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x455063, &ThePaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4550AF, &ThePaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x4550B4, &ThePaths.m_numPathNodes, true);
        WriteMemory(0x4550D3, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x4550E9, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x4550F4, &ThePaths.m_carPathConnections, true);
        WriteMemory(0x45512F, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x455135, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x455144, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x45514E, &ThePaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455160, &ThePaths.m_numCarPathLinks, true);
        WriteMemory(0x455171, &ThePaths.m_numCarPathNodes, true);
        WriteMemory(0x45518D, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4551B6, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x455206, &ThePaths.m_pathNodes->firstLink, true);
        WriteMemory(0x455210, &ThePaths.m_connectionFlags, true);
        WriteMemory(0x455224, &ThePaths.m_connections, true);
        WriteMemory(0x455231, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x45525C, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4552A5, &ThePaths.m_connectionFlags, true);
        WriteMemory(0x4552AE, &ThePaths.m_pathNodes->numLinks, true);
        WriteMemory(0x4552C7, &ThePaths.m_numPathNodes, true);
        WriteMemory(0x45536D, &ThePaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455389, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x4553A0, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x4553D2, &ThePaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455410, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x455416, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x45541E, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x455424, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4554A2, &ThePaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x4554BE, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x4554D5, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x455507, &ThePaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455545, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x45554B, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x455553, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x455559, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x4555E4, &ThePaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455600, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x455617, &ThePaths.m_carPathLinks->pathNodeIndex, true);
        WriteMemory(0x455649, &ThePaths.m_carPathLinks->trafficLightType, true);
        WriteMemory(0x455687, &ThePaths.m_carPathLinks->pos.y, true);
        WriteMemory(0x45568D, &ThePaths.m_carPathLinks->dir.y, true);
        WriteMemory(0x455695, &ThePaths.m_carPathLinks->pos.x, true);
        WriteMemory(0x45569B, &ThePaths.m_carPathLinks->dir.x, true);
        WriteMemory(0x456470, &ThePaths.m_carPathLinks->trafficLightType + 0x1, true); // flags
        WriteMemory(0x456484, &ThePaths.m_carPathLinks->trafficLightType + 0x1, true); // flags
        WriteMemory(0x476E2F, &ThePaths, true);
        WriteMemory(0x477FD6, &ThePaths, true);
        WriteMemory(0x4780C4, &ThePaths, true);
        WriteMemory(0x4788FD, &ThePaths, true);
        WriteMemory(0x48BFB6, &ThePaths, true);
        WriteMemory(0x48BFC0, &ThePaths, true);
        WriteMemory(0x48C06F, &ThePaths, true);
        WriteMemory(0x48C62B, &ThePaths, true);
        WriteMemory(0x48C671, &ThePaths, true);
        WriteMemory(0x490F50, &ThePaths, true);
        WriteMemory(0x490FA4, &ThePaths.m_pathNodes->pos.z, true);
        WriteMemory(0x490FAC, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x490FB4, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x49FE6B, &ThePaths, true);
        WriteMemory(0x4B40E7, &ThePaths, true);
        WriteMemory(0x4B410B, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4B4115, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4B4125, &ThePaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4B41FF, &ThePaths, true);
        WriteMemory(0x4B4223, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4B422D, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4B423D, &ThePaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4C22F8, &ThePaths.m_mapObjects, true);
        WriteMemory(0x4C7361, &ThePaths, true);
        WriteMemory(0x4C9B3B, &ThePaths, true);
        WriteMemory(0x4C9C07, &ThePaths, true);
        WriteMemory(0x4C9E49, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4C9E53, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4C9F26, &ThePaths, true);
        WriteMemory(0x4C9F3E, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4C9F44, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4C9F67, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4C9F81, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4D2154, &ThePaths, true);
        WriteMemory(0x4D280A, &ThePaths, true);
        WriteMemory(0x4D2874, &ThePaths, true);
        WriteMemory(0x4D29FF, &ThePaths, true);
        WriteMemory(0x4D2ABB, &ThePaths, true);
        WriteMemory(0x4D2B1F, &ThePaths, true);
        WriteMemory(0x4D2B4D, &ThePaths, true);
        WriteMemory(0x4DAF13, &ThePaths, true);
        WriteMemory(0x4DAF4E, &ThePaths, true);
        WriteMemory(0x4DAFED, &ThePaths.m_pathNodes->pos.z, true);
        WriteMemory(0x4DAFF7, &ThePaths.m_pathNodes->pos.y, true);
        WriteMemory(0x4DAFFF, &ThePaths.m_pathNodes->pos.x, true);
        WriteMemory(0x4E3ACA, &ThePaths, true);
        WriteMemory(0x4E3B70, &ThePaths, true);
        WriteMemory(0x4E3BBC, &ThePaths.m_connections, true);
        WriteMemory(0x4E3BC5, &ThePaths, true);
        WriteMemory(0x4E3C81, &ThePaths.m_connections, true);
        WriteMemory(0x4E3C8A, &ThePaths, true);
        WriteMemory(0x4E3D4A, &ThePaths.m_connections, true);
        WriteMemory(0x4E3D53, &ThePaths, true);
        WriteMemory(0x4F4E02, &ThePaths, true);
        WriteMemory(0x589268, &ThePaths, true);
        WriteMemory(0x589327, &ThePaths, true);
        WriteMemory(0x58A95E, &ThePaths, true);
        WriteMemory(0x58A995, &ThePaths, true);
        WriteMemory(0x58A9AA, &ThePaths, true);
        WriteMemory(0x58AAA4, &ThePaths, true);
        WriteMemory(0x58AABB, &ThePaths, true);
        WriteMemory(0x58AAD0, &ThePaths, true);
        WriteMemory(0x58FF21, &ThePaths, true);
        WriteMemory(0x591096, &ThePaths, true);

        MakeCALL(0x48BFBA, PathFindWrappers::Init);
        MakeCALL(0x48C62F, PathFindWrappers::Init);
        MakeCALL(0x478902, PathFindWrappers::RegisterMapObject);
        MakeCALL(0x48C076, PathFindWrappers::PreparePathData);
        MakeCALL(0x48C675, PathFindWrappers::PreparePathData);
        MakeCALL(0x41C670, PathFindWrappers::DoPathSearch);
        MakeCALL(0x41CDAD, PathFindWrappers::DoPathSearch);
        MakeCALL(0x41FA5F, PathFindWrappers::DoPathSearch);
        MakeCALL(0x41FA7F, PathFindWrappers::RemoveBadStartNode);
        MakeCALL(0x4C9B72, PathFindWrappers::FindNextNodeWandering);
        MakeCALL(0x4D2163, PathFindWrappers::FindNextNodeWandering);
        MakeCALL(0x4D2819, PathFindWrappers::FindNextNodeWandering);
        MakeCALL(0x4D2883, PathFindWrappers::FindNextNodeWandering);
        MakeCALL(0x4D2A30, PathFindWrappers::FindNextNodeWandering);
        MakeCALL(0x4D2AC9, PathFindWrappers::FindNextNodeWandering);
        MakeCALL(0x416B4E, PathFindWrappers::NewGenerateCarCreationCoors);
        MakeCALL(0x41FED1, PathFindWrappers::NewGenerateCarCreationCoors);
        MakeCALL(0x4F4E3C, PathFindWrappers::GeneratePedCreationCoors);
        MakeCALL(0x416BC9, PathFindWrappers::TestCoorsCloseness);
        MakeCALL(0x49FE6F, PathFindWrappers::CalcRoadDensity);
        MakeCALL(0x58AAAF, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x58A989, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x4E3AE2, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x4DAF34, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x4C9C2C, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x4B4217, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x4B40FF, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x490F60, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x44F39E, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x445AEA, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x4459F4, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x436615, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x43635E, PathFindWrappers::FindNodeClosestToCoors);
        MakeCALL(0x41F889, PathFindWrappers::FindNodeClosestToCoorsFavourDirection);
        MakeCALL(0x44F3D2, PathFindWrappers::FindNodeOrientationForCarPlacement);
        MakeCALL(0x58A9C7, PathFindWrappers::FindNodeOrientationForCarPlacementFacingDestination);
        MakeCALL(0x58AAF3, PathFindWrappers::FindNodeOrientationForCarPlacementFacingDestination);
        MakeCALL(0x48BFC9, PathFindWrappers::AllocatePathFindInfoMem);
        MakeCALL(0x476E3D, PathFindWrappers::AllocatePathFindInfoMem);
#ifndef FIX_BUGS
        MakeCALL(0x4780C9, PathFindWrappers::StoreNodeInfoCar);
#endif
        MakeCALL(0x477FDB, PathFindWrappers::StoreNodeInfoPed);
        MakeCALL(0x44265A, PathFindWrappers::SwitchRoadsOffInArea);
        MakeCALL(0x44257D, PathFindWrappers::SwitchRoadsOffInArea);
        MakeCALL(0x443D01, PathFindWrappers::SwitchPedRoadsOffInArea);
        MakeCALL(0x443C3D, PathFindWrappers::SwitchPedRoadsOffInArea);
        MakeCALL(0x44DADA, PathFindWrappers::SwitchRoadsInAngledArea);
        MakeCALL(0x44DA80, PathFindWrappers::SwitchRoadsInAngledArea);
        MakeCALL(0x44DA26, PathFindWrappers::SwitchRoadsInAngledArea);
        MakeCALL(0x44D9CC, PathFindWrappers::SwitchRoadsInAngledArea);
        MakeCALL(0x42DF32, PathFindWrappers::SwitchOffNodeAndNeighbours);
        MakeCALL(0x42DE64, PathFindWrappers::SwitchOffNodeAndNeighbours);
        MakeCALL(0x42DB01, PathFindWrappers::SwitchOffNodeAndNeighbours);
        MakeCALL(0x42DA05, PathFindWrappers::SwitchOffNodeAndNeighbours);
        MakeCALL(0x589293, PathFindWrappers::MarkRoadsBetweenLevelsInArea);
        MakeCALL(0x589352, PathFindWrappers::PedMarkRoadsBetweenLevelsInArea);
        MakeCALL(0x4D2B23, PathFindWrappers::TestForPedTrafficLight);
        MakeCALL(0x4D2B53, PathFindWrappers::TestCrossesRoad);
        MakeCALL(0x4C7367, PathFindWrappers::TestCrossesRoad);
        MakeCALL(0x413D07, PathFindWrappers::SetLinksBridgeLights);
        MakeCALL(0x413AAC, PathFindWrappers::SetLinksBridgeLights);
        MakeCALL(0x58FF27, PathFindWrappers::Save);
        MakeCALL(0x59109A, PathFindWrappers::Load);
    };
} PathsIII;



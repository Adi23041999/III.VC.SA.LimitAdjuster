/*
* Copyright (c) re3
*/

#pragma once

#ifdef GTA3
#include "stdint.h"
#include "CVector.h"
#include "CVector2D.h"
#include "CMatrix.h"
#include "CBuilding.h"
#include "OLACommon.h"

// Defaults
//{
//	NUM_PATHNODES = 4930,
//	NUM_CARPATHLINKS = 2076,
//	NUM_MAPOBJECTS = 1250,
//	NUM_PATHCONNECTIONS = 10260,
//	PATHNODESIZE = 4500,
//	NODESTOBECLEARED = 4995,
//	NUMTEMPNODES = 4000,
//	NUMDETACHED_CARS = 100,
//	NUMDETACHED_PEDS = 50,
//};

enum
{
	NUM_PATHNODES = INT16_MAX,
	NUM_CARPATHLINKS = INT16_MAX,
	NUM_MAPOBJECTS = INT16_MAX,
	NUM_PATHCONNECTIONS = INT16_MAX,
	PATHNODESIZE = INT16_MAX,
	NODESTOBECLEARED = INT16_MAX,
	NUMTEMPNODES = INT16_MAX,
	NUMDETACHED_CARS = 100,
	NUMDETACHED_PEDS = 50,
};

class CTreadableRe : public CBuilding
{
public:
	int16_t m_nodeIndices[2][12];	// first car, then ped
};

class CPhysical;

enum
{
	NodeTypeExtern = 1,
	NodeTypeIntern = 2,

	UseInRoadBlock = 1,
	ObjectEastWest = 2,
};

enum
{
	SWITCH_OFF = 0,
	SWITCH_ON = 1,
};

enum
{
	ROUTE_ADD_BLOCKADE = 0,
	ROUTE_NO_BLOCKADE = 1
};

struct CPedPathNodeRe
{
	bool bBlockade;
	uint8 nodeIdX;
	uint8 nodeIdY;
	int16 id;
	CPedPathNodeRe* prev;
	CPedPathNodeRe* next;
};

struct CPathNodeRe
{
	CVector pos;
	CPathNodeRe* prev;
	CPathNodeRe* next;
	int16 distance;		// in path search
	int16 objectIndex;
	int16 firstLink;
	uint8 numLinks;

	uint8 unkBits : 2;
	uint8 bDeadEnd : 1;
	uint8 bDisabled : 1;
	uint8 bBetweenLevels : 1;

	int8 group;

	CVector& GetPosition(void) { return pos; }
	void SetPosition(const CVector& p) { pos = p; }
	float GetX(void) { return pos.x; }
	float GetY(void) { return pos.y; }
	float GetZ(void) { return pos.z; }

	CPathNodeRe* GetPrev(void) { return prev; }
	CPathNodeRe* GetNext(void) { return next; }
	void SetPrev(CPathNodeRe* node) { prev = node; }
	void SetNext(CPathNodeRe* node) { next = node; }
};

union CConnectionFlagsRe
{
	uint8 flags;
	struct {
		uint8 bCrossesRoad : 1;
		uint8 bTrafficLight : 1;
	};
};

enum
{
	// flags read from path definitions

	// m_carPathLinks
	FLAG_BLOCK_ONE_WAY_ROAD_SWITCH = 1 << 0,

	// m_connectionFlags
	FLAG_CROSSES_ROAD = 1 << 0,
};

struct CCarPathLinkRe
{
	CVector2D pos;
	CVector2D dir;
	int16 pathNodeIndex;
	int8 numLeftLanes;
	int8 numRightLanes;
	uint8 trafficLightType;

	uint8 bBridgeLights : 1;
	uint8 bBlockOneWayRoadSwitch : 1;
	// more?

	CVector2D& GetPosition(void) { return pos; }
	CVector2D& GetDirection(void) { return dir; }
	float GetX(void) { return pos.x; }
	float GetY(void) { return pos.y; }
	float GetDirX(void) { return dir.x; }
	float GetDirY(void) { return dir.y; }

	float OneWayLaneOffset()
	{
		if (numLeftLanes == 0)
			return 0.5f - 0.5f * numRightLanes;
		if (numRightLanes == 0)
			return 0.5f - 0.5f * numLeftLanes;
		return 0.5f;
	}
};

// This is what we're reading from the files, only temporary
struct CPathInfoForObjectRe
{
	int16 x;
	int16 y;
	int16 z;
	int8 type;
	int8 next;
	int8 numLeftLanes;
	int8 numRightLanes;
	uint8 flags;
};
extern CPathInfoForObjectRe* NewInfoForTileCars;
extern CPathInfoForObjectRe* NewInfoForTilePeds;

struct CTempNodeRe
{
	CVector pos;
	float dirX;
	float dirY;
	int16 link1;
	int16 link2;
	int8 numLeftLanes;
	int8 numRightLanes;
	int8 linkState;
	uint8 blockOneWayRoadSwitch : 1;
};

struct CTempDetachedNodeRe	// unused
{
	uint8 foo[20];
};

class CPathFindRe
{
public:
	CPathNodeRe m_pathNodes[NUM_PATHNODES];
	CCarPathLinkRe m_carPathLinks[NUM_CARPATHLINKS];
	CTreadableRe* m_mapObjects[NUM_MAPOBJECTS];
	uint8 m_objectFlags[NUM_MAPOBJECTS];
	int16 m_connections[NUM_PATHCONNECTIONS];
	int16 m_distances[NUM_PATHCONNECTIONS];
	CConnectionFlagsRe m_connectionFlags[NUM_PATHCONNECTIONS];
	int16 m_carPathConnections[NUM_PATHCONNECTIONS];

	int32 m_numPathNodes;
	int32 m_numCarPathNodes;
	int32 m_numPedPathNodes;
	int16 m_numMapObjects;
	int16 m_numConnections;
	int32 m_numCarPathLinks;
	int32 unk;
	uint8 m_numGroups[2];
	CPathNodeRe m_searchNodes[512];

	void Init(void);
	void AllocatePathFindInfoMem(int16 numPathGroups);
	void RegisterMapObject(CTreadableRe* mapObject);
	void StoreNodeInfoPed(int16 id, int16 node, int8 type, int8 next, int16 x, int16 y, int16 z, int16 width, bool crossing);
	void StoreNodeInfoCar(int16 id, int16 node, int8 type, int8 next, int16 x, int16 y, int16 z, int16 width, int8 numLeft, int8 numRight, uint8 flags);
	void CalcNodeCoors(int16 x, int16 y, int16 z, int32 id, CVector* out);
	bool LoadPathFindData(void);
	void PreparePathData(void);
	void CountFloodFillGroups(uint8 type);
	void PreparePathDataForType(uint8 type, CTempNodeRe* tempnodes, CPathInfoForObjectRe* objectpathinfo,
		float maxdist, CTempDetachedNodeRe* detachednodes, int32 numDetached);

	bool IsPathObject(int id) { return id < PATHNODESIZE && (NewInfoForTileCars[id * 12].type != 0 || NewInfoForTilePeds[id * 12].type != 0); }

	float CalcRoadDensity(float x, float y);
	bool TestForPedTrafficLight(CPathNodeRe* n1, CPathNodeRe* n2);
	bool TestCrossesRoad(CPathNodeRe* n1, CPathNodeRe* n2);
	void AddNodeToList(CPathNodeRe* node, int32 listId);
	void RemoveNodeFromList(CPathNodeRe* node);
	void RemoveBadStartNode(CVector pos, CPathNodeRe** nodes, int16* n);
	void SetLinksBridgeLights(float, float, float, float, bool);
	void SwitchOffNodeAndNeighbours(int32 nodeId, bool disable);
	void SwitchRoadsOffInArea(float x1, float x2, float y1, float y2, float z1, float z2, bool disable);
	void SwitchPedRoadsOffInArea(float x1, float x2, float y1, float y2, float z1, float z2, bool disable);
	void SwitchRoadsInAngledArea(float x1, float y1, float z1, float x2, float y2, float z2, float length, uint8 type, uint8 enable);
	void MarkRoadsBetweenLevelsNodeAndNeighbours(int32 nodeId);
	void MarkRoadsBetweenLevelsInArea(float x1, float x2, float y1, float y2, float z1, float z2);
	void PedMarkRoadsBetweenLevelsInArea(float x1, float x2, float y1, float y2, float z1, float z2);
	int32 FindNodeClosestToCoors(CVector coors, uint8 type, float distLimit, bool ignoreDisabled = false, bool ignoreBetweenLevels = false);
	int32 FindNodeClosestToCoorsFavourDirection(CVector coors, uint8 type, float dirX, float dirY);
	float FindNodeOrientationForCarPlacement(int32 nodeId);
	float FindNodeOrientationForCarPlacementFacingDestination(int32 nodeId, float x, float y, bool towards);
	bool NewGenerateCarCreationCoors(float x, float y, float dirX, float dirY, float spawnDist, float angleLimit, bool forward, CVector* pPosition, int32* pNode1, int32* pNode2, float* pPositionBetweenNodes, bool ignoreDisabled = false);
	bool GeneratePedCreationCoors(float x, float y, float minDist, float maxDist, float minDistOffScreen, float maxDistOffScreen, CVector* pPosition, int32* pNode1, int32* pNode2, float* pPositionBetweenNodes, CMatrix* camMatrix);
	CTreadableRe* FindRoadObjectClosestToCoors(CVector coors, uint8 type);
	void FindNextNodeWandering(uint8, CVector, CPathNodeRe**, CPathNodeRe**, uint8, uint8*);
	void DoPathSearch(uint8 type, CVector start, int32 startNodeId, CVector target, CPathNodeRe** nodes, int16* numNodes, int16 maxNumNodes, CPhysical* vehicle, float* dist, float distLimit, int32 forcedTargetNode);
	bool TestCoorsCloseness(CVector target, uint8 type, CVector start);
	void Save(uint8* buf, uint32* size);
	void Load(uint8* buf, uint32 size);
	uint16 ConnectedNode(int id) { return m_connections[id]; }
	bool ConnectionCrossesRoad(int id) { return m_connectionFlags[id].bCrossesRoad; }
	bool ConnectionHasTrafficLight(int id) { return m_connectionFlags[id].bTrafficLight; }
	void ConnectionSetTrafficLight(int id) { m_connectionFlags[id].bTrafficLight = true; }

	//void DisplayPathData(void);
};

extern CPathFindRe TheNewPaths;

//extern bool gbShowPedPaths;
//extern bool gbShowCarPaths;
//extern bool gbShowCarPathsLinks;

#endif // GTA3
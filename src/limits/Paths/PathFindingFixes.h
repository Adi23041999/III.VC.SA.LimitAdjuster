#pragma once

#if GTA3
#ifdef FIX_BUGS
#include "PathFindIII.h"
#include "CCarCtrl.h"
#include "CCurves.h"
#include "CGeneral.h"

#define PATH_DIRECTION_NONE 0
#define PATH_DIRECTION_STRAIGHT 1
#define PATH_DIRECTION_RIGHT 2
#define PATH_DIRECTION_LEFT 4
#define ATTEMPTS_TO_FIND_NEXT_NODE 15
#define LANE_WIDTH 5.0f

class CAutoPilotRe {
public:
	int32 m_nCurrentRouteNode;
	int32 m_nNextRouteNode;
	int32 m_nPrevRouteNode;
	int32 m_nTimeEnteredCurve;
	int32 m_nTimeToSpendOnCurrentCurve;
	uint32 m_nCurrentPathNodeInfo;
	uint32 m_nNextPathNodeInfo;
	uint32 m_nPreviousPathNodeInfo;
	uint32 m_nAntiReverseTimer;
	uint32 m_nTimeToStartMission;
	int8 m_nPreviousDirection;
	int8 m_nCurrentDirection;
	int8 m_nNextDirection;
	int8 m_nCurrentLane;
	int8 m_nNextLane;
	uint8 m_nDrivingStyle;
	uint8 m_nCarMission;
	uint8 m_nTempAction;
	uint32 m_nTimeTempAction;
	float m_fMaxTrafficSpeed;
	uint8 m_nCruiseSpeed;
	uint8 m_bSlowedDownBecauseOfCars : 1;
	uint8 m_bSlowedDownBecauseOfPeds : 1;
	uint8 m_bStayInCurrentLevel : 1;
	uint8 m_bStayInFastLane : 1;
	uint8 m_bIgnorePathfinding : 1;
	CVector m_vecDestinationCoors;
	CPathNodeRe* m_aPathFindNodesInfo[/*NUM_PATH_NODES_IN_m_autoPilot*/8];
	int16 m_nPathFindNodesCount;
	CVehicle* m_pTargetCar;
};

namespace PathFindingFixes
{
static void __cdecl LoadCarPathNode(const char* line, int id, int node)
{
	int type, next, flags, numLeft, numRight;
	float x, y, z, width;

	sscanf(line, "%d %d %d %f %f %f %f %d %d", &type, &next, &flags, &x, &y, &z, &width, &numLeft, &numRight);
	TheNewPaths.StoreNodeInfoCar(id, node, type, next, (int16)x, (int16)y, (int16)z, 0, numLeft, numRight, flags);
}

static void __cdecl PickNextNodeRandomly(CVehicle* pVehicle)
{
	//using namespace CCarCtrl;
	CAutoPilotRe& m_autoPilot = (CAutoPilotRe&)pVehicle->m_autoPilot;
	int32 prevNode = m_autoPilot.m_nCurrentRouteNode;
	int32 curNode = m_autoPilot.m_nNextRouteNode;
	uint8 totalLinks = TheNewPaths.m_pathNodes[curNode].numLinks;
	CCarPathLinkRe* pCurLink = &TheNewPaths.m_carPathLinks[m_autoPilot.m_nNextPathNodeInfo];
	uint8 lanesOnCurrentPath;
	bool isOnOneWayRoad;
	if (pCurLink->pathNodeIndex == curNode) {
		lanesOnCurrentPath = pCurLink->numLeftLanes;
		isOnOneWayRoad = pCurLink->numRightLanes == 0 && pCurLink->bBlockOneWayRoadSwitch;
	}
	else {
		lanesOnCurrentPath = pCurLink->numRightLanes;
		isOnOneWayRoad = pCurLink->numLeftLanes == 0 && pCurLink->bBlockOneWayRoadSwitch;
	}
	uint8 allowedDirections = PATH_DIRECTION_NONE;
	uint8 nextLane = m_autoPilot.m_nNextLane;
	if (nextLane == 0)
		/* We are always allowed to turn left from  leftmost lane */
		allowedDirections |= PATH_DIRECTION_LEFT;
	if (nextLane == lanesOnCurrentPath - 1)
		/* We are always allowed to turn right from rightmost lane */
		allowedDirections |= PATH_DIRECTION_RIGHT;
	if (lanesOnCurrentPath < 3 || allowedDirections == PATH_DIRECTION_NONE)
		/* We are always allowed to go straight on one/two-laned road */
		/* or if we are in one of middle lanes of the road */
		allowedDirections |= PATH_DIRECTION_STRAIGHT;
	int attempt;
	m_autoPilot.m_nPrevRouteNode = m_autoPilot.m_nCurrentRouteNode;
	m_autoPilot.m_nCurrentRouteNode = m_autoPilot.m_nNextRouteNode;
	CPathNodeRe* pPrevPathNode = &TheNewPaths.m_pathNodes[prevNode];
	CPathNodeRe* pCurPathNode = &TheNewPaths.m_pathNodes[curNode];
	int16 nextLink;
	CCarPathLinkRe* pNextLink;
	CPathNodeRe* pNextPathNode;
	bool goingAgainstOneWayRoad;
	bool nextNodeIsOneWayRoad;
	uint8 direction;
	for (attempt = 0; attempt < ATTEMPTS_TO_FIND_NEXT_NODE; attempt++) {
		if (attempt != 0) {
			if (m_autoPilot.m_nNextRouteNode != prevNode) {
				if (direction & allowedDirections) {
					pNextPathNode = &TheNewPaths.m_pathNodes[m_autoPilot.m_nNextRouteNode];
					if ((!pNextPathNode->bDeadEnd || pPrevPathNode->bDeadEnd) &&
						(!pNextPathNode->bDisabled || pPrevPathNode->bDisabled) &&
						(!pNextPathNode->bBetweenLevels || pPrevPathNode->bBetweenLevels || !m_autoPilot.m_bStayInCurrentLevel) &&
						!goingAgainstOneWayRoad && (!isOnOneWayRoad || !nextNodeIsOneWayRoad))
						break;
				}
			}
		}
		nextLink = OLA::GetRandomNumber() % totalLinks;
		m_autoPilot.m_nNextRouteNode = TheNewPaths.ConnectedNode(nextLink + pCurPathNode->firstLink);
		direction = CCarCtrl::FindPathDirection(prevNode, curNode, m_autoPilot.m_nNextRouteNode);
		pNextLink = &TheNewPaths.m_carPathLinks[TheNewPaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
		goingAgainstOneWayRoad = pNextLink->pathNodeIndex == curNode ? pNextLink->numRightLanes == 0 : pNextLink->numLeftLanes == 0;
		nextNodeIsOneWayRoad = pNextLink->pathNodeIndex == curNode ? pNextLink->numLeftLanes == 0 : pNextLink->numRightLanes == 0;
	}
	if (attempt >= ATTEMPTS_TO_FIND_NEXT_NODE) {
		/* If we failed 15 times, then remove dead end, one way road and current lane limitations */
		for (attempt = 0; attempt < ATTEMPTS_TO_FIND_NEXT_NODE; attempt++) {
			if (attempt != 0) {
				if (m_autoPilot.m_nNextRouteNode != prevNode) {
					pNextPathNode = &TheNewPaths.m_pathNodes[m_autoPilot.m_nNextRouteNode];
					if ((!pNextPathNode->bDisabled || pPrevPathNode->bDisabled) &&
						(!pNextPathNode->bBetweenLevels || pPrevPathNode->bBetweenLevels || !m_autoPilot.m_bStayInCurrentLevel) &&
						!goingAgainstOneWayRoad)
						break;
				}
			}
			nextLink = OLA::GetRandomNumber() % totalLinks;
			m_autoPilot.m_nNextRouteNode = TheNewPaths.ConnectedNode(nextLink + pCurPathNode->firstLink);
			pNextLink = &TheNewPaths.m_carPathLinks[TheNewPaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
			goingAgainstOneWayRoad = pNextLink->pathNodeIndex == curNode ? pNextLink->numRightLanes == 0 : pNextLink->numLeftLanes == 0;
		}
	}
	if (attempt >= ATTEMPTS_TO_FIND_NEXT_NODE) {
		/* If we failed again, remove no U-turn limitation and remove randomness */
		for (nextLink = 0; nextLink < totalLinks; nextLink++) {
			m_autoPilot.m_nNextRouteNode = TheNewPaths.ConnectedNode(nextLink + pCurPathNode->firstLink);
			pNextLink = &TheNewPaths.m_carPathLinks[TheNewPaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
			goingAgainstOneWayRoad = pNextLink->pathNodeIndex == curNode ? pNextLink->numRightLanes == 0 : pNextLink->numLeftLanes == 0;
			if (!goingAgainstOneWayRoad) {
				pNextPathNode = &TheNewPaths.m_pathNodes[m_autoPilot.m_nNextRouteNode];
				if ((!pNextPathNode->bDisabled || pPrevPathNode->bDisabled) &&
					(!pNextPathNode->bBetweenLevels || pPrevPathNode->bBetweenLevels || !m_autoPilot.m_bStayInCurrentLevel))
					/* Nice way to exit loop but this will fail because this is used for indexing! */
					nextLink = 1000;
			}
		}
		if (nextLink < 999)
			/* If everything else failed, turn vehicle around */
			m_autoPilot.m_nNextRouteNode = prevNode;
	}
	pNextPathNode = &TheNewPaths.m_pathNodes[m_autoPilot.m_nNextRouteNode];
	pNextLink = &TheNewPaths.m_carPathLinks[TheNewPaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
	if (prevNode == m_autoPilot.m_nNextRouteNode) {
		/* We can no longer shift vehicle without physics if we have to turn it around. */
		pVehicle->m_nStatus = STATUS_PHYSICS;
		CCarCtrl::SwitchVehicleToRealPhysics(pVehicle);
	}
	m_autoPilot.m_nTimeEnteredCurve += m_autoPilot.m_nTimeToSpendOnCurrentCurve;
	m_autoPilot.m_nPreviousPathNodeInfo = m_autoPilot.m_nCurrentPathNodeInfo;
	m_autoPilot.m_nCurrentPathNodeInfo = m_autoPilot.m_nNextPathNodeInfo;
	m_autoPilot.m_nPreviousDirection = m_autoPilot.m_nCurrentDirection;
	m_autoPilot.m_nCurrentDirection = m_autoPilot.m_nNextDirection;
	m_autoPilot.m_nCurrentLane = m_autoPilot.m_nNextLane;
	m_autoPilot.m_nNextPathNodeInfo = TheNewPaths.m_carPathConnections[nextLink + pCurPathNode->firstLink];
	int8 lanesOnNextNode;
	if (curNode >= m_autoPilot.m_nNextRouteNode) {
		m_autoPilot.m_nNextDirection = 1;
		lanesOnNextNode = pNextLink->numLeftLanes;
	}
	else {
		m_autoPilot.m_nNextDirection = -1;
		lanesOnNextNode = pNextLink->numRightLanes;
	}
	float currentPathLinkForwardX = m_autoPilot.m_nCurrentDirection * pCurLink->GetDirX();
	float nextPathLinkForwardX = m_autoPilot.m_nNextDirection * pNextLink->GetDirX();
#ifdef FIX_BUGS
	float currentPathLinkForwardY = m_autoPilot.m_nCurrentDirection * pCurLink->GetDirY();
	float nextPathLinkForwardY = m_autoPilot.m_nNextDirection * pNextLink->GetDirY();
#endif
	if (lanesOnNextNode >= 0) {
		if ((OLA::GetRandomNumber() & 0x600) == 0) {
			/* 25% chance vehicle will try to switch lane */
			CVector2D dist = pNextPathNode->GetPosition() - pCurPathNode->GetPosition();
			if (dist.MagnitudeSqr() >= SQR(14.0f)) {
				if (OLA::GetRandomTrueFalse())
					m_autoPilot.m_nNextLane += 1;
				else
					m_autoPilot.m_nNextLane -= 1;
			}
		}
		m_autoPilot.m_nNextLane = Min(lanesOnNextNode - 1, m_autoPilot.m_nNextLane);
		m_autoPilot.m_nNextLane = Max(0, m_autoPilot.m_nNextLane);
	}
	else {
		m_autoPilot.m_nNextLane = m_autoPilot.m_nCurrentLane;
	}
	if (m_autoPilot.m_bStayInFastLane)
		m_autoPilot.m_nNextLane = 0;
	CVector positionOnCurrentLinkIncludingLane(
		pCurLink->GetX() + ((m_autoPilot.m_nCurrentLane + pCurLink->OneWayLaneOffset()) * LANE_WIDTH)
#ifdef FIX_BUGS
		* currentPathLinkForwardY
#endif
		, pCurLink->GetY() - ((m_autoPilot.m_nCurrentLane + pCurLink->OneWayLaneOffset()) * LANE_WIDTH) * currentPathLinkForwardX,
		0.0f);
	CVector positionOnNextLinkIncludingLane(
		pNextLink->GetX() + ((m_autoPilot.m_nNextLane + pNextLink->OneWayLaneOffset()) * LANE_WIDTH)
#ifdef FIX_BUGS
		* nextPathLinkForwardY
#endif
		, pNextLink->GetY() - ((m_autoPilot.m_nNextLane + pNextLink->OneWayLaneOffset()) * LANE_WIDTH) * nextPathLinkForwardX,
		0.0f);
	float directionCurrentLinkX = pCurLink->GetDirX() * m_autoPilot.m_nCurrentDirection;
	float directionCurrentLinkY = pCurLink->GetDirY() * m_autoPilot.m_nCurrentDirection;
	float directionNextLinkX = pNextLink->GetDirX() * m_autoPilot.m_nNextDirection;
	float directionNextLinkY = pNextLink->GetDirY() * m_autoPilot.m_nNextDirection;
	/* We want to make a path between two links that may not have the same forward directions a curve. */
	m_autoPilot.m_nTimeToSpendOnCurrentCurve = CCurves::CalcSpeedScaleFactor(
		&positionOnCurrentLinkIncludingLane,
		&positionOnNextLinkIncludingLane,
		directionCurrentLinkX, directionCurrentLinkY,
		directionNextLinkX, directionNextLinkY
	) * (1000.0f / m_autoPilot.m_fMaxTrafficSpeed);
	if (m_autoPilot.m_nTimeToSpendOnCurrentCurve < 10)
		/* Oh hey there Obbe */
		printf("fout\n");
	m_autoPilot.m_nTimeToSpendOnCurrentCurve = Max(10, m_autoPilot.m_nTimeToSpendOnCurrentCurve);
}
}
#endif // FIX_BUGS
#endif // GTA3

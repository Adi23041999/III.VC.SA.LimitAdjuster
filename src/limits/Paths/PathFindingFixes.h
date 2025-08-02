#pragma once

#ifdef FIX_BUGS
#include "Types/General.h"
#include "Types/Entities.h"
#include "PathFindIII.h"

struct CVehicle;

#define PATH_DIRECTION_NONE 0
#define PATH_DIRECTION_STRAIGHT 1
#define PATH_DIRECTION_RIGHT 2
#define PATH_DIRECTION_LEFT 4
#define ATTEMPTS_TO_FIND_NEXT_NODE 15
#define LANE_WIDTH 5.0f

namespace PathFindingFixes
{
static void __cdecl LoadCarPathNode(const char* line, int id, int node)
{
	int type, next, flags, numLeft, numRight;
	float x, y, z, width;

	sscanf(line, "%d %d %d %f %f %f %f %d %d", &type, &next, &flags, &x, &y, &z, &width, &numLeft, &numRight);
	ThePaths.StoreNodeInfoCar(id, node, type, next, x, y, z, 0, numLeft, numRight, flags);
}

static void __cdecl PickNextNodeRandomly(CVehicle* pVehicle)
{
	using namespace CCarCtrl;
	int32 prevNode = pVehicle->AutoPilot.m_nCurrentRouteNode;
	int32 curNode = pVehicle->AutoPilot.m_nNextRouteNode;
	uint8 totalLinks = ThePaths.m_pathNodes[curNode].numLinks;
	CCarPathLink* pCurLink = &ThePaths.m_carPathLinks[pVehicle->AutoPilot.m_nNextPathNodeInfo];
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
	uint8 nextLane = pVehicle->AutoPilot.m_nNextLane;
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
	pVehicle->AutoPilot.m_nPrevRouteNode = pVehicle->AutoPilot.m_nCurrentRouteNode;
	pVehicle->AutoPilot.m_nCurrentRouteNode = pVehicle->AutoPilot.m_nNextRouteNode;
	CPathNode* pPrevPathNode = &ThePaths.m_pathNodes[prevNode];
	CPathNode* pCurPathNode = &ThePaths.m_pathNodes[curNode];
	int16 nextLink;
	CCarPathLink* pNextLink;
	CPathNode* pNextPathNode;
	bool goingAgainstOneWayRoad;
	bool nextNodeIsOneWayRoad;
	uint8 direction;
	for (attempt = 0; attempt < ATTEMPTS_TO_FIND_NEXT_NODE; attempt++) {
		if (attempt != 0) {
			if (pVehicle->AutoPilot.m_nNextRouteNode != prevNode) {
				if (direction & allowedDirections) {
					pNextPathNode = &ThePaths.m_pathNodes[pVehicle->AutoPilot.m_nNextRouteNode];
					if ((!pNextPathNode->bDeadEnd || pPrevPathNode->bDeadEnd) &&
						(!pNextPathNode->bDisabled || pPrevPathNode->bDisabled) &&
						(!pNextPathNode->bBetweenLevels || pPrevPathNode->bBetweenLevels || !pVehicle->AutoPilot.m_bStayInCurrentLevel) &&
						!goingAgainstOneWayRoad && (!isOnOneWayRoad || !nextNodeIsOneWayRoad))
						break;
				}
			}
		}
		nextLink = CGeneral::GetRandomNumber() % totalLinks;
		pVehicle->AutoPilot.m_nNextRouteNode = ThePaths.ConnectedNode(nextLink + pCurPathNode->firstLink);
		direction = FindPathDirection(prevNode, curNode, pVehicle->AutoPilot.m_nNextRouteNode);
		pNextLink = &ThePaths.m_carPathLinks[ThePaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
		goingAgainstOneWayRoad = pNextLink->pathNodeIndex == curNode ? pNextLink->numRightLanes == 0 : pNextLink->numLeftLanes == 0;
		nextNodeIsOneWayRoad = pNextLink->pathNodeIndex == curNode ? pNextLink->numLeftLanes == 0 : pNextLink->numRightLanes == 0;
	}
	if (attempt >= ATTEMPTS_TO_FIND_NEXT_NODE) {
		/* If we failed 15 times, then remove dead end, one way road and current lane limitations */
		for (attempt = 0; attempt < ATTEMPTS_TO_FIND_NEXT_NODE; attempt++) {
			if (attempt != 0) {
				if (pVehicle->AutoPilot.m_nNextRouteNode != prevNode) {
					pNextPathNode = &ThePaths.m_pathNodes[pVehicle->AutoPilot.m_nNextRouteNode];
					if ((!pNextPathNode->bDisabled || pPrevPathNode->bDisabled) &&
						(!pNextPathNode->bBetweenLevels || pPrevPathNode->bBetweenLevels || !pVehicle->AutoPilot.m_bStayInCurrentLevel) &&
						!goingAgainstOneWayRoad)
						break;
				}
			}
			nextLink = CGeneral::GetRandomNumber() % totalLinks;
			pVehicle->AutoPilot.m_nNextRouteNode = ThePaths.ConnectedNode(nextLink + pCurPathNode->firstLink);
			pNextLink = &ThePaths.m_carPathLinks[ThePaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
			goingAgainstOneWayRoad = pNextLink->pathNodeIndex == curNode ? pNextLink->numRightLanes == 0 : pNextLink->numLeftLanes == 0;
		}
	}
	if (attempt >= ATTEMPTS_TO_FIND_NEXT_NODE) {
		/* If we failed again, remove no U-turn limitation and remove randomness */
		for (nextLink = 0; nextLink < totalLinks; nextLink++) {
			pVehicle->AutoPilot.m_nNextRouteNode = ThePaths.ConnectedNode(nextLink + pCurPathNode->firstLink);
			pNextLink = &ThePaths.m_carPathLinks[ThePaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
			goingAgainstOneWayRoad = pNextLink->pathNodeIndex == curNode ? pNextLink->numRightLanes == 0 : pNextLink->numLeftLanes == 0;
			if (!goingAgainstOneWayRoad) {
				pNextPathNode = &ThePaths.m_pathNodes[pVehicle->AutoPilot.m_nNextRouteNode];
				if ((!pNextPathNode->bDisabled || pPrevPathNode->bDisabled) &&
					(!pNextPathNode->bBetweenLevels || pPrevPathNode->bBetweenLevels || !pVehicle->AutoPilot.m_bStayInCurrentLevel))
					/* Nice way to exit loop but this will fail because this is used for indexing! */
					nextLink = 1000;
			}
		}
		if (nextLink < 999)
			/* If everything else failed, turn vehicle around */
			pVehicle->AutoPilot.m_nNextRouteNode = prevNode;
	}
	pNextPathNode = &ThePaths.m_pathNodes[pVehicle->AutoPilot.m_nNextRouteNode];
	pNextLink = &ThePaths.m_carPathLinks[ThePaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
	if (prevNode == pVehicle->AutoPilot.m_nNextRouteNode) {
		/* We can no longer shift vehicle without physics if we have to turn it around. */
		pVehicle->SetStatus(STATUS_PHYSICS);
		SwitchVehicleToRealPhysics(pVehicle);
	}
	pVehicle->AutoPilot.m_nTimeEnteredCurve += pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve;
	pVehicle->AutoPilot.m_nPreviousPathNodeInfo = pVehicle->AutoPilot.m_nCurrentPathNodeInfo;
	pVehicle->AutoPilot.m_nCurrentPathNodeInfo = pVehicle->AutoPilot.m_nNextPathNodeInfo;
	pVehicle->AutoPilot.m_nPreviousDirection = pVehicle->AutoPilot.m_nCurrentDirection;
	pVehicle->AutoPilot.m_nCurrentDirection = pVehicle->AutoPilot.m_nNextDirection;
	pVehicle->AutoPilot.m_nCurrentLane = pVehicle->AutoPilot.m_nNextLane;
	pVehicle->AutoPilot.m_nNextPathNodeInfo = ThePaths.m_carPathConnections[nextLink + pCurPathNode->firstLink];
	int8 lanesOnNextNode;
	if (curNode >= pVehicle->AutoPilot.m_nNextRouteNode) {
		pVehicle->AutoPilot.m_nNextDirection = 1;
		lanesOnNextNode = pNextLink->numLeftLanes;
	}
	else {
		pVehicle->AutoPilot.m_nNextDirection = -1;
		lanesOnNextNode = pNextLink->numRightLanes;
	}
	float currentPathLinkForwardX = pVehicle->AutoPilot.m_nCurrentDirection * pCurLink->GetDirX();
	float nextPathLinkForwardX = pVehicle->AutoPilot.m_nNextDirection * pNextLink->GetDirX();
#ifdef FIX_BUGS
	float currentPathLinkForwardY = pVehicle->AutoPilot.m_nCurrentDirection * pCurLink->GetDirY();
	float nextPathLinkForwardY = pVehicle->AutoPilot.m_nNextDirection * pNextLink->GetDirY();
#endif
	if (lanesOnNextNode >= 0) {
		if ((CGeneral::GetRandomNumber() & 0x600) == 0) {
			/* 25% chance vehicle will try to switch lane */
			CVector2D dist = pNextPathNode->GetPosition() - pCurPathNode->GetPosition();
			if (dist.MagnitudeSqr() >= SQR(14.0f)) {
				if (CGeneral::GetRandomTrueFalse())
					pVehicle->AutoPilot.m_nNextLane += 1;
				else
					pVehicle->AutoPilot.m_nNextLane -= 1;
			}
		}
		pVehicle->AutoPilot.m_nNextLane = Min(lanesOnNextNode - 1, pVehicle->AutoPilot.m_nNextLane);
		pVehicle->AutoPilot.m_nNextLane = Max(0, pVehicle->AutoPilot.m_nNextLane);
	}
	else {
		pVehicle->AutoPilot.m_nNextLane = pVehicle->AutoPilot.m_nCurrentLane;
	}
	if (pVehicle->AutoPilot.m_bStayInFastLane)
		pVehicle->AutoPilot.m_nNextLane = 0;
	CVector positionOnCurrentLinkIncludingLane(
		pCurLink->GetX() + ((pVehicle->AutoPilot.m_nCurrentLane + pCurLink->OneWayLaneOffset()) * LANE_WIDTH)
#ifdef FIX_BUGS
		* currentPathLinkForwardY
#endif
		, pCurLink->GetY() - ((pVehicle->AutoPilot.m_nCurrentLane + pCurLink->OneWayLaneOffset()) * LANE_WIDTH) * currentPathLinkForwardX,
		0.0f);
	CVector positionOnNextLinkIncludingLane(
		pNextLink->GetX() + ((pVehicle->AutoPilot.m_nNextLane + pNextLink->OneWayLaneOffset()) * LANE_WIDTH)
#ifdef FIX_BUGS
		* nextPathLinkForwardY
#endif
		, pNextLink->GetY() - ((pVehicle->AutoPilot.m_nNextLane + pNextLink->OneWayLaneOffset()) * LANE_WIDTH) * nextPathLinkForwardX,
		0.0f);
	float directionCurrentLinkX = pCurLink->GetDirX() * pVehicle->AutoPilot.m_nCurrentDirection;
	float directionCurrentLinkY = pCurLink->GetDirY() * pVehicle->AutoPilot.m_nCurrentDirection;
	float directionNextLinkX = pNextLink->GetDirX() * pVehicle->AutoPilot.m_nNextDirection;
	float directionNextLinkY = pNextLink->GetDirY() * pVehicle->AutoPilot.m_nNextDirection;
	/* We want to make a path between two links that may not have the same forward directions a curve. */
	pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve = CCurves::CalcSpeedScaleFactor(
		&positionOnCurrentLinkIncludingLane,
		&positionOnNextLinkIncludingLane,
		directionCurrentLinkX, directionCurrentLinkY,
		directionNextLinkX, directionNextLinkY
	) * (1000.0f / pVehicle->AutoPilot.m_fMaxTrafficSpeed);
	if (pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve < 10)
		/* Oh hey there Obbe */
		printf("fout\n");
	pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve = Max(10, pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve);
}
}
#endif // FIX_BUGS

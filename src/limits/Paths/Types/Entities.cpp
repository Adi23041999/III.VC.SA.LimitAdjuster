/*
* Copyright (c) re3
*/

#include "Entities.h"

CCamera::_IsSphereVisible1 CCamera::IsSphereVisible1 = GetBranchDestination(raw_ptr(0x42C5BB)).get();
CCamera::_IsSphereVisible2 CCamera::IsSphereVisible2 = GetBranchDestination(raw_ptr(0x43D2F4)).get();
CWorld::_GetIsLineOfSightClear CWorld::GetIsLineOfSightClear = GetBranchDestination(raw_ptr(0x42BC51)).get();
CWorld::_FindGroundZFor3DCoord CWorld::FindGroundZFor3DCoord = GetBranchDestination(raw_ptr(0x42C68C)).get();
CFileMgr::_SetDir CFileMgr::SetDir = GetBranchDestination(raw_ptr(0x429C0C)).get();
CGeneral::_GetRadianAngleBetweenPoints CGeneral::GetRadianAngleBetweenPoints = GetBranchDestination(raw_ptr(0x42DBB9)).get();
CCollision::_DistToLine CCollision::DistToLine = GetBranchDestination(raw_ptr(0x42D41B)).get();
CCarCtrl::_FindPathDirection CCarCtrl::FindPathDirection = GetBranchDestination(raw_ptr(0x41BC1F)).get();
CCarCtrl::_SwitchVehicleToRealPhysics CCarCtrl::SwitchVehicleToRealPhysics = GetBranchDestination(raw_ptr(0x41BF19)).get();
CCurves::_CalcSpeedScaleFactor CCurves::CalcSpeedScaleFactor = GetBranchDestination(raw_ptr(0x41C2D7)).get();

unsigned long long CGeneral::myrand_seed = 1;
int CGeneral::myrand(void)
{
	// Use our own implementation of rand, stolen from PS2
	myrand_seed = 0x5851F42D4C957F2D * myrand_seed + 1;
	return ((myrand_seed >> 32) & 0x7FFFFFFF);
}

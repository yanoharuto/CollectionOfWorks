#pragma once
#include "DxLib.h"
#include "InputDirection.h"
#include "CheckPoint.h"
#include "AutoDriveInfo.h"
/// <summary>
/// 大雑把な進行方向を決めてくれる
/// </summary>
class DirectionOfTravelGenerator
{
public:
    DirectionOfTravelGenerator();
    ~DirectionOfTravelGenerator();

    static InputInfo GetPlayerDirection(AutoDriveInfo autoDriveParam);
    static InputInfo GetNextPointDirection(AutoDriveInfo autoDriveParam,VECTOR checkPointPos);
private :
    static InputInfo GetDirection(AutoDriveInfo autoDriveParam,VECTOR pos);
};
#pragma once
#include "ConflictProccesor.h"
/// <summary>
/// Y座標を無視しているけど線分の当たり判定
/// </summary>
class LineCollider :
    public ConflictProccesor
{
public:
    //線分の長さは高さと係数によって決める
    LineCollider(Actor* obj,float setLineRange);

    /// <summary>
    /// Y座標を無視しているけど線分の当たり判定
    /// </summary>
    /// <param name="hitCheckInfo">当たってくる奴の情報</param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo)override;
private:
    //線分の長さは高さと係数によって決める
    float lineRange;
};


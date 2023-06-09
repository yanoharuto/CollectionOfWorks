#pragma once
#include "UIDataStruct.h"
#include <string>
/// <summary>
/// UI
/// </summary>
class UI abstract
{
public:
    UI() { uiData = {}; };
    /// <summary>
    /// どの位置に描画するかとか描画したいものとか渡して欲しい
    /// </summary>
    /// <param name="data"></param>
    UI(UIData data) { uiData = data; };
    virtual ~UI() {};
    /// <summary>
    /// 描画
    /// </summary>
    virtual void DrawUI() {};
    /// <summary>
    /// 位置変更
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    void SetXY(int x, int y) { uiData.x = x; uiData.y = y; };
protected:
    //描画場所と描画対象のデータ
    UIData uiData;
};
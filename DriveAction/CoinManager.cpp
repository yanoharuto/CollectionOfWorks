#include "CoinManager.h"
#include "CourceDataLoader.h"
#include "Utility.h"
/// <summary>
/// コインの設置
/// </summary>
CoinManager::CoinManager()
{
    std::list<VECTOR> posList = CourceDataLoader::GetVECTORData(coinPosPass);
    coinFirstNum = posList.size();
    for (auto ite = posList.begin(); ite != posList.end(); ite++)
    {
        Coin* newCoin = new Coin((*ite));
        coinList.push_back(newCoin);
    }
}

CoinManager::~CoinManager()
{
    for (auto ite = coinList.begin(); ite != coinList.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
    coinList.clear();
}
/// <summary>
/// coinPosListの更新と取られたコインの削除
/// </summary>
void CoinManager::Update()
{
    coinPosList.clear();
    auto objIte = coinList.begin();
    std::list<Coin*> brokenList;
    //更新する必要が無くなったら消去
    while (objIte != coinList.end())
    {
        //回転させたり
        (*objIte)->Update();
        if (!(*objIte)->GetAliveFlag()) //もう存在していなかったら更新終了
        {
            //壊すものリストに追加
            brokenList.push_back((*objIte));
            //eraseは消したイテレーターの次の奴を返す
            objIte = coinList.erase(objIte);
        }
        else
        {
            //コインの位置を更新
            coinPosList.push_back((*objIte)->GetPos());
            //消す条件に合わなかったら次
            ++objIte;
        }
    }
    //消していいやつ消す
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
}
/// <summary>
/// コインの描画
/// </summary>
void CoinManager::Draw()
{
    for (auto ite = coinList.begin(); ite != coinList.end(); ite++)
    {
        (*ite)->Draw();
    }
}

/// <summary>
/// コインの位置
/// </summary>
/// <returns></returns>
std::list<VECTOR> CoinManager::GetCoinPosList()
{
    return coinPosList;
}
/// <summary>
/// コインの初期枚数
/// </summary>
/// <returns></returns>
int CoinManager::GetCoinFirstNum()
{
    return coinFirstNum;
}
/// <summary>
/// コインの現在の枚数
/// </summary>
/// <returns></returns>
int CoinManager::GetCoinNowNum()
{
    return coinList.size();
}


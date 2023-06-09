#include "FiringItemManager.h"
#include "Rocket.h"
#include "Utility.h"
#include "ListUtility.h"

//オブジェクトタグがDamageObjectになってるオブジェクトのリスト
std::list<Actor*> FiringItemManager::damageObjList;
FiringItemManager::FiringItemManager()
{
    damageObjGenerator = new DamageObjectGenerator();
}

FiringItemManager::~FiringItemManager()
{
    for (auto ite = damageObjList.begin(); ite != damageObjList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
    damageObjList.clear();
}

void FiringItemManager::AddFiringObject(Actor* damageObj)
{
    if (damageObj != nullptr)
    {
        damageObjList.push_back(damageObj);
    }
}

void FiringItemManager::Update()
{
    //イテレーター
    auto objIte = damageObjList.begin();
    //消去していいやつリスト
    std::list<Actor*> brokenList;
    //更新する必要が無くなったら消去
    while (objIte != damageObjList.end())
    {
        (*objIte)->Update();
        if (!(*objIte)->GetAliveFlag()) //もう存在していなかったら更新終了
        {
            brokenList.push_back((*objIte));

            objIte = damageObjList.erase(objIte);//eraseは消したイテレーターの次の奴を返す
        }
        else
        {
            ++objIte;//消す条件に合わなかったら次に
        }
    }
    //消していいやつ消す
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
}

void FiringItemManager::Draw()
{
    for (auto objIte = damageObjList.begin(); objIte != damageObjList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
}
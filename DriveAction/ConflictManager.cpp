#include "ConflictManager.h"

std::list<ConflictProccesor*> ConflictManager::conflictObjList;
std::unordered_map<ConflictProccesor*, std::list<ConflictProccesor*>> ConflictManager::conflictMap;
ConflictManager::ConflictManager()
{
}

ConflictManager::~ConflictManager()
{

}
/// <summary>
/// �����蔻���ǉ�
/// </summary>
/// <param name="conflictProccesor"></param>
void ConflictManager::AddConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    conflictObjList.push_back(conflictProccesor);
}
/// <summary>
///�@�����蔻������Ȃ��Ă����悤�ɂ���
/// </summary>
/// <param name="conflictProccesor"></param>
void ConflictManager::EraceConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    conflictMap.erase(conflictProccesor);
    auto procceesor = std::find(conflictObjList.begin(), conflictObjList.end(), conflictProccesor);
    if (procceesor != conflictObjList.end())
    {
        conflictObjList.erase(procceesor);
    }
}
/// <summary>
/// �f�o�b�O�p�̋������蔻���������
/// </summary>
void ConflictManager::DrawCollisionSphere()
{
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
       HitCheckExamineObjectInfo info = (*objIte)->GetHitExamineCheckInfo();
        DrawSphere3D(info.pos, info.radius, 4, GetColor(200, 200, 200), GetColor(200, 200, 200), false);
    }
}

/// <summary>
/// �����̃I�u�W�F�N�g�ƂԂ����Ă��邩���ׂ�
/// </summary>
/// <param name="examineObjInfo"></param>
/// <returns></returns>
std::list<ConflictExamineResultInfo> ConflictManager::GetConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    std::list<ConflictExamineResultInfo> nowHitList;
    ConflictExamineResultInfo examineResultInfo = {};
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        //�����̃I�u�W�F�N�g���̂��̂Ɠ������Ă���X���[
        if (conflictProccesor != (*objIte))
        {
            //�������Ă��邩���ׂ�
            examineResultInfo = (*objIte)->HitCheck(conflictProccesor->GetHitExamineCheckInfo());
            //�Ԃ����Ă���Ȃ�
            if (examineResultInfo.hit != HitSituation::NotHit)
            {
                if (conflictMap.contains(conflictProccesor))
                {
                    //���X�g�ɓo�^�ς݂�
                    if (IsContainsConflictList(conflictProccesor, (*objIte)))
                    {
                        //���łɂ��Ă��镨�Ȃ瓖���葱���Ă���
                        examineResultInfo.hit = HitSituation::Stay;
                    }
                    else
                    {
                        //���X�g�ɓo�^
                        conflictMap[conflictProccesor].push_back((*objIte));
                    }
                }
                else
                {
                    //���߂ē������Ă���Ȃ�map�ɒǉ�
                    std::list<ConflictProccesor*> list;
                    list.push_back((*objIte));
                    conflictMap.insert(std::make_pair(conflictProccesor,list));
                }
                //������������ǉ�
                nowHitList.push_back(examineResultInfo);
            }
            //���������ĂȂ����ǂԂ��������Ƃ̂�����̂Ȃ�
            if (IsContainsConflictList(conflictProccesor, (*objIte)))
            {
                //�������܂œ������Ă����Ǔ�����Ȃ��Ȃ����̂Ń��X�g�������
                auto containIte = std::find(conflictMap[conflictProccesor].begin(), conflictMap[conflictProccesor].end(),(*objIte));
                conflictMap[conflictProccesor].erase(containIte);
                //�������܂œ������Ă���͗��ꂽ����
                examineResultInfo.hit = HitSituation::Exist;
                //���ꂽ����̂��̂��ǉ�
                nowHitList.push_back(examineResultInfo);
            }
        }
    }
    return nowHitList;
}

bool ConflictManager::IsContainsConflictList(ConflictProccesor* proccesor, ConflictProccesor* pastProccesor)
{
    for (auto ite = conflictMap[proccesor].begin(); ite != conflictMap[proccesor].end(); ite++)
    {
        if ((*ite) == pastProccesor)
        {
            return true;
        }
    }
    return false;
}


void ConflictManager::Update()
{
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        (*objIte)->ConflictProccess(GetConflictObjInfo((*objIte)));
    }
}
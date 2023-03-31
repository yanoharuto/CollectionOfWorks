#pragma once
#include <string>
#include <fstream>
#include "DxLib.h"
/// <summary>
/// �x�N�^�[�̃f�[�^���������ɋL�^����
/// </summary>
class VectorDataCreator
{
public:
    VectorDataCreator();
    /// <summary>
    /// �J���������̃t�@�C���l�[��
    /// </summary>
    /// <param name="setFileName"></param>
    VectorDataCreator(std::string setFileName);
    ~VectorDataCreator();
    /// <summary>
    /// �ǉ��ŏ�������
    /// </summary>
    /// <param name="vec"></param>
    void WriteVECTOR(VECTOR vec);
private:
    std::ofstream writing_file;
    std::string fileName;
};

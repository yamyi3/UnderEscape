#include "teleportmanager.h"
#include "..\..\stage\stage.h"
#include <iostream>
#include <vector>
TeleportManager::TeleportManager()
{
}
TeleportManager& TeleportManager::GetInstance()
{
	static  TeleportManager instance;
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return instance;
}

void TeleportManager::Initialize(const int tp_stairs_count)
{
    const int g_map_chip_count_width=Stage::GetInstance().GetStageWidthCount();
    const int g_map_chip_count_height = Stage::GetInstance().GetStageHeightCount();

    std::vector<std::vector<int>> g_Map(g_map_chip_count_height, std::vector<int>(g_map_chip_count_width));

	const int tp_set_count = tp_stairs_count / 2;
	for (int i = 0; i < tp_set_count; i++)
	{
		Teleport* teleport = nullptr;
		teleport = new Teleport();
		if (!teleport)return;
		teleport->Initialize();

		m_Teleport.push_back(teleport);
	}
    //�t�@�C������

    FILE* fp = nullptr;
    // �t�@�C�����J�� 
    fopen_s(&fp, "data\\TP.csv", "r");
    // �T�C�Y�𒲂ׂ� 
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    // �T�C�Y���������ꕨ��p�ӂ���(�ꎞ�I�ȃf�[�^) 
    char* buf = new char[size];
    // �f�[�^(CSV�t�@�C�����̕�����)��ǂݍ��� 
    fread(buf, size, 1, fp);
    // �t�@�C�������
    fclose(fp);

    //�f�[�^���

        // �f�[�^�̃T�C�Y���J��Ԃ� 
    for (int i = 0, k = 0; i < size; ++i)
    {
        // ������0�`3�ł���ΐ��l�ɕϊ����� 
        if (buf[i] >= '0' && buf[i] <= '0'+ tp_set_count)
        {
            char t = buf[i];
            g_Map[k / g_map_chip_count_width][k % g_map_chip_count_width] =
                (unsigned char)atoi(&t);
            ++k;
        }
    }
    // �ꎞ�I�ȃf�[�^���폜 
    delete[] buf;
}

void TeleportManager::Update()
{
}

void TeleportManager::Draw()
{
}

void TeleportManager::Finalize()
{
}

vivid::Vector2 TeleportManager::StairsTeleport(vivid::Vector2)
{
    return{ 0,0 };
}

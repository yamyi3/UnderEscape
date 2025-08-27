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
	// TODO: return ステートメントをここに挿入します
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
    //ファイル操作

    FILE* fp = nullptr;
    // ファイルを開く 
    fopen_s(&fp, "data\\TP.csv", "r");
    // サイズを調べる 
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    // サイズ分だけ入れ物を用意する(一時的なデータ) 
    char* buf = new char[size];
    // データ(CSVファイル内の文字列)を読み込む 
    fread(buf, size, 1, fp);
    // ファイルを閉じる
    fclose(fp);

    //データ解析

        // データのサイズ分繰り返し 
    for (int i = 0, k = 0; i < size; ++i)
    {
        // 文字の0～3であれば数値に変換する 
        if (buf[i] >= '0' && buf[i] <= '0'+ tp_set_count)
        {
            char t = buf[i];
            g_Map[k / g_map_chip_count_width][k % g_map_chip_count_width] =
                (unsigned char)atoi(&t);
            ++k;
        }
    }
    // 一時的なデータを削除 
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

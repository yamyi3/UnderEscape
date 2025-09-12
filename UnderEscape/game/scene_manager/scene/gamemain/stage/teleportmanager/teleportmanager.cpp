#include "teleportmanager.h"
#include "..\..\stage\stage.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
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
    map_chip_size = Stage::GetInstance().GetMapChipSize();

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







    // ファイル読み込み
    FILE* fp = nullptr;
    // ファイルを開く 
    fopen_s(&fp, "data\\TP.csv", "r");
    // サイズを調べる 
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    // サイズ分だけ入れ物を用意する(一時的なデータ) 
    char* buf = new char[size + 1];   // +1 は文字列終端用
    // データ(CSVファイル内の文字列)を読み込む 
    fread(buf, size, 1, fp);
    buf[size] = '\0';                 // 文字列終端を付与
    // ファイルを閉じる
    fclose(fp);

    // CSV解析
    std::string data(buf);
    // 一時的なデータを削除 
    delete[] buf;

    std::stringstream ss(data);
    int k = 0;
    int value;

    while (ss >> value) {
        // 配列に代入（2次元→1次元に直して格納）
        g_Map[k / g_map_chip_count_width][k % g_map_chip_count_width] =
            value;
        ++k;

        // 区切り文字が来たら読み飛ばす
        if (ss.peek() == ',' || ss.peek() == '\n') {
            ss.ignore();
        }
    }


    for (int y = 0; y < g_map_chip_count_height; y++)
    {
        for (int x = 0; x < g_map_chip_count_width; x++)
        {
            if (g_Map[y][x]!=0)
            {
                //m_Teleport g_Map[y][x]
                TELEPORT_LIST::iterator it = m_Teleport.begin();
                for (int i = 0; i < g_Map[y][x]-1; i++)
                {
                    it++;
                }
                vivid::Vector2 ob_pos = { (float)(x * map_chip_size),(float)(y * map_chip_size) };
                (*it)->InputTpPos(ob_pos);
            }
        }
    }
}

void TeleportManager::Update()
{
}

void TeleportManager::Draw()
{
    TELEPORT_LIST::iterator it = m_Teleport.begin();
    TELEPORT_LIST::iterator end = m_Teleport.end();
    
    while (it != end)
    {
        (*it)->Draw(scroll);

        ++it;
    }
}

void TeleportManager::Finalize()
{
}

bool TeleportManager::GetTeleportFlg(vivid::Vector2 c_pos)
{

    
    TELEPORT_LIST::iterator it = m_Teleport.begin();
    TELEPORT_LIST::iterator end = m_Teleport.end();
    while (it != end)
    {
        Teleport* teleport = (*it);

        if ((*it)->GetTeleportFlg(c_pos))
            return true;
        ++it;
    }
    return false;
}

vivid::Vector2 TeleportManager::StairsTeleport(vivid::Vector2 c_pos)
{
    TELEPORT_LIST::iterator it = m_Teleport.begin();
    TELEPORT_LIST::iterator end = m_Teleport.end();
    while (it != end)
    {
        Teleport* teleport = (*it);

        vivid::Vector2 tp_pos = (*it)->GetTeleportPos(c_pos);
        if (tp_pos!=c_pos)
            return tp_pos;
        ++it;
    }
    return c_pos;

}

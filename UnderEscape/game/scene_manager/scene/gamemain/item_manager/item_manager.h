#pragma once
#include<list>
#include"vivid.h"
//#include"item/sound_item/sound_item.h"
#include"item/item.h"
#include"item/item_id.h"
class ItemManager
{
public:
	// �C���X�^���X�̎擾
	static ItemManager& GetInstance();
	// ������
	void Initialize();
	// �X�V
	void Update(vivid::Vector2 cPos, float cWidth, float cHeight, float rHeight);
	// �`��
	void Draw();
	// �J��
	void Finalize();
	// �A�C�e���̐���
	void CreateItem(vivid::Vector2 position,ItemID id);

private:
	using ITEM_LIST = std::list<Item*>;
	ITEM_LIST m_Item;										// �A�C�e���̃��X�g
	ItemManager() = default;								// �R���X�g���N�^
	ItemManager(const ItemManager&) = delete;				// �R�s�[�R���X�g���N�^���폜
	ItemManager& operator=(const ItemManager&) = delete;	// ������Z�q���폜
	~ItemManager() = default;								// �f�X�g���N�^
};


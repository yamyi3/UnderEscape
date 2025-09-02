#pragma once
#include<list>
#include"vivid.h"
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
	void Update(vivid::Vector2 cPos, float cWidth, float cHeight, float rHeight,bool check);
	// �`��
	void Draw();
	// �J��
	void Finalize();
	// �A�C�e���̐���
	void CreateItem(vivid::Vector2 position,ITEM_ID id);
	//�A�C�e���̃A�N�e�B�u�t���O���擾
	bool GetItemActiveFlag();	
	//�A�C�e���̈ʒu���擾
	vivid::Vector2 GetItemPos();
	//�A�C�e���̗L���͈͂��擾
	float GetEfectiveArea(ITEM_ID);
	//ITEM_ID���擾
	ITEM_ID GetItemID();
	//ITEM_STATE���擾
	bool GetItemCheck();
private:

	ITEM_ID Item_id;
	using ITEM_LIST = std::list<Item*>;
	ITEM_LIST m_Item;										// �A�C�e���̃��X�g
	ItemManager() = default;								// �R���X�g���N�^
	ItemManager(const ItemManager&) = delete;				// �R�s�[�R���X�g���N�^���폜
	ItemManager& operator=(const ItemManager&) = delete;	// ������Z�q���폜
	~ItemManager() = default;								// �f�X�g���N�^
};


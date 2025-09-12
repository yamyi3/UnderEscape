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
	void Update(vivid::Vector2 cPos, float cWidth, float cHeight, float rHeight);
	// �`��
	void Draw();
	// �J��
	void Finalize();
	// �A�C�e���̐���
	void CreateItem(vivid::Vector2 position, ITEM_ID id);
	//�A�C�e���̃A�N�e�B�u�t���O���擾
	bool GetItemActiveFlag();
	//�A�C�e���̈ʒu���擾
	vivid::Vector2 GetItemPos();
	//�A�C�e���̗L���͈͂��擾
	float GetEfectiveArea();
	//ITEM_ID���擾
	ITEM_ID GetItemID();
	//ITEM_STATE���擾
	bool GetItemCheck();
private:
	bool				priority;			//�A�C�e���̗D��t���O
	float 				effective_area;		//�A�C�e���̗L���͈�
	bool				active;				//�A�C�e���̃A�N�e�B�u�t���O
	vivid::Vector2		position;			//�A�C�e���̈ʒu
	ITEM_ID				Item_id;			//�A�C�e����ID
	using ITEM_LIST = std::list<CItem*>;
	ITEM_LIST m_Item;						// �A�C�e���̃��X�g

	CItem* m_CatchItem;

	//�A�C�e���������Ă�����
	void PickupItem(const vivid::Vector2& center_pos);
	//�����铮��Ɉڍs
	void ThrowItem(void);
	//�u������Ɉڍs
	void PlaceItem(const vivid::Vector2& c_pos);

	ItemManager();								// �R���X�g���N�^
	ItemManager(const ItemManager&) = delete;				// �R�s�[�R���X�g���N�^���폜
	ItemManager& operator=(const ItemManager&) = delete;	// ������Z�q���폜
	~ItemManager() = default;								// �f�X�g���N�^
};


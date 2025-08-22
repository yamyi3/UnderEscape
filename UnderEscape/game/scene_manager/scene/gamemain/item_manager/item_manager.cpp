#include "item_manager.h"
#include"item/item.h"
#include"item/sound_item/sound_item.h"
#include"item/flash_item/flash_item.h"
#include"../character/character.h"
ItemManager& ItemManager::GetInstance()
{
	static ItemManager instance;
	return instance;
}

void ItemManager::Initialize()
{
	
}

void ItemManager::Update(vivid::Vector2 cPos, float cWidth, float cHeight,   float rHeight)
{
	ITEM_LIST::iterator it = m_Item.begin();
	ITEM_LIST::iterator end = m_Item.end();

	while (it != end)
	{
		//�s�����ȃf�[�^�̏���
		if (!(*it)->IsActive())
		{
			(*it)->Finalize();

			delete (*it);

			it = m_Item.erase(it);

			continue;
		}

		(*it)->Update( cPos,  cWidth,  cHeight,  rHeight);
		++it;
	}
}


void ItemManager::Draw()
{
	//�e�A�C�e���I�u�W�F�N�g�̕`��
	ITEM_LIST::iterator    it = m_Item.begin();
	ITEM_LIST::iterator    end = m_Item.end();

	while (it != end)
	{
		(*it)->Draw();

		++it;
	}
}

void ItemManager::Finalize()
{
	//�e�A�C�e���I�u�W�F�N�g�̕`��
	ITEM_LIST::iterator    it = m_Item.begin();
	ITEM_LIST::iterator    end = m_Item.end();

	while (it != end)
	{
		(*it)->Finalize();

		delete(*it);

		++it;
	}
	m_Item.clear(); // ���X�g���N���A
}

void ItemManager::CreateItem(vivid::Vector2 position, ItemID id)
{
	Item* item = nullptr;

	switch (id)
	{
	case ItemID::SOUND_ITEM:	item = new SoundItem();
		break;
	case ItemID::FLASH_ITEM:	item = new FlashItem();
		break;
	case ItemID::UNKNOWN_ITEM:
		break;
	default:
		break;
	}
	
	if (!item)return;

	item->Initialize(position);

	m_Item.push_back(item);
}

bool ItemManager::GetItemActiveFlag()
{
	//�e�A�C�e���I�u�W�F�N�g�̕`��
	ITEM_LIST::iterator    it = m_Item.begin();
	ITEM_LIST::iterator    end = m_Item.end();

	bool Active = false;
	while (it != end)
	{
		Active=(*it)->GetItemActive();

		++it;
	}
	return Active;

}

vivid::Vector2 ItemManager::GetItemPos()
{
	//�e�A�C�e���I�u�W�F�N�g�̕`��
	ITEM_LIST::iterator    it = m_Item.begin();
	ITEM_LIST::iterator    end = m_Item.end();

	vivid::Vector2 Pos(0.0f, 0.0f);
	while (it != end)
	{
		Pos = (*it)->GetItemPos();

		++it;
	}
	return Pos;
}

float ItemManager::GetEfectiveArea()
{
	//�e�A�C�e���I�u�W�F�N�g�̕`��
	ITEM_LIST::iterator    it = m_Item.begin();
	ITEM_LIST::iterator    end = m_Item.end();

	float Area;
	while (it != end)
	{
		Area = (*it)->GetEffectiveArea();

		++it;
	}
	return Area;
}



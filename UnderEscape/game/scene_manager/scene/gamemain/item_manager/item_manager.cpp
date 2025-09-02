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

void ItemManager::Update(vivid::Vector2 cPos, float cWidth, float cHeight,   float rHeight, bool check)
{
	ITEM_LIST::iterator it = m_Item.begin();
	ITEM_LIST::iterator end = m_Item.end();

	while (it != end)
	{
		//不活性なデータの消去
		if (!(*it)->IsActive())
		{
			(*it)->Finalize();

			delete (*it);

			it = m_Item.erase(it);

			continue;
		}

		(*it)->Update( cPos,  cWidth,  cHeight,  rHeight, check);
		++it;
	}
}


void ItemManager::Draw()
{
	//各アイテムオブジェクトの描画
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
	//各アイテムオブジェクトの描画
	ITEM_LIST::iterator    it = m_Item.begin();
	ITEM_LIST::iterator    end = m_Item.end();

	while (it != end)
	{
		(*it)->Finalize();

		delete(*it);

		++it;
	}
	m_Item.clear(); // リストをクリア
}

void ItemManager::CreateItem(vivid::Vector2 position, ITEM_ID id)
{
	Item* item = nullptr;

	switch (id)
	{
	case ITEM_ID::SOUND_ITEM:	item = new SoundItem();
		//Item_effective_area = item->GetEffectiveArea();
		break;
	case ITEM_ID::FLASH_ITEM:	item = new FlashItem();
		//Item_effective_area = item->GetEffectiveArea();
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
	//各アイテムオブジェクトの描画
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
	//各アイテムオブジェクトの描画
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

float ItemManager::GetEfectiveArea(ITEM_ID id)
{
	//各アイテムオブジェクトの描画
	ITEM_LIST::iterator    it = m_Item.begin();
	ITEM_LIST::iterator    end = m_Item.end();

	float a;
	while (it != end)
	{
		a = (*it)->GetEffectiveArea( id );
		++it;
	}
	return a;
}


ITEM_ID ItemManager::GetItemID()
{
	//各アイテムオブジェクトの描画
	ITEM_LIST::iterator    it = m_Item.begin();
	ITEM_LIST::iterator    end = m_Item.end();

									//アイテムの種類

	while (it != end)
	{
		if ((*it)->GetCatchFlg() == true)
		{
			Item_id = (*it)->GetItemID();

			return Item_id;

		}
		++it;
	}
	return ITEM_ID::DUMMY;
}

bool ItemManager::GetItemCheck()
{
	//各アイテムオブジェクトの描画
	ITEM_LIST::iterator    it = m_Item.begin();
	ITEM_LIST::iterator    end = m_Item.end();

	//アイテムの種類
	ITEM_STATE state;
	while (it != end)
	{
		if ((*it)->GetCatchFlg() == true)
		{
			return true;
		}
		it++;
	}
	return false;
}



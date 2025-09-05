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

void ItemManager::Update(vivid::Vector2 cPos, float cWidth, float cHeight, float rHeight)
{
	ITEM_LIST::iterator it = m_Item.begin();
	ITEM_LIST::iterator end = m_Item.end();
	ITEM_LIST::iterator priority = it;
	bool check = GetItemCheck();
	float c;
	while (it != end && priority != end)
	{
		//if ((*priority)->GetPriority() <= (*it)->GetPriority())
		//{
		//}
		//else
		//{
		//	priority = it;
		//}
		//不活性なデータの消去
		if (!(*it)->IsActive())
		{
			(*it)->Finalize();

			delete (*it);

			it = m_Item.erase(it);

			continue;
		}
		////(*priority)->Update(cPos, cWidth, cHeight, rHeight, check, true);
		(*it)->Update(cPos, cWidth, cHeight, rHeight, check, true);

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
	return active;
}

vivid::Vector2 ItemManager::GetItemPos()
{
	return position;
}

float ItemManager::GetEfectiveArea()
{
	return effective_area;
}


ITEM_ID ItemManager::GetItemID()
{
	return Item_id;
}

bool ItemManager::GetItemCheck()
{
	//各アイテムオブジェクトの描画
	ITEM_LIST::iterator    it = m_Item.begin();
	ITEM_LIST::iterator    end = m_Item.end();

	//アイテムの所持判別
	while (it != end)
	{

		if ((*it)->GetCatchFlg() == true)
		{
			position = (*it)->GetItemPos();
			active = (*it)->GetItemActive();
			Item_id = (*it)->GetItemID();
			effective_area = (*it)->GetEffectiveArea();
			return true;
		}
		else
		{
			position = vivid::Vector2(0.0f, 0.0f);
			active = false;
			Item_id = ITEM_ID::DUMMY;
			effective_area = 0;
		}


		it++;
	}
	return false;
}



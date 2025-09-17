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


	while (it != end)
	{
		(*it)->Update(cPos, cWidth, cHeight, rHeight);

		//不活性なデータの消去
		if (!(*it)->IsActive())
		{
			(*it)->Finalize();

			delete (*it);

			it = m_Item.erase(it);

			continue;
		}

		++it;
	}

	// 拾う・使う
	bool is_pick_up = vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::F);
	bool is_throw = vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::C);
	bool is_place = vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::V);

	if (is_pick_up || Character::GetInstance().GetTriggerA()) PickupItem(vivid::Vector2(cPos.x + cWidth / 2.0f, cPos.y + cHeight / 2.0f));
	if (is_throw || Character::GetInstance().GetTriggerLB())	ThrowItem();
	if (is_place)PlaceItem(cPos);
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
	CItem* item = nullptr;

	switch (id)
	{
	case ITEM_ID::SOUND_ITEM:	item = new CSoundItem();
		//Item_effective_area = item->GetEffectiveArea();
		break;
	case ITEM_ID::FLASH_ITEM:	item = new CFlashItem();
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


void ItemManager::PickupItem(const vivid::Vector2& center_pos)
{
	if (m_CatchItem) return;

	ITEM_LIST::iterator it = m_Item.begin();
	ITEM_LIST::iterator end = m_Item.end();

	CItem* item = nullptr;
	float length = FLT_MAX;

	while (it != end)
	{
		if ((*it)->CanPickUp())
		{
			vivid::Vector2 v = center_pos - (*it)->GetCenterPosition();

			if (length > v.Length())
			{
				m_CatchItem = (*it);

				length = v.Length();
			}
		}

		++it;
	}

	if (m_CatchItem != nullptr)
		m_CatchItem->Found();

	return;
}

void ItemManager::ThrowItem(void)
{
	if (m_CatchItem == nullptr) return;

	m_CatchItem->Thrown();

	m_CatchItem = nullptr;
}

void ItemManager::PlaceItem(const vivid::Vector2& c_pos)
{
	if (m_CatchItem == nullptr) return;

	m_CatchItem->Place(c_pos);

	m_CatchItem = nullptr;

}

ItemManager::ItemManager()
	: m_CatchItem(nullptr)
{
}



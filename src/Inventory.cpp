#include "Inventory.h"
#include "Item.h"
#include <iostream>

Inventory::Inventory() = default;

Inventory::~Inventory() = default;


void Inventory::AddItem(std::unique_ptr<Item> item)
{
	Items.emplace_back(std::move(item));
}

std::unique_ptr<Item> Inventory::RemoveItem(size_t index)
{
	if (index >= Items.size())
	{
		std::cout << "잘못된 인덱스입니다.\n\n";
		return nullptr;
	}
	std::unique_ptr<Item> item = std::move(Items[index]);
	Items.erase(Items.begin() + index);
	return item;
}

Item* Inventory::GetItem(size_t index) const
{
	if (index >= Items.size())
	{
		return nullptr;
	}
	return Items[index].get();
}

void Inventory::PrintInventory() const
{
	if (Items.empty())
	{
		std::cout << "보유한 아이템이 없습니다.\n\n";
		return;
	}

	for(int i = 0; i < Items.size(); ++i)
	{
		Item* it = Items[i].get();
		std::cout << "[" << i << "] "
			<< it->GetName() << " / "
			<< it->GetItemTypeName() << " / "
			<< it->GetValue() << "\n";
	}
	std::cout << "\n";
}

size_t Inventory::Count() const
{
	return Items.size();
}


